In concurrent programs, threads often need to coordinate:

* one thread **produces** data
* another thread **consumes** it
* some threads must **wait** until a condition becomes true

Busy-waiting like this is wasteful:

```cpp
while (!ready) {
    // keep checking
}
```

It burns CPU.

A **condition variable** lets a thread **sleep efficiently** until some state changes.

A **blocking queue** is a classic abstraction built using:

* a mutex
* a condition variable
* a container like `std::queue`

It lets producers push items and consumers wait until items are available.

---

# 2. Core primitives in C++ concurrency

Before condition variables, you need the core building blocks.

## 2.1 `std::thread`

Represents an OS thread.

```cpp
std::thread t([] {
    // work
});
t.join();
```

## 2.2 `std::mutex`

Protects shared data from concurrent access.

```cpp
std::mutex m;
m.lock();
// critical section
m.unlock();
```

Usually use RAII wrappers instead of manual lock/unlock.

## 2.3 `std::lock_guard`

Simple scoped mutex lock.

```cpp
std::lock_guard<std::mutex> lock(m);
```

Locks on construction, unlocks on destruction.

## 2.4 `std::unique_lock`

More flexible than `lock_guard`. Required for `std::condition_variable`.

```cpp
std::unique_lock<std::mutex> lock(m);
```

Why not `lock_guard` for condition variables?
Because condition variable wait must:

* unlock the mutex while waiting
* relock it when awakened

That requires a movable/unlockable lock object, which `unique_lock` provides.

## 2.5 `std::condition_variable`

Lets threads wait for a condition.

Main operations:

* `wait(lock)`
* `wait(lock, predicate)`
* `notify_one()`
* `notify_all()`

---

# 3. Condition variable basics

A condition variable does **not** store a condition by itself.

That is one of the most important ideas.

It is only a mechanism for:

* putting threads to sleep
* waking them up

The **actual condition** lives in shared state, protected by a mutex.

Example shared state:

```cpp
bool ready = false;
std::mutex m;
std::condition_variable cv;
```

Waiting thread:

```cpp
std::unique_lock<std::mutex> lock(m);
cv.wait(lock, [] { return ready; });
```

Signaling thread:

```cpp
{
    std::lock_guard<std::mutex> lock(m);
    ready = true;
}
cv.notify_one();
```

---

# 4. Correct mental model

A condition variable is always tied to:

* **state**
* **mutex**
* **waiters**
* **notifications**

The standard pattern is:

## Wait side

1. lock mutex
2. check condition
3. if false, sleep using `cv.wait(...)`
4. when awakened, re-check condition
5. proceed when condition is true

## Notify side

1. lock mutex
2. modify shared state
3. unlock mutex
4. notify waiting thread(s)

---

# 5. The golden rule: always wait with a predicate

Never do this casually:

```cpp
cv.wait(lock);
```

unless you really understand what you are doing.

Prefer:

```cpp
cv.wait(lock, [] { return ready; });
```

or equivalent loop:

```cpp
while (!ready) {
    cv.wait(lock);
}
```

Why?

Because of:

* **spurious wakeups**
* **missed assumptions**
* multiple consumers racing for the same resource

---

# 6. Spurious wakeups

A waiting thread can wake up even if nobody meaningfully notified it.

So this is wrong:

```cpp
if (!ready) {
    cv.wait(lock);
}
```

Because after waking, `ready` might still be false.

Correct:

```cpp
while (!ready) {
    cv.wait(lock);
}
```

or:

```cpp
cv.wait(lock, [] { return ready; });
```

The predicate overload is just cleaner and safer.

---

# 7. Example: simplest condition variable

## Problem

One worker thread waits until main thread says “start”.

```cpp
#include <iostream>
#include <thread>
#include <mutex>
#include <condition_variable>

std::mutex m;
std::condition_variable cv;
bool ready = false;

void worker() {
    std::unique_lock<std::mutex> lock(m);
    cv.wait(lock, [] { return ready; });
    std::cout << "Worker started\n";
}

int main() {
    std::thread t(worker);

    {
        std::lock_guard<std::mutex> lock(m);
        ready = true;
    }
    cv.notify_one();

    t.join();
}
```

## What happens

* worker locks mutex
* worker checks `ready`
* if false, worker sleeps
* main sets `ready = true`
* main notifies
* worker wakes, reacquires mutex, checks predicate again, continues

---

# 8. Why mutex is required with condition variable

A common beginner question:
“Why can’t I just wait on the condition variable without a mutex?”

