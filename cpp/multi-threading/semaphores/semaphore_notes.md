# Semaphore 

A semaphore is a counter that controls how many threads are allowed to proceed.

* `acquire()` takes one permit
* `release()` returns one permit
* if no permit is available, `acquire()` blocks

In C++20, semaphores are in `<semaphore>`.

```cpp
#include <semaphore>
```

There are two common kinds:

* `std::binary_semaphore` → only 0 or 1 permit
* `std::counting_semaphore` → multiple permits

---

# 1. Binary semaphore

A binary semaphore acts like a gate with only two states:

* closed (`0`)
* open (`1`)

It is commonly used for **signaling**.

## Example: wait until initialization finishes

```cpp
#include <iostream>
#include <thread>
#include <semaphore>

std::binary_semaphore ready(0);

void initialize_system() {
    std::cout << "Initializing...\n";
    std::this_thread::sleep_for(std::chrono::seconds(2));
    std::cout << "Initialization complete\n";
    ready.release();   // signal completion
}

void worker() {
    std::cout << "Worker waiting for system...\n";
    ready.acquire();   // wait until ready
    std::cout << "Worker starts working\n";
}
```

## Use case

A worker thread should not begin until another thread finishes setup.

Examples:

* network service waits for config load
* processing thread waits for camera/device startup
* background task waits for cache warmup

## Note

A binary semaphore is very useful when one thread says:
**“Don’t continue until I tell you.”**

---

# 2. Counting semaphore

A counting semaphore allows more than one thread to proceed at the same time.

## Example: only 3 threads may use a resource

```cpp
#include <iostream>
#include <thread>
#include <vector>
#include <semaphore>
#include <chrono>

std::counting_semaphore<3> slots(3);

void task(int id) {
    slots.acquire();   // take one slot
    std::cout << "Task " << id << " entered\n";

    std::this_thread::sleep_for(std::chrono::seconds(1));

    std::cout << "Task " << id << " leaving\n";
    slots.release();   // return slot
}
```

## Use case

You have a limited number of identical resources.

Examples:

* only 10 DB connections exist
* only 4 file downloads at once
* only 2 GPU jobs in parallel
* only 8 requests to an API at once

## Note

This is the most common semaphore use:
**limiting concurrency**.

---

# Most useful semaphore patterns

## 1. One-time signal

One thread waits for another to finish something.

## Example

```cpp
#include <iostream>
#include <thread>
#include <semaphore>

std::binary_semaphore done(0);

void producer() {
    std::cout << "Preparing data...\n";
    done.release();
}

void consumer() {
    done.acquire();
    std::cout << "Data is ready, consuming now\n";
}
```

## Use cases

* startup sequencing
* handoff between threads
* “notify me when finished”

## Notes

* Start semaphore with `0` when you want waiting initially
* `release()` means “event happened”
* `acquire()` means “wait for event”

---

## 2. Limit concurrent work

Allow up to `N` threads into some section.

## Example

```cpp
#include <iostream>
#include <thread>
#include <vector>
#include <semaphore>
#include <chrono>

std::counting_semaphore<2> workers(2);

void process(int id) {
    workers.acquire();
    std::cout << "Processing " << id << "\n";

    std::this_thread::sleep_for(std::chrono::milliseconds(800));

    std::cout << "Finished " << id << "\n";
    workers.release();
}
```

## Use cases

* rate limiting
* connection pools
* bounded parallelism
* preventing CPU or memory overload

## Notes

Without a semaphore, launching many threads can overload the system.
A semaphore makes the limit explicit.

---

## 3. Resource pool

Each permit represents one real resource.

## Example: 5 printers, connections, or devices

```cpp
#include <semaphore>

std::counting_semaphore<5> resources(5);

void use_resource() {
    resources.acquire();   // reserve one resource

    // use the resource

    resources.release();   // return it
}
```

## Use cases

* database connections
* printers
* sockets
* hardware channels
* reusable buffers

## Notes

This pattern works best when:

* all resources are equivalent
* you only care about how many are free

Each semaphore permit means:
**“one instance is available.”**

---

## 4. Producer-consumer coordination

