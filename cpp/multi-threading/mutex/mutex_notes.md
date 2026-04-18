# Mutex Notes

## 1) Core concepts first

### What is a mutex?

A **mutex** (mutual exclusion lock) is a synchronization primitive that allows **only one thread at a time** to access a critical section.

Use it when:

* data is **shared across threads**
* at least one thread **modifies** that data
* correctness depends on multiple operations happening together

### Why do we need it?

Without synchronization, concurrent access can cause a **race condition**.

Example:

```cpp
counter = counter + 1;
```

This is not one atomic step. It is usually:

1. read `counter`
2. add 1
3. write result back

If two threads do that at the same time, one update can be lost.

### Critical section

A **critical section** is the part of code that touches shared mutable state.

Example:

```cpp
balance -= amount;
```

If many threads access `balance`, this operation should be protected.

### Basic mutex operations

```cpp
mtx.lock();
// critical section
mtx.unlock();
```

Better pattern in C++:

```cpp
{
    std::lock_guard<std::mutex> lock(mtx);
    // critical section
}
```

This automatically unlocks when the scope ends.

### Key idea to remember

A mutex makes concurrent code **correct**, not automatically fast.

---

## 2) The most important topics to remember

### A. Race condition

A race condition happens when the result depends on unpredictable thread timing.

Example:

```cpp
std::vector<int> v;
v.push_back(10);
```

If multiple threads call this on the same non-thread-safe container without protection, behavior may be incorrect or unsafe.

### B. Mutual exclusion

Only one thread at a time may enter the protected region.

### C. Ownership

Usually, the thread that locks the mutex must be the one that unlocks it.

### D. Blocking behavior

If one thread holds the mutex, another thread trying to lock it usually waits.

### E. Lock scope

Keep the locked region as small as possible.

Bad:

```cpp
lock(mtx);
read_file();
parse_data();
update_shared_state();
unlock(mtx);
```

Better:

```cpp
auto data = read_file();
auto parsed = parse_data(data);

lock(mtx);
update_shared_state();
unlock(mtx);
```

### F. Protect the data, not random code

Do not think “I should lock this function.”
Think “Which shared state must remain consistent?”

### G. Use scoped locking

Prefer patterns that guarantee unlock even if:

* an exception happens
* a return happens early
* logic changes later

C++:

```cpp
std::lock_guard<std::mutex> lock(mtx);
```

Python:

```python
with lock:
    counter += 1
```

Java:

```java
lock.lock();
try {
    count++;
} finally {
    lock.unlock();
}
```

---

## 3) Top interview patterns with clear examples

### Pattern 1: Thread-safe counter

This is the easiest and most common mutex example.

```cpp
#include <mutex>

std::mutex mtx;
int counter = 0;

void increment() {
    std::lock_guard<std::mutex> lock(mtx);
    ++counter;
}
```

**Interview explanation:**

* `counter` is shared mutable state
* increment is not guaranteed to be atomic
* mutex ensures only one thread updates at a time

**Follow-up:**
If the only operation is simple increment/decrement, an atomic may be better than a mutex.

---

### Pattern 2: Check-then-update must be atomic

A very common interview scenario.

#### Bank withdrawal example

```cpp
std::mutex mtx;
int balance = 100;

bool withdraw(int amount) {
    std::lock_guard<std::mutex> lock(mtx);
    if (balance >= amount) {
        balance -= amount;
        return true;
    }
    return false;
}
```

**Why mutex is needed:**
The check and the update must happen together.
Without a mutex, two threads can both see enough balance and both withdraw.

**Interview sentence:**
“The invariant is that balance must never be overdrawn by concurrent check-and-update operations.”

---

### Pattern 3: Thread-safe logging

Without locking, log output from different threads may interleave.

```cpp
std::mutex logMutex;

void logMessage(const std::string& msg) {
    std::lock_guard<std::mutex> lock(logMutex);
    std::cout << msg << std::endl;
}
```

**Interview point:**
Sometimes the shared resource is not a variable; it can be output, a file handle, or a shared device.

---

### Pattern 4: Thread-safe queue

A classic producer-consumer question.

```cpp
#include <queue>
#include <mutex>

std::queue<int> q;
std::mutex qMutex;

void push(int x) {
    std::lock_guard<std::mutex> lock(qMutex);
    q.push(x);
}

bool pop(int& out) {
    std::lock_guard<std::mutex> lock(qMutex);
    if (q.empty()) return false;
    out = q.front();
    q.pop();
    return true;
}
```

