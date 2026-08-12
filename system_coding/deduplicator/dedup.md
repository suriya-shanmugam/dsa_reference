This is a common **system design / coding interview** problem. The short description gives hints about the expected data structures.

## Problem Explanation

You need to build a **Recent Event Deduplicator**.

The system receives a stream of events (such as user IDs, request IDs, or message IDs). If the **same event appears again within a recent time window**, it should be treated as a duplicate. If it hasn't appeared recently, it should be accepted.

The challenge is to perform this efficiently.

---

## Example Problem Statement

> Design a data structure that accepts events one by one. Return `true` if the event has **not occurred within the last K events** (or within a recent time window), otherwise return `false`.

Only recent events matter. Older events are forgotten.

---

## Input

Suppose the window size is:

```text
K = 3
```

Incoming events:

```text
A
B
C
A
D
A
```

---

## Output

```text
true
true
true
false
true
true
```

---

## Why?

Let's process one event at a time.

| Event | Recent Window | Duplicate?                                   | Output |
| ----- | ------------- | -------------------------------------------- | ------ |
| A     | A             | No                                           | true   |
| B     | A B           | No                                           | true   |
| C     | A B C         | No                                           | true   |
| A     | A B C         | Yes                                          | false  |
| D     | B C D         | No (A was removed after the window advanced) | true   |
| A     | C D A         | No                                           | true   |

Notice that after processing `D`, the oldest event (`A`) leaves the window, so a later `A` is accepted again.

---

## Why use a Hash Set + Deque?

### 1. Hash Set

Stores all events currently in the window.

Example:

```text
{A, B, C}
```

Purpose:

* Check if an event already exists.
* Lookup is **O(1)** on average.

---

### 2. Deque (Double-ended Queue)

Stores events in the order they arrived.

```text
Front               Back

A  B  C
```

When the window becomes too large:

Remove from the front.

```text
Remove A

B  C
```

Also remove `A` from the hash set.

---

## Sliding Window

The "window" means we only remember the last `K` events.

For `K = 3`:

```text
A B C
```

Next event:

```text
B C D
```

Next:

```text
C D E
```

The window keeps sliding forward.

---

## Algorithm

For every new event:

1. Check if it exists in the hash set.

   * Yes → return `false` (duplicate).
   * No → continue.
2. Insert it into:

   * hash set
   * back of deque
3. If deque size exceeds `K`:

   * remove the front element
   * remove the same element from the hash set
4. Return `true`.

---

## Why is it Amortized O(1)?

Each event is:

* inserted into the deque once,
* removed from the deque once,
* inserted into the hash set once,
* removed from the hash set once.

Each of these operations is **O(1)** on average, so although removals happen as the window advances, each event incurs only a constant amount of work over its lifetime. Therefore, the average time per processed event is **amortized O(1)**.

---

### Summary

* **Problem:** Detect duplicates among only the most recent `K` events.
* **Input:** A stream of events and a window size `K`.
* **Output:** `true` if the event is new within the current window, `false` if it is a recent duplicate.
* **Data structures:**

  * **Hash Set** → fast duplicate checks.
  * **Deque** → efficiently remove the oldest event when the window slides.
* **Time Complexity:** Amortized **O(1)** per event.
* **Space Complexity:** **O(K)**, since only the last `K` events are stored.
