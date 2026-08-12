The core idea behind a **monotonic clock** is simple:

> **Measure the passage of time, not the current time.**

Think of it as a stopwatch rather than a wall clock.

### Wall clock (`time.time()`)

A wall clock answers:

> "What time is it right now?"

For example:

```text
10:15:30 AM
10:15:31 AM
10:15:32 AM
```

But someone can change it:

```text
10:15:32 AM
10:10:00 AM   <-- clock adjusted backward
10:10:01 AM
```

This is fine for telling the time, but bad for measuring durations.

---

### Monotonic clock

A monotonic clock answers:

> "How much time has passed since I started counting?"

It doesn't care about dates or time zones.

Imagine an internal counter:

```text
0.000
0.001
0.002
...
5234.125
5234.126
5234.127
```

It **never decreases**.

Even if the system time changes from:

```text
10:30 AM
```

to

```text
9:45 AM
```

the monotonic clock continues:

```text
5234.127
5234.128
5234.129
```

---

## Where does it come from?

Modern operating systems maintain **multiple clocks**.

For example:

* **Real-time clock** → current date and time (used by `time.time()`)
* **Monotonic clock** → elapsed time since boot or another fixed reference (used by `time.monotonic()`)

On Linux, for example:

```c
clock_gettime(CLOCK_MONOTONIC, ...)
```

returns time from a kernel-maintained monotonic timer.

The "zero" point is arbitrary—often when the system booted—but you don't need to know it because only differences between readings matter.

---

## Why not use the wall clock internally?

Suppose you're implementing a 5-second timeout.

Using the wall clock:

```text
Start = 10:00:00
```

After 2 seconds, the system clock is corrected backward by 30 seconds:

```text
Current = 09:59:32
```

Elapsed:

```text
09:59:32 - 10:00:00 = -28 seconds
```

Your timeout logic breaks.

With a monotonic clock:

```text
Start = 1050.0
Current = 1052.0
```

Elapsed:

```text
2.0 seconds
```

No matter what happens to the wall clock, the elapsed time is correct.

---

## An analogy

Imagine running a marathon.

### Wall clock

You're checking the clock on a building.

```
9:00
9:05
8:58   <-- someone changed it
9:06
```

You can't reliably determine how long you've been running.

### Monotonic clock

You start a stopwatch when the race begins.

```
0 s
5 s
10 s
15 s
```

No one can reset it while you're running.

That's exactly what a monotonic clock is: **a stopwatch maintained by the operating system**.

---

### Summary

* **`time.time()`**: "What is the current date and time?"
* **`time.monotonic()`**: "How much time has elapsed?"

That's why systems like **rate limiters, schedulers, retry mechanisms, locks, cache expiration checks, and networking timeouts** almost always use a monotonic clock: they care about **elapsed intervals**, not the current calendar time.


### Distributed system
Yes. This is one of the **limitations of a monotonic clock**. It is excellent for measuring elapsed time **within the lifetime of a running system**, but it is **not suitable for persistent timestamps**.

### 1. System restart

On most operating systems, the monotonic clock starts from a new reference point after reboot (often close to zero).

For example:

```text
Before reboot:
time.monotonic() = 152340.5
```

After reboot:

```text
time.monotonic() = 3.2
```

Suppose you persisted:

```python
last_refill = 152340.5
```

After restart:

```python
elapsed = 3.2 - 152340.5
```

which is a huge negative number, making your rate limiter incorrect.

So **never persist (`serialize`) values returned by `time.monotonic()`**.

---

### 2. Serialization / Deserialization

Similarly, if you serialize an object:

```python
{
    "tokens": 15,
    "last_refill": 98342.18   # monotonic time
}
```

and restore it later (or on another machine), that value has no meaning.

Each machine has its own monotonic clock:

```
Machine A:
monotonic = 98342

Machine B:
monotonic = 512
```

They are unrelated.

---

### 3. Distributed systems

Imagine a Redis-backed token bucket.

Server A:

```
monotonic = 2500
```

stores

```
last_refill = 2500
```

Later Server B reads it.

Its monotonic clock is

```
monotonic = 180
```

Now

```python
elapsed = 180 - 2500
```

is meaningless.

This is why **monotonic clocks cannot be shared across processes or machines**.

---

## What should you do instead?

It depends on where the state lives.

### In-memory rate limiter (single process)

Use `time.monotonic()`.

```python
tokens
last_refill_monotonic
```

This is the recommended approach.

---

### Persistent or distributed rate limiter

Use wall-clock time (`time.time()`) or store an absolute timestamp.

For example:

```python
{
    "tokens": 15,
    "last_refill": 1722078100.42
}
```

After restart:

```python
elapsed = time.time() - last_refill
```

This works because both values refer to the same real-world timeline.

The trade-off is that wall-clock adjustments (e.g., NTP corrections) can affect elapsed-time calculations. Many distributed systems accept this because persistence and interoperability are more important.

---

## How production systems handle this

* **Local in-memory caches, schedulers, and rate limiters:** `time.monotonic()`
* **Redis/database-backed rate limiters:** wall-clock timestamps or the datastore's own time source (for example, Redis provides a `TIME` command so all clients use a consistent clock).

### Rule of thumb

* ✅ `time.monotonic()` → ephemeral state that stays within one running process.
* ❌ Do not serialize or transmit monotonic timestamps.
* ✅ `time.time()` (or another shared wall-clock source) → state that must survive restarts or be shared across machines.