Semaphores are very useful when one thread produces items and another consumes them.

A common setup:

* one semaphore counts empty slots
* one semaphore counts full slots

## Example: bounded queue logic

```cpp
#include <iostream>
#include <queue>
#include <mutex>
#include <thread>
#include <semaphore>

constexpr int CAPACITY = 3;

std::queue<int> q;
std::mutex q_mutex;

std::counting_semaphore<CAPACITY> empty_slots(CAPACITY);
std::counting_semaphore<CAPACITY> full_slots(0);

void producer() {
    for (int i = 1; i <= 5; ++i) {
        empty_slots.acquire();   // wait for free space

        {
            std::lock_guard<std::mutex> lock(q_mutex);
            q.push(i);
            std::cout << "Produced " << i << "\n";
        }

        full_slots.release();    // signal item available
    }
}

void consumer() {
    for (int i = 1; i <= 5; ++i) {
        full_slots.acquire();    // wait for available item

        int value;
        {
            std::lock_guard<std::mutex> lock(q_mutex);
            value = q.front();
            q.pop();
            std::cout << "Consumed " << value << "\n";
        }

        empty_slots.release();   // signal free space
    }
}
```

## Use cases

* job queues
* task pipelines
* message passing
* packet buffering
* streaming systems

## Notes

Semaphores track **how many items or slots exist**.
They do not automatically protect the queue itself, so shared structures still need safe access.

---

## 5. Gate / turnstile

Threads wait behind a closed gate. When someone opens it, they can pass.

## Example

```cpp
#include <iostream>
#include <thread>
#include <vector>
#include <semaphore>

std::binary_semaphore gate(0);

void worker(int id) {
    gate.acquire();
    gate.release();  // allow next waiting thread through
    std::cout << "Worker " << id << " passed gate\n";
}
```

## Use cases

* release a batch of waiting workers
* pause execution until an external event happens
* staged startup

## Notes

This is a useful building block for more advanced synchronization designs.

---

## 6. Batch release

A semaphore can wake multiple waiting threads by releasing more than one permit.

## Example

```cpp
#include <semaphore>

std::counting_semaphore<10> sem(0);

// later
sem.release(3);   // allow three waiting threads to continue
```

## Use cases

* open 3 worker slots at once
* add a batch of resources
* signal arrival of multiple items

## Notes

This is helpful when permits appear in groups instead of one at a time.

---

# Clear real-world use cases

## A. Database connection pool

Suppose only 10 DB connections are allowed.

```cpp
std::counting_semaphore<10> db_connections(10);
```

Each request handler:

* acquires one connection permit
* uses DB
* releases permit

### Why semaphore fits

You do not want exclusive access by one thread.
You want **up to 10 concurrent users**.

---

## B. Download manager

Suppose your app allows only 4 simultaneous downloads.

```cpp
std::counting_semaphore<4> download_slots(4);
```

Each download task must acquire a slot before starting.

### Why semaphore fits

You are controlling concurrency, not ownership of one object.

---

## C. Service startup dependency

The processing thread must wait for the service thread to finish setup.

```cpp
std::binary_semaphore ready(0);
```

### Why semaphore fits

This is a simple signal:
“wait until ready.”

---

## D. Bounded queue

The queue should never exceed capacity 100.

```cpp
std::counting_semaphore<100> empty_slots(100);
std::counting_semaphore<100> full_slots(0);
```

### Why semaphore fits

Semaphores model counts naturally:

* how many spaces remain
* how many items exist

---

## E. Limiting expensive work

Suppose image processing is memory-heavy, and running too many in parallel crashes performance.

```cpp
std::counting_semaphore<2> image_jobs(2);
```

### Why semaphore fits

Only 2 jobs may run at once.

---

# Notes that matter in practice

## 1. Initial value is the key design choice

The starting count defines the initial state.

### Examples

```cpp
std::binary_semaphore sem1(0);   // closed, threads wait
std::binary_semaphore sem2(1);   // open, one thread can pass

std::counting_semaphore<5> pool(5); // 5 permits available
std::counting_semaphore<5> none(0); // nobody can proceed yet
```

Think of the initial value as:
**“how many passes are already available?”**

