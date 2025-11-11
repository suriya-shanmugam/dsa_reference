## 🔹 1. What Is a Heap?

A **heap** is a **binary tree-based data structure** where:

* Each parent node has a specific order relationship with its children.
* The **heap property** ensures that:

  * **Min-heap**: Parent ≤ children → smallest element is at the root.
  * **Max-heap**: Parent ≥ children → largest element is at the root.

Python’s `heapq` module implements a **min-heap** by default.

---

## 🔹 2. Why Use a Heap?

* Efficient **finding the smallest (or largest) element**: O(1)
* Efficient **inserting or removing elements**: O(log n)
* Common use cases:

  * Priority queues
  * Dijkstra’s algorithm / graph algorithms
  * Scheduling tasks
  * Sorting using heap sort

---

## 🔹 3. Importing `heapq`

```python
import heapq
```

---

## 🔹 4. Creating a Heap

### From a list:

```python
import heapq

nums = [5, 3, 8, 1, 2]
heapq.heapify(nums)  # transforms list into a heap
print(nums)  # e.g., [1, 2, 8, 5, 3] (heap property maintained)
```

> Note: The list is rearranged **in-place** to satisfy the heap property.
> The smallest element is always `nums[0]`.

---

## 🔹 5. Adding Elements

```python
heapq.heappush(nums, 0)
print(nums)  # smallest element is still at index 0
```

---

## 🔹 6. Removing the Smallest Element

```python
smallest = heapq.heappop(nums)
print(smallest)
print(nums)
```

> `heappop` removes and returns the **smallest element**.

---

## 🔹 7. Peek at Smallest Element

```python
print(nums[0])  # just access index 0
```

---

## 🔹 8. Push and Pop in One Step

```python
# push 4, pop smallest
smallest = heapq.heappushpop(nums, 4)
print(smallest, nums)
```

* Efficient: combines push & pop in O(log n)

---

## 🔹 9. Replace Smallest Element

```python
# Pop smallest, then push new value
heapq.heapreplace(nums, 6)
```

> Faster than heappop + heappush if you always replace the smallest.

---

## 🔹 10. Find n Largest or Smallest Elements

```python
nums = [5, 3, 8, 1, 2, 10]

import heapq
print(heapq.nlargest(3, nums))  # [10, 8, 5]
print(heapq.nsmallest(2, nums)) # [1, 2]
```

* Useful for top-k problems.

---

## 🔹 11. Using a Max-Heap

Python only has min-heap. To simulate a max-heap:

```python
nums = [5, 3, 8, 1]
max_heap = [-x for x in nums]
heapq.heapify(max_heap)

# Get max element
max_val = -heapq.heappop(max_heap)
print(max_val)  # 8
```

* Trick: store **negatives** to reverse ordering.

---

## 🔹 12. Heap vs Sorted List

| Operation        | List       | Heap       |
| ---------------- | ---------- | ---------- |
| Insert           | O(n)       | O(log n)   |
| Remove min       | O(n)       | O(log n)   |
| Find min         | O(1)       | O(1)       |
| Sort entire list | O(n log n) | O(n log n) |

* Heaps are **not for general random access**; they optimize **priority operations**.

---

## 🔹 13. Example: Priority Queue

```python
tasks = [(3, 'low'), (1, 'high'), (2, 'medium')]
heapq.heapify(tasks)

while tasks:
    priority, task = heapq.heappop(tasks)
    print(task, priority)
```

Output:

```
high 1
medium 2
low 3
```

* Tuples are compared by first element → natural priority queue behavior.

---

## 🔹 Summary of Key `heapq` Functions

| Function                  | Description                       |
| ------------------------- | --------------------------------- |
| `heapify(list)`           | Convert list to a heap (in-place) |
| `heappush(heap, item)`    | Add element to heap               |
| `heappop(heap)`           | Remove & return smallest element  |
| `heappushpop(heap, item)` | Push then pop smallest element    |
| `heapreplace(heap, item)` | Pop smallest then push new item   |
| `nlargest(n, iterable)`   | Return n largest elements         |
| `nsmallest(n, iterable)`  | Return n smallest elements        |

---

# Custom key in heap in python

---

## 🔹 1. The Problem

Python’s `heapq` **does not have a `key` parameter** like `sorted()` or `min()`.
Instead, you need to **structure your data so the heap compares the right element**.

---

## 🔹 2. Use Tuples `(priority, value)`

The standard way is to store each item as a tuple:

```python
import heapq

tasks = [
    ('write report', 3),   # priority 3
    ('urgent email', 1),   # priority 1
    ('meeting', 2)         # priority 2
]

# Use (priority, task) so heap uses priority
heapq.heapify([(p, t) for t, p in tasks])

pq = [(p, t) for t, p in tasks]
heapq.heapify(pq)

while pq:
    p, t = heapq.heappop(pq)
    print(t, p)
```

**Output:**

```
urgent email 1
meeting 2
write report 3
```

✅ Key idea: the **heap compares the first element** of each tuple.

---

## 🔹 3. Using `NamedTuple` or `dataclass` for Clarity

For more readable code, you can use `dataclass` or `namedtuple`:

```python
from dataclasses import dataclass, field
import heapq

@dataclass(order=True)
class Task:
    priority: int
    name: str = field(compare=False)

tasks = [Task(3, 'write report'), Task(1, 'urgent email'), Task(2, 'meeting')]
heapq.heapify(tasks)

while tasks:
    t = heapq.heappop(tasks)
    print(t.name, t.priority)
```

**Output:**

```
urgent email 1
meeting 2
write report 3
```

✅ `order=True` makes `Task` objects **comparable by `priority`**, ignoring `name`.

---

## 🔹 4. Max-Heap with Custom Key

Min-heap is default, but you can invert the key to simulate max-heap:

```python
tasks = [('write report', 3), ('urgent email', 1), ('meeting', 2)]
pq = [(-p, t) for t, p in tasks]  # negate priority
heapq.heapify(pq)

while pq:
    p, t = heapq.heappop(pq)
    print(t, -p)
```

**Output (highest priority first):**

```
write report 3
meeting 2
urgent email 1
```

---

## 🔹 5. Using a Function as Key

Python’s `heapq` doesn’t take a `key` parameter directly, but you can **precompute the key**:

```python
# Suppose we want to prioritize by string length
words = ['apple', 'banana', 'kiwi', 'grape']
pq = [(len(word), word) for word in words]
heapq.heapify(pq)

while pq:
    length, word = heapq.heappop(pq)
    print(word, length)
```

**Output:**

```
kiwi 4
grape 5
apple 5
banana 6
```

✅ Key idea: always **push `(key, value)` into the heap**, then pop and access the value.

---

### 🔹 Summary

* **Heap compares the first element** of tuples or comparable objects.
* For custom keys, push **(key, value)** into the heap.
* Use `dataclass(order=True)` or `namedtuple` for clarity.
* For max-heap, **negate the key**.

---