Because you need atomic coordination between:

* checking the state
* going to sleep

Without the mutex, you can get a race like:

1. worker checks `ready == false`
2. notifier sets `ready = true` and calls notify
3. worker goes to sleep after the notify
4. worker sleeps forever

The mutex + wait mechanism prevents that race.

---

# 9. What `wait()` does internally

When you call:

```cpp
cv.wait(lock);
```

it roughly does this atomically:

1. put the thread into the condition variable’s wait queue
2. unlock the mutex
3. suspend the thread

When awakened:
4. reacquire the mutex
5. return to caller

That unlock-and-sleep transition is the key.

Pseudo-internal view:

```cpp
while (!predicate()) {
    enqueue_current_thread_on_cv();
    unlock(mutex);
    sleep();
    wake_up();
    lock(mutex);
}
```

Not exact implementation, but close enough conceptually.

---

# 10. `notify_one()` vs `notify_all()`

## `notify_one()`

Wakes one waiting thread.

Use when:

* only one thread can make progress
* e.g. one new item added to a queue

## `notify_all()`

Wakes all waiting threads.

Use when:

* many threads may now proceed
* e.g. shutdown flag set
* barrier-like state changes
* broad state change affecting all waiters

### Example

If you push one item into a queue with 10 consumers, `notify_one()` is usually best.

If you set `stopped = true` and want all consumers to exit, use `notify_all()`.

---

# 11. Notify before unlock or after unlock?

You’ll see both patterns.

Common recommended form:

```cpp
{
    std::lock_guard<std::mutex> lock(m);
    ready = true;
}
cv.notify_one();
```

Why this is good:

* state change is protected
* lock is released before waking waiter
* waiter can often acquire mutex immediately after waking

If you notify while still holding the lock, correctness is still often fine, but performance may be worse because the awakened thread may just block again on the mutex.

---

# 12. Timed waits

You can wait with timeout.

## `wait_for`

```cpp
cv.wait_for(lock, std::chrono::seconds(1), [] {
    return ready;
});
```

## `wait_until`

```cpp
auto deadline = std::chrono::steady_clock::now() + std::chrono::seconds(1);
cv.wait_until(lock, deadline, [] {
    return ready;
});
```

Prefer predicate version here too.

---

# 13. Common mistakes with condition variables

## Mistake 1: using `if` instead of `while`

Wrong:

```cpp
if (queue.empty()) {
    cv.wait(lock);
}
```

Right:

```cpp
while (queue.empty()) {
    cv.wait(lock);
}
```

## Mistake 2: shared state not protected by mutex

Wrong if `ready` is read/written unsafely.

## Mistake 3: thinking notify stores events

Condition variables do not act like message queues.
If nobody is waiting, `notify_one()` does not accumulate a wake token.

The actual state must reflect what happened.

## Mistake 4: waiting on one mutex, modifying state with another

The same mutex must protect the condition and the state tied to it.

## Mistake 5: forgetting shutdown logic

In real systems, waiting threads often need a stop flag.

---

# 14. From condition variable to blocking queue

A **blocking queue** is a queue where:

* `push()` inserts an item
* `pop()` waits if queue is empty
* consumer thread sleeps efficiently until producer adds data

This is one of the most common interview questions.

---

# 15. Basic blocking queue implementation

## Unbounded blocking queue

```cpp
#include <queue>
#include <mutex>
#include <condition_variable>

template <typename T>
class BlockingQueue {
public:
    void push(const T& item) {
        {
            std::lock_guard<std::mutex> lock(m_);
            q_.push(item);
        }
        cv_.notify_one();
    }

    void push(T&& item) {
        {
            std::lock_guard<std::mutex> lock(m_);
            q_.push(std::move(item));
        }
        cv_.notify_one();
    }

    T pop() {
        std::unique_lock<std::mutex> lock(m_);
        cv_.wait(lock, [this] { return !q_.empty(); });

        T item = std::move(q_.front());
        q_.pop();
        return item;
    }

    bool empty() const {
        std::lock_guard<std::mutex> lock(m_);
        return q_.empty();
    }

    size_t size() const {
        std::lock_guard<std::mutex> lock(m_);
        return q_.size();
    }

private:
    mutable std::mutex m_;
    std::condition_variable cv_;
    std::queue<T> q_;
};
```

---

# 16. How this blocking queue works

## `push()`

* lock mutex
* push item
* unlock mutex
* notify one waiting consumer

## `pop()`

* lock mutex
* if queue empty, wait
* once non-empty, remove front item and return it

