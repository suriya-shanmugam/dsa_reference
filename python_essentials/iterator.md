## 🔹 What Is an *Iterable*?

An **iterable** is any Python object capable of returning its elements **one at a time**, so you can loop over it with a `for` loop or pass it to functions like `list()`, `sum()`, or `sorted()`.

Common examples of iterables:

```python
[1, 2, 3]             # list
(1, 2, 3)             # tuple
"hello"               # string
{1, 2, 3}             # set
{'a': 1, 'b': 2}      # dict (iterates over keys)
range(5)              # range object
open('file.txt')      # file object (line by line)
```

---

## 🔹 How to Check if Something Is Iterable

You can check this by importing from `collections.abc`:

```python
from collections.abc import Iterable

isinstance([1, 2, 3], Iterable)   # ✅ True
isinstance(10, Iterable)          # ❌ False
```

---

## 🔹 Iterable vs Iterator

These are *related but different* concepts.

| Term         | Description                                 | How to Get It    | Key Method                             |
| ------------ | ------------------------------------------- | ---------------- | -------------------------------------- |
| **Iterable** | Can return an iterator (can be looped over) | e.g. `range(5)`  | Has `__iter__()`                       |
| **Iterator** | Produces items one at a time                | `iter(iterable)` | Has both `__iter__()` and `__next__()` |

### Example:

```python
nums = [1, 2, 3]         # iterable
it = iter(nums)          # iterator created from iterable

next(it)  # 1
next(it)  # 2
next(it)  # 3
next(it)  # raises StopIteration
```

→ The **iterator** “remembers” its position.
→ The **iterable** can make *new* iterators each time you loop.

---

## 🔹 The Iterator Protocol

This is how `for` loops and many built-ins work internally.

An object is **iterable** if:

* It has a method `__iter__()` that returns an **iterator**.

An object is an **iterator** if:

* It has a method `__next__()` that returns the next value.
* When no more items, `__next__()` raises `StopIteration`.

---

## 🔹 How `for` Loops Work Internally

This:

```python
for x in [1, 2, 3]:
    print(x)
```

Is roughly equivalent to:

```python
nums = [1, 2, 3]
it = iter(nums)
while True:
    try:
        x = next(it)
        print(x)
    except StopIteration:
        break
```

---

## 🔹 Common Iterable-Building Tools

### 1. **range()**

A lazy, iterable sequence of integers.

### 2. **Generators**

Functions or expressions that yield values one at a time.

```python
def countdown(n):
    while n > 0:
        yield n
        n -= 1
```

→ `countdown(5)` is an *iterator*.

### 3. **Generator Expressions**

Compact syntax:

```python
squares = (x*x for x in range(5))
```

→ Also returns an *iterator*.

### 4. **Comprehensions**

Lists, sets, dicts — they *create* new iterables:

```python
[x*x for x in range(5)]    # list comprehension
{x*x for x in range(5)}    # set comprehension
{x: x*x for x in range(5)} # dict comprehension
```

---

## 🔹 Key Built-in Functions for Iterables

| Function                          | Description                        |
| --------------------------------- | ---------------------------------- |
| `iter(obj)`                       | Get an iterator from an iterable   |
| `next(it)`                        | Get the next item from an iterator |
| `enumerate(iterable)`             | Pairs index with item              |
| `zip(a, b)`                       | Combines multiple iterables        |
| `map(func, iterable)`             | Applies a function lazily          |
| `filter(func, iterable)`          | Keeps elements passing a test      |
| `sorted(iterable)`                | Returns a new sorted list          |
| `any(iterable)` / `all(iterable)` | Check boolean conditions           |

---

## 🔹 Lazy vs Eager Iterables

* **Eager**: Builds all elements in memory (e.g., `list`, `tuple`, `set`)
* **Lazy**: Produces items on demand (e.g., `range`, `map`, `zip`, generators)

Lazy iterables are memory-efficient for large data streams.

---

## 🔹 Summary Diagram

```
Iterable
 ├── has __iter__() → returns Iterator
 │
 Iterator
 ├── has __next__() → returns next item
 └── raises StopIteration when done
```

---