**Interview point:**
Mutex protects the queue’s internal consistency.

**Common extension:**
Use a **condition variable** so consumers can sleep until data arrives.

---

### Pattern 5: Producer-consumer with condition variable

This is very interview-relevant.

```cpp
#include <queue>
#include <mutex>
#include <condition_variable>

std::queue<int> q;
std::mutex mtx;
std::condition_variable cv;

void producer(int item) {
    {
        std::lock_guard<std::mutex> lock(mtx);
        q.push(item);
    }
    cv.notify_one();
}

int consumer() {
    std::unique_lock<std::mutex> lock(mtx);
    cv.wait(lock, [] { return !q.empty(); });

    int item = q.front();
    q.pop();
    return item;
}
```

**Important interview points:**

* the mutex protects the queue
* the condition variable avoids busy waiting
* always wait with a predicate / condition check
* wakeups can be spurious, so re-check the condition

---

### Pattern 6: Deadlock scenario

One of the most important interview patterns.

#### Unsafe version

```cpp
// Thread 1
lock(A);
lock(B);

// Thread 2
lock(B);
lock(A);
```

If Thread 1 gets `A` and Thread 2 gets `B`, both can wait forever.

#### How to explain deadlock

A deadlock happens when threads form a cycle of waiting and none can proceed.

#### Prevention methods

* always lock in a consistent global order
* keep lock scope small
* avoid nested locks when possible
* use deadlock-safe multi-lock utilities where available

#### Safer transfer example

```cpp
void transfer(Account& from, Account& to, int amount) {
    std::scoped_lock lock(from.mtx, to.mtx);
    from.balance -= amount;
    to.balance += amount;
}
```

**Interview point:**
Recognizing the deadlock risk is often more important than just writing the code.

---

### Pattern 7: Multiple resources and lock ordering

Suppose you must lock two objects.

Rule:

* always lock the lower id first
* or always lock `userMutex` before `accountMutex`

This simple policy prevents circular waiting.

**Interview line:**
“When multiple locks are required, define and document a strict lock acquisition order.”

---

### Pattern 8: Thread-safe singleton / lazy initialization

This appears often in interviews.

Unsafe:

```cpp
if (instance == nullptr) {
    instance = new Singleton();
}
```

Two threads can create two instances.

Safer general idea:

```cpp
std::mutex mtx;
Singleton* instance = nullptr;

Singleton* getInstance() {
    std::lock_guard<std::mutex> lock(mtx);
    if (instance == nullptr) {
        instance = new Singleton();
    }
    return instance;
}
```

**Interview discussion:**

* correct but may lock every time
* many languages provide safer built-in initialization patterns
* double-checked locking is tricky and depends on the language memory model

---

### Pattern 9: Shared cache / map

```cpp
std::unordered_map<std::string, std::string> cache;
std::mutex cacheMutex;

void put(const std::string& key, const std::string& value) {
    std::lock_guard<std::mutex> lock(cacheMutex);
    cache[key] = value;
}

bool get(const std::string& key, std::string& value) {
    std::lock_guard<std::mutex> lock(cacheMutex);
    auto it = cache.find(key);
    if (it == cache.end()) return false;
    value = it->second;
    return true;
}
```

**Interview point:**
Correct and simple, but read-heavy workloads may perform better with a read-write lock or sharding.

---

### Pattern 10: Avoid holding a lock while calling external code

Bad:

```cpp
std::lock_guard<std::mutex> lock(mtx);
callback();
```

This is risky because:

* callback may be slow
* callback may try to lock something else
* callback may call back into your code
* deadlock risk increases

Better:

```cpp
Data localCopy;
{
    std::lock_guard<std::mutex> lock(mtx);
    localCopy = sharedData;
}
callback(localCopy);
```

**Interview point:**
Do minimal work under lock. Copy what you need, unlock, then do expensive or unknown work.

---

## 4) The most asked interview questions and answer points

### Q1. What is a mutex?

A mutex is a synchronization primitive that ensures only one thread at a time can access a critical section.

### Q2. When do you use a mutex?

Use it when multiple threads access shared mutable data and at least one thread writes to it.

### Q3. What is a race condition?

A race condition occurs when correctness depends on thread timing or interleaving.

### Q4. What is a critical section?

The section of code that accesses shared state and must not be executed concurrently by multiple threads.