This is the core producer-consumer pattern.

---

# 17. Producer-consumer example

```cpp
#include <iostream>
#include <thread>
#include <vector>
#include <chrono>

int main() {
    BlockingQueue<int> q;

    std::thread producer([&] {
        for (int i = 1; i <= 5; ++i) {
            q.push(i);
            std::this_thread::sleep_for(std::chrono::milliseconds(100));
        }
    });

    std::thread consumer([&] {
        for (int i = 1; i <= 5; ++i) {
            int x = q.pop();
            std::cout << "Consumed: " << x << "\n";
        }
    });

    producer.join();
    consumer.join();
}
```

---

# 18. Why `notify_one()` is enough for queue push

Suppose one item is pushed.

Only one consumer can pop that single item.

If you `notify_all()`, all waiting consumers wake up:

* one gets the item
* others reacquire lock one by one
* see empty queue
* go back to sleep

That is called the **thundering herd** problem.

So for one item, prefer `notify_one()`.

---

# 19. Blocking queue with shutdown support

Real queues often need a way to stop waiting threads cleanly.

```cpp
#include <queue>
#include <mutex>
#include <condition_variable>
#include <optional>

template <typename T>
class StoppableBlockingQueue {
public:
    void push(const T& item) {
        {
            std::lock_guard<std::mutex> lock(m_);
            if (stopped_) return;
            q_.push(item);
        }
        cv_.notify_one();
    }

    void push(T&& item) {
        {
            std::lock_guard<std::mutex> lock(m_);
            if (stopped_) return;
            q_.push(std::move(item));
        }
        cv_.notify_one();
    }

    std::optional<T> pop() {
        std::unique_lock<std::mutex> lock(m_);
        cv_.wait(lock, [this] {
            return stopped_ || !q_.empty();
        });

        if (q_.empty()) {
            return std::nullopt; // stopped and no work left
        }

        T item = std::move(q_.front());
        q_.pop();
        return item;
    }

    void stop() {
        {
            std::lock_guard<std::mutex> lock(m_);
            stopped_ = true;
        }
        cv_.notify_all();
    }

private:
    std::mutex m_;
    std::condition_variable cv_;
    std::queue<T> q_;
    bool stopped_ = false;
};
```

## Why `notify_all()` in `stop()`

Because all waiting consumers should wake up and exit.

---

# 20. Bounded blocking queue

Another very common interview pattern.

## Problem

Queue has capacity `N`.

* producers block when queue is full
* consumers block when queue is empty

This uses **two conditions**:

* not empty
* not full

Usually implemented using:

* one mutex
* two condition variables, or sometimes one condition variable with two predicates

---

# 21. Bounded blocking queue implementation

```cpp
#include <queue>
#include <mutex>
#include <condition_variable>

template <typename T>
class BoundedBlockingQueue {
public:
    explicit BoundedBlockingQueue(size_t capacity)
        : capacity_(capacity) {}

    void push(const T& item) {
        std::unique_lock<std::mutex> lock(m_);
        not_full_.wait(lock, [this] { return q_.size() < capacity_; });

        q_.push(item);

        lock.unlock();
        not_empty_.notify_one();
    }

    void push(T&& item) {
        std::unique_lock<std::mutex> lock(m_);
        not_full_.wait(lock, [this] { return q_.size() < capacity_; });

        q_.push(std::move(item));

        lock.unlock();
        not_empty_.notify_one();
    }

    T pop() {
        std::unique_lock<std::mutex> lock(m_);
        not_empty_.wait(lock, [this] { return !q_.empty(); });

        T item = std::move(q_.front());
        q_.pop();

        lock.unlock();
        not_full_.notify_one();

        return item;
    }

private:
    size_t capacity_;
    std::queue<T> q_;
    std::mutex m_;
    std::condition_variable not_empty_;
    std::condition_variable not_full_;
};
```

---

# 22. Why two condition variables help

You could use one condition variable, but two often make the logic clearer:

* `not_empty_`: consumers wait here
* `not_full_`: producers wait here

This reduces unnecessary wakeups and makes intent more obvious.

---

# 23. Internal reasoning for bounded queue

### Producer push

* wait until `size < capacity`
* enqueue item
* signal that queue is now not empty

### Consumer pop

* wait until `!empty`
* dequeue item
* signal that queue is now not full

---

# 24. Interview pattern: implement producer-consumer

This usually tests whether you understand:

* mutex
* condition variable
* predicate wait
* spurious wakeups
* notify strategy