---

## 2. `release()` can happen before `acquire()`

This is one of the most useful properties.

If a thread releases first, the permit is stored.
A later acquire can use it immediately.

## Example

```cpp
std::binary_semaphore signal(0);

signal.release();   // event happens early
signal.acquire();   // later: proceeds immediately
```

## Why this matters

Semaphores remember signals.
That makes them good for event-style coordination.

---

## 3. A semaphore does not identify ownership

Any thread can release a semaphore permit.

That is different from lock-style ownership ideas.

## Example use

* thread A waits
* thread B signals
* thread C may later signal again

This is normal for semaphores.

---

## 4. Always pair acquire and release correctly

If you acquire and forget to release, permits leak away.

## Example problem

```cpp
sem.acquire();
// forgot sem.release();
```

Eventually every thread blocks forever.

## Practical note

This is one of the biggest semaphore bugs.

---

## 5. Over-releasing is also a bug

If a semaphore represents 3 resources, calling `release()` too many times creates fake permits.

## Example problem

```cpp
std::counting_semaphore<3> sem(3);

// bad: releases without a matching acquire
sem.release();
```

Now the program thinks more resources exist than actually do.

---

## 6. Semaphore count models quantity, not data safety

A semaphore controls **how many** threads proceed.
It does not automatically protect shared objects.

If multiple threads modify the same structure, you still need safe coordination around that structure.

---

## 7. Timeouts are often useful

Sometimes you do not want to wait forever.

## Example

```cpp
if (sem.try_acquire_for(std::chrono::seconds(2))) {
    // got permit
} else {
    // timed out
}
```

## Use cases

* fail fast if pool is exhausted
* avoid hanging forever
* implement graceful degradation

---

## 8. Binary semaphore is not just “tiny counting semaphore” in design terms

Although conceptually related, you usually choose:

* binary semaphore for signaling/gating
* counting semaphore for resource counts

This design distinction makes code easier to understand.

---

# Minimal complete example

Here is a compact, clear semaphore example.

## Example: only 2 threads may run a section at once

```cpp
#include <iostream>
#include <thread>
#include <vector>
#include <semaphore>
#include <chrono>

std::counting_semaphore<2> sem(2);

void worker(int id) {
    std::cout << "Worker " << id << " waiting\n";
    sem.acquire();

    std::cout << "Worker " << id << " entered\n";
    std::this_thread::sleep_for(std::chrono::seconds(1));
    std::cout << "Worker " << id << " leaving\n";

    sem.release();
}

int main() {
    std::vector<std::thread> threads;

    for (int i = 1; i <= 5; ++i) {
        threads.emplace_back(worker, i);
    }

    for (auto& t : threads) {
        t.join();
    }
}
```

## What happens

* workers 1 and 2 enter first
* workers 3, 4, 5 wait
* each time one leaves, one waiting worker enters

This is the simplest strong mental model for a semaphore.

---

# Good ways to think about semaphores

## Model 1: tickets

Each permit is a ticket.
A thread must get a ticket to proceed.

## Model 2: parking spaces

Each permit is one free parking slot.
If all spaces are used, incoming cars wait.

## Model 3: stored signals

Each `release()` adds one “go ahead” signal.
Each `acquire()` consumes one.

These three models explain most semaphore behavior.

---

# When semaphores are especially useful

Use semaphores when the problem is naturally one of:

* available slots
* available resources
* maximum concurrency
* event signals
* producer/consumer counts
* gating or staged execution

A semaphore is strongest when the question is:

**“How many threads should be allowed through?”**

---

# Summary

Semaphores are best understood as permit counters.

The most practical semaphore uses are:

* **binary semaphore** for signaling or waiting for an event
* **counting semaphore** for limiting concurrency
* resource pools
* producer-consumer coordination
* gates and staged release of threads

The clearest real applications are:

* DB connection pools
* download limits
* worker throttling
* bounded queues
* startup synchronization
* controlling expensive jobs

The most important practical notes are:

* choose the initial count carefully
* always balance `acquire()` and `release()`
* semaphores remember permits
* semaphores control quantity, not data correctness
* use them when the problem is naturally “number of available passes”