### Q5. What is deadlock?

Deadlock is when two or more threads wait forever for locks held by each other.

### Q6. How do you avoid deadlock?

* consistent lock ordering
* small critical sections
* avoid nested locking when possible
* use deadlock-safe helpers

### Q7. Mutex vs semaphore?

* **mutex**: one owner, mutual exclusion
* **semaphore**: counter/permits, can allow several threads

### Q8. Mutex vs atomic?

* **atomic**: best for simple single-variable operations
* **mutex**: best when multiple operations or multiple variables must stay consistent together

### Q9. Mutex vs spinlock?

* **mutex**: thread may sleep while waiting
* **spinlock**: thread actively spins; useful only for very short waits

### Q10. Why is manual lock/unlock risky?

Because early return, exception, or future code changes may skip `unlock()`.

---

## 5) Best practices

### Use RAII / scoped locking

Prefer:

```cpp
std::lock_guard<std::mutex> lock(mtx);
```

over manual `lock()` / `unlock()`.

### Keep critical sections small

Less time holding locks means:

* less contention
* better performance
* lower deadlock risk

### Protect shared state consistently

Every access that relies on a protected invariant should follow the same locking rule.

### Define what each mutex protects

Example:

* `balanceMutex` protects account balance
* `queueMutex` protects queue state
* `cacheMutex` protects cache map

### Document lock ordering when multiple locks exist

This is one of the highest-value habits in concurrent system design.

### Prefer simpler designs

Sometimes the best optimization is:

* thread-local data
* immutable data
* message passing
* atomics for simple counters/flags

---

## 6) Common mistakes

### Mistake 1: forgetting to unlock

```cpp
mtx.lock();
if (error) return; // bug: never unlocked
mtx.unlock();
```

### Mistake 2: holding lock too long

Large lock scope reduces concurrency.

### Mistake 3: accessing protected data without the lock

Even one unprotected access can break correctness.

### Mistake 4: using too many locks without a policy

This increases complexity and deadlock risk.

### Mistake 5: calling unknown or slow code while holding a lock

This can cause contention and deadlocks.

### Mistake 6: assuming mutex solves every concurrency issue

Mutex helps with mutual exclusion, but not automatically with fairness, ordering, or scalability.

---

## 7) Extra details worth knowing

### try_lock

Attempts to acquire the mutex without waiting forever.

```cpp
if (mtx.try_lock()) {
    // do work
    mtx.unlock();
}
```

Useful when you want to avoid blocking.

### Timed lock

Some mutex types allow timeout-based lock attempts.

### Recursive mutex

Allows the same thread to lock multiple times.
Use carefully; it can hide poor design.

### Starvation

A thread may wait too long because others keep acquiring the lock first.

### Livelock

Threads keep reacting to each other but still make no progress.

### Priority inversion

A high-priority thread waits for a lock held by a lower-priority thread.
Important in real-time systems.

### Read-write locks

Useful when reads are very frequent and writes are rare.

* many readers can proceed together
* writers need exclusive access

---

## 8) Quick revision sheet

### One-line definition

A mutex ensures only one thread at a time can access shared mutable state inside a critical section.

### When to use

Use a mutex when:

* data is shared
* at least one thread writes
* correctness depends on coordinated access

### Interview checklist

Ask:

1. What shared state exists?
2. What invariant must stay true?
3. Which operations must happen atomically together?
4. Could multiple locks create deadlock?
5. Can lock scope be reduced?

### High-value interview phrases

* “Protect the invariant, not just the statement.”
* “Keep critical sections as small as possible.”
* “Use scoped locking to guarantee unlock.”
* “Define a lock ordering policy to prevent deadlock.”
* “Choose atomics for simple single-variable updates, mutexes for larger invariants.”

---

## 9) Final memory map

### Most important topics first

1. mutex definition
2. race condition
3. critical section
4. scoped locking
5. check-then-update pattern
6. deadlock and lock ordering
7. producer-consumer with condition variable
8. mutex vs atomic / semaphore / spinlock

### Most important interview patterns

1. shared counter
2. bank withdrawal
3. thread-safe queue
4. producer-consumer
5. transfer between accounts
6. thread-safe singleton
7. thread-safe cache
8. logging from multiple threads

### Best summary sentence

A mutex is used to safely protect shared mutable state by ensuring only one thread at a time executes the critical section, but good design also requires careful lock scope, deadlock prevention, and consistent protection of invariants.