### Typical prompt

“Design a thread-safe queue where consumers block until an item is available.”

They expect:

* `std::mutex`
* `std::condition_variable`
* `std::queue<T>`
* `wait(lock, predicate)`

---

# 25. Interview pattern: multiple producers and consumers

Your queue should still work correctly with:

* many producers
* many consumers

The mutex serializes access to queue state.

The condition variable safely puts consumers to sleep when queue is empty.

Key idea:
Even if several consumers wake up, only one at a time can pop due to the mutex, and predicate re-check prevents errors.

---

# 26. Interview pattern: avoid lost wakeups

Interviewers often ask:
“What is a lost wakeup?”

A useful explanation:

A lost wakeup happens when a thread should have been awakened based on a state change, but due to incorrect synchronization, it misses that transition and sleeps indefinitely.

Using:

* shared state under mutex
* `wait(lock, predicate)`

prevents this class of bugs.

---

# 27. Interview pattern: semaphore vs condition variable

You may be asked to compare.

## Condition variable

* not a counter of events
* tied to a predicate over shared state
* requires mutex discipline

## Semaphore

* maintains permits/count
* `release()` increments
* `acquire()` decrements or blocks
* more naturally models available resources

In modern C++, `std::counting_semaphore` can sometimes simplify bounded-resource problems.

But condition variables are still foundational and often expected in interviews.

---

# 28. Interview pattern: one CV vs two CVs

For bounded queue:

* one CV is possible
* two CVs are often cleaner and more efficient

One CV can wake threads that still cannot proceed.
Two CVs target the right side more directly.

---

# 29. Interview pattern: why predicate must read shared state under lock

Because the predicate checks queue state that may be modified concurrently.

This is wrong:

```cpp
if (q_.empty()) { ... }  // outside lock
```

This is correct:

```cpp
std::unique_lock<std::mutex> lock(m_);
cv_.wait(lock, [this] { return !q_.empty(); });
```

---

# 30. Interview pattern: thread-safe queue vs blocking queue

They are not the same.

## Thread-safe queue

Operations are synchronized, but `pop()` may fail immediately if empty.

Example:

```cpp
bool try_pop(T& out);
```

## Blocking queue

`pop()` waits until data is available.

Example:

```cpp
T pop();
```

A strong interview answer mentions both APIs:

* `try_pop`
* blocking `pop`
* maybe timed `pop_for`

---

# 31. Nice production-style API design

A better queue often supports:

* `push`
* `try_pop`
* blocking `pop`
* timed `pop_for`
* `stop`
* `size`
* maybe `emplace`

Example sketch:

```cpp
template <typename T>
class BlockingQueue {
public:
    void push(T item);
    bool try_pop(T& out);
    std::optional<T> pop();
    template<class Rep, class Period>
    std::optional<T> pop_for(const std::chrono::duration<Rep, Period>& timeout);
    void stop();
};
```

---

# 32. Example with `try_pop`

```cpp
bool try_pop(T& out) {
    std::lock_guard<std::mutex> lock(m_);
    if (q_.empty()) return false;

    out = std::move(q_.front());
    q_.pop();
    return true;
}
```

Useful when caller does not want to block.

---

# 33. Example with timed pop

```cpp
template <typename T>
class TimedBlockingQueue {
public:
    void push(T item) {
        {
            std::lock_guard<std::mutex> lock(m_);
            q_.push(std::move(item));
        }
        cv_.notify_one();
    }

    template<class Rep, class Period>
    std::optional<T> pop_for(const std::chrono::duration<Rep, Period>& timeout) {
        std::unique_lock<std::mutex> lock(m_);
        bool ok = cv_.wait_for(lock, timeout, [this] { return !q_.empty(); });
        if (!ok) return std::nullopt;

        T item = std::move(q_.front());
        q_.pop();
        return item;
    }

private:
    std::mutex m_;
    std::condition_variable cv_;
    std::queue<T> q_;
};
```

---

# 34. Deeper internals: OS support

Under the hood, `std::condition_variable` is usually implemented using OS primitives:

* Linux: often futex-based mechanisms under the library/runtime
* Windows: condition variable primitives in kernel/user-mode support
* pthreads on POSIX systems: `pthread_cond_t`

The C++ standard does not mandate the exact implementation, only the semantics.

Conceptually:

* waiters are queued
* mutex release + sleep is coordinated atomically
* notifier wakes one or more waiters

---

# 35. Memory ordering intuition

Mutex locking/unlocking provides the needed synchronization.

Rough intuition:

* writes done by notifier thread before unlock become visible to waiter after waiter reacquires the same mutex

That is why condition variables are almost always used with mutex-protected state instead of random atomics alone.

---

# 36. Can atomics replace condition variables?

Not directly.

Atomics help with visibility and lock-free synchronization for some cases, but they do not by themselves provide efficient blocking sleep/wake coordination like condition variables do.

You can combine atomics with CVs, but it is usually harder to get right.

For interview and production clarity, prefer mutex + CV unless there is a strong reason otherwise.

---

# 37. Subtle example: missed design if state is not the source of truth

Bad design:

```cpp
// conceptual anti-pattern
producer:
    notify_one();

consumer:
    wait();
```

This is wrong because `notify_one` alone does not record “work exists”.

Good design:

```cpp
producer:
    lock
    queue.push(item)
    unlock
    notify_one()

consumer:
    lock
    wait until !queue.empty()
    pop item
```

The queue contents are the source of truth.

---

# 38. Example: worker thread pool pattern

A thread pool often uses a blocking queue of tasks.

```cpp
#include <functional>
#include <vector>
#include <thread>

class ThreadPool {
public:
    ThreadPool(size_t n) {
        for (size_t i = 0; i < n; ++i) {
            workers_.emplace_back([this] {
                while (true) {
                    auto task = tasks_.pop();
                    if (!task) return;
                    (*task)();
                }
            });
        }
    }

    void submit(std::function<void()> f) {
        tasks_.push(std::move(f));
    }

    void shutdown() {
        tasks_.stop();
        for (auto& t : workers_) {
            if (t.joinable()) t.join();
        }
    }

private:
    StoppableBlockingQueue<std::function<void()>> tasks_;
    std::vector<std::thread> workers_;
};
```

This is a classic real-world use case.

---

# 39. Example: bounded queue for backpressure

Suppose producers can generate work faster than consumers can process it.

An unbounded queue may grow forever.

A bounded blocking queue introduces **backpressure**:

* once full, producers block
* system self-regulates

This is important in:

* logging pipelines
* message processing
* networking
* job schedulers

---

# 40. Common interview question: can `notify_one()` wake the “wrong” thread?

Yes, in general it wakes one waiting thread, not necessarily one you specifically choose.

That is okay because awakened thread always re-checks predicate.

If it still cannot proceed, it waits again.

This is why predicates are fundamental.

---

# 41. Common interview question: what happens if notify occurs before wait starts?

If shared state is properly set, this is fine.

Example:

```cpp
{
    std::lock_guard<std::mutex> lock(m);
    ready = true;
}
cv.notify_one();
```

Then later waiter does:

```cpp
std::unique_lock<std::mutex> lock(m);
cv.wait(lock, [] { return ready; });
```

It will not block, because predicate is already true.

This is another reason the **state** matters more than the notification itself.

---

# 42. Single condition variable bounded queue variant

You may be asked whether you can do bounded queue with one CV. Yes.

```cpp
template <typename T>
class OneCvBoundedQueue {
public:
    explicit OneCvBoundedQueue(size_t cap) : capacity_(cap) {}

    void push(T item) {
        std::unique_lock<std::mutex> lock(m_);
        cv_.wait(lock, [this] { return q_.size() < capacity_; });
        q_.push(std::move(item));
        lock.unlock();
        cv_.notify_all();
    }

    T pop() {
        std::unique_lock<std::mutex> lock(m_);
        cv_.wait(lock, [this] { return !q_.empty(); });
        T item = std::move(q_.front());
        q_.pop();
        lock.unlock();
        cv_.notify_all();
        return item;
    }

private:
    size_t capacity_;
    std::queue<T> q_;
    std::mutex m_;
    std::condition_variable cv_;
};
```

Works, but may cause extra wakeups. Two CVs are usually better.

---

# 43. Interview-quality explanation of spurious wakeup

A good answer:

“A condition variable wait can return even if no useful notification for my condition occurred. Therefore waiting code must always re-check the condition in a loop or use the predicate overload.”

That answer is usually enough.

---

# 44. Exception safety notes

In queue implementations:

* use RAII locks
* move items when possible
* be careful if copying/moving `T` can throw

A stronger version might extract item before popping only after safe construction, depending on requirements.

For interviews, the simpler version is usually accepted.

---

# 45. Performance notes

## Lock granularity

Keep critical sections small.

Good:

```cpp
{
    std::lock_guard<std::mutex> lock(m_);
    q_.push(item);
}
cv_.notify_one();
```

Not ideal:

* doing long computations while holding queue mutex

## Avoid notify_all unless needed

Can wake many useless threads.

## Bounded queue can improve system stability

Prevents runaway memory growth.

---

# 46. Common follow-up: why not just use a spin lock or busy wait?

Busy wait may be okay for ultra-low-latency, very short waits in specialized systems, but generally:

* wastes CPU
* scales poorly
* increases contention

Condition variables are the standard efficient blocking tool.

---

# 47. A polished interview answer for blocking queue

If asked to explain from scratch, a strong concise answer is:

“A blocking queue is a thread-safe queue where `pop` blocks when the queue is empty. In C++, I’d implement it with a mutex to protect the queue and a condition variable to put consumers to sleep. Producers push under the mutex, then `notify_one`. Consumers take a `unique_lock`, call `wait(lock, predicate)` until the queue is non-empty, then pop the item. For bounded queues I’d add a second condition variable for `not_full` so producers block when capacity is reached.”

That is a very solid answer.

---

# 48. Full interview-ready bounded queue with stop support

This combines many patterns.

```cpp
#include <queue>
#include <mutex>
#include <condition_variable>
#include <optional>

template <typename T>
class BoundedStoppableQueue {
public:
    explicit BoundedStoppableQueue(size_t capacity)
        : capacity_(capacity) {}

    bool push(const T& item) {
        std::unique_lock<std::mutex> lock(m_);
        not_full_.wait(lock, [this] {
            return stopped_ || q_.size() < capacity_;
        });

        if (stopped_) return false;

        q_.push(item);
        lock.unlock();
        not_empty_.notify_one();
        return true;
    }

    bool push(T&& item) {
        std::unique_lock<std::mutex> lock(m_);
        not_full_.wait(lock, [this] {
            return stopped_ || q_.size() < capacity_;
        });

        if (stopped_) return false;

        q_.push(std::move(item));
        lock.unlock();
        not_empty_.notify_one();
        return true;
    }

    std::optional<T> pop() {
        std::unique_lock<std::mutex> lock(m_);
        not_empty_.wait(lock, [this] {
            return stopped_ || !q_.empty();
        });

        if (q_.empty()) {
            return std::nullopt;
        }

        T item = std::move(q_.front());
        q_.pop();
        lock.unlock();
        not_full_.notify_one();
        return item;
    }

    void stop() {
        {
            std::lock_guard<std::mutex> lock(m_);
            stopped_ = true;
        }
        not_empty_.notify_all();
        not_full_.notify_all();
    }

private:
    size_t capacity_;
    std::queue<T> q_;
    std::mutex m_;
    std::condition_variable not_empty_;
    std::condition_variable not_full_;
    bool stopped_ = false;
};
```

---

# 49. What interviewers really look for

Usually these points:

* shared state is protected by a mutex
* waiter uses `std::unique_lock`
* uses `wait(lock, predicate)` or loop
* understands spurious wakeups
* knows when to use `notify_one` vs `notify_all`
* can explain bounded queue with `not_full` and `not_empty`
* thinks about shutdown/termination

If you cover those, you are doing very well.

---

# 50. Quick summary cheatsheet

## Condition variable

Use it when a thread should sleep until shared state changes.

### Pattern

```cpp
std::unique_lock<std::mutex> lock(m);
cv.wait(lock, [] { return condition; });
```

### Signal side

```cpp
{
    std::lock_guard<std::mutex> lock(m);
    condition = true;
}
cv.notify_one();
```

## Rules

* protect condition state with mutex
* always wait with predicate or loop
* notification is not the state
* use `notify_one()` for one waiter
* use `notify_all()` for broad state changes like shutdown

## Blocking queue

Built from:

* `std::queue<T>`
* `std::mutex`
* `std::condition_variable`

### Unbounded

* producers never block
* consumers block on empty

### Bounded

* producers block on full
* consumers block on empty

---

# 51. Best practice interview examples to remember

## Example 1: one-time start flag

* thread waits for `ready`

## Example 2: producer-consumer queue

* classic blocking queue

## Example 3: bounded queue

* `not_empty` + `not_full`

## Example 4: stoppable worker pool

* stop flag + `notify_all`

These four cover most interview variations.

---

# 52. Final intuition in one sentence

A **condition variable** lets threads **sleep until protected shared state changes**, and a **blocking queue** is a classic structure built on that idea to coordinate producers and consumers safely and efficiently.
