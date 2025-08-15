# Python Lists & Arrays — Industry Cheat Sheet

> Fast, practical notes on core techniques, handy methods/APIs, and the most common real‑world scenarios.

---

## 0) Quick Reference

- **List literal**: `a = [1, 2, 3]`
- **Common libs**: `itertools`, `heapq`, `bisect`, `collections`, `array`, `random`
- **Type hints**: `from typing import List, Iterable, Sequence, MutableSequence`
- **Time complexity** (amortized): append O(1), pop-end O(1), pop-front O(n), insert O(n), get/set O(1), contains O(n), sort O(n log n)

---

## 1) Core List Operations

### Creation

```python
lst = []
lst = [0] * 10          # pre-size with same element
lst = list(range(5))
lst = list(iterable)    # from any iterable
```

### Access & Update

```python
x = lst[i]               # get
lst[i] = value           # set
lst[i:j:k]               # slicing with step
lst[i:j] = other_list    # splice (replace slice)
```

### Adding & Removing

```python
lst.append(x)            # O(1) amortized
lst.extend([a, b])       # bulk add
lst += [a, b]
lst.insert(idx, x)       # O(n)

lst.pop()                # remove & return last
lst.pop(i)               # remove by index
lst.remove(value)        # remove first matching value

# Fast remove without order guarantee (common trick)
lst[i] = lst[-1]; lst.pop()
```

### Common Queries

```python
len(lst)
x in lst                 # linear search
lst.count(x)
lst.index(x)            # first index or ValueError
min(lst), max(lst), sum(lst)
```

### Copying

```python
lst_copy = lst[:]        # shallow copy
lst_copy = list(lst)
import copy
lst_deep = copy.deepcopy(lst)
```

### Sorting

```python
lst.sort()                               # in-place, stable
lst.sort(key=lambda x: x.score, reverse=True)
new_sorted = sorted(lst, key=str.lower)
```

**Stable multi-key sort**:

```python
# sort by last name, then first name
people.sort(key=lambda p: (p.last, p.first))
```

### Reversing & Rotating

```python
lst.reverse()                             # in-place
rev = lst[::-1]                           # copy reversed

# rotate right by k (simple)
k %j= len(lst)
lst[:] = lst[-k:] + lst[:-k]
```

---

## 2) Slicing, Comprehensions, and Idioms

### Slicing Patterns

```python
head, *middle, tail = lst                 # unpack with remainder
first3 = lst[:3]
rest = lst[3:]
step2 = lst[::2]
last3 = lst[-3:]
```

### List Comprehensions

```python
squares = [x*x for x in lst]
filtered = [x for x in lst if x % 2 == 0]
composed = [f(g(x)) for x in items if predicate(x)]
```

### Handy Idioms

```python
# flatten one level
flat = [y for x in matrix for y in x]

# unique while preserving order
seen = set()
unique = [x for x in lst if not (x in seen or seen.add(x))]

# chunk into fixed sizes
chunks = [lst[i:i+n] for i in range(0, len(lst), n)]

# sliding window (size k)
windows = [lst[i:i+k] for i in range(len(lst)-k+1)]
```

---

## 3) Searching & Insertion (bisect)

Use `bisect` for **sorted lists**.

```python
import bisect
idx = bisect.bisect_left(a, x)    # first position to insert x
bisect.insort_left(a, x)          # insert keeping a sorted
```

**Binary search membership**:

```python
import bisect
idx = bisect.bisect_left(a, target)
found = idx < len(a) and a[idx] == target
```

---

## 4) Heaps (Priority Queues)

`heapq` maintains a **min-heap** in a list.

```python
import heapq
h = []
heapq.heappush(h, item)
smallest = heapq.heappop(h)
peek = h[0]
```

**Max-heap** trick:

```python
heapq.heappush(h, -x); -heapq.heappop(h)
```

**Top‑K**:

```python
import heapq
# K largest / smallest efficiently
heapq.nlargest(K, data, key=score)
heapq.nsmallest(K, data, key=score)
```

**Streaming median** (two heaps): maintain max-heap for lower half (negated) and min-heap for upper; rebalance sizes.

---

## 5) Deques (Fast ends)

For frequent **front** operations, prefer `collections.deque`.

```python
from collections import deque
q = deque([1,2,3])
q.append(4); q.appendleft(0)
q.pop(); q.popleft()
q.rotate(1)       # right rotate
```

---

## 6) Counting & Grouping

### Frequencies

```python
from collections import Counter
cnt = Counter(lst)
common = cnt.most_common(10)
```

### Group consecutive items

```python
import itertools as it
for key, group in it.groupby(lst):
    block = list(group)
```

### Group by key function (not just consecutive)

```python
from collections import defaultdict
by_key = defaultdict(list)
for x in items:
    by_key[keyfunc(x)].append(x)
```

---

## 7) Functional Tools (map/zip/itertools)

```python
mapped = list(map(f, lst))
paired = list(zip(a, b))

import itertools as it
acc = list(it.accumulate(nums))
# permutations, combinations, product
perms = list(it.permutations(lst, r=3))
```

**Unzip**:

```python
xs, ys = map(list, zip(*pairs))
```

---

## :8) In‑place vs Copy (Performance & Safety)

- `list.sort()` and `list.reverse()` are **in‑place**.
- Slicing like `lst[::-1]` or `sorted(lst)` returns **copies**.
- Large lists: avoid accidental copies in hot paths. Use iterators or `deque`.
- Beware aliasing: `grid = [[0]*m]*n` duplicates **references**; use `[[0 for _ in range(m)] for _ in range(n)]`.

---

## 9) Randomization & Sampling

```python
import random
random.shuffle(lst)          # in-place
sample = random.sample(lst, k)
choice = random.choice(lst)
```

**Reservoir sampling** for single pass unknown size:

```python
import random
picked = None
for i, x in enumerate(stream, 1):
    if random.randrange(i) == 0:
        picked = x
```

---

## 10) Memory‑Efficient Numeric Arrays

When you need dense numeric storage:

### `array` module (homogeneous types)

```python
from array import array
arr = array('i', [1, 2, 3])   # 'i' int, 'f' float, 'd' double, etc.
arr.append(4); arr[0]
```

### `bytearray` + `memoryview` (I/O, protocols)

```python
buf = bytearray(b"hello")
view = memoryview(buf)
view[0] = ord('H')
```

### `numpy` (industry‑standard for numeric ops)

- Vectorized operations, broadcasting, slicing views (no copy).

```python
import numpy as np
x = np.array([1,2,3], dtype=np.int32)
y = x * 2         # vectorized
sub = x[1:]       # view, not copy (usually)
```

> Rule of thumb: Python lists for mixed/low‑volume logic; NumPy arrays for large numeric compute; `array/bytearray` for compact binary data.

---

## 11) Common Real‑World Scenarios

### 11.1 Top‑K, Leaderboards

```python
import heapq
leaders = heapq.nlargest(100, users, key=lambda u: u.score)
```

### 11.2 Deduplicate while preserving order

```python
seen = set()
out = []
for x in lst:
    if x not in seen:
        seen.add(x); out.append(x)
```

### 11.3 Merge K sorted lists

```python
import heapq
h = []
for i, it in enumerate(iters):
    first = next(it, None)
    if first is not None:
        heapq.heappush(h, (first, i))

out = []
while h:
    val, i = heapq.heappop(h)
    out.append(val)
    nxt = next(iters[i], None)
    if nxt is not None:
        heapq.heappush(h, (nxt, i))
```

### 11.4 Sliding window sum/avg

```python
from collections import deque
window, s = deque(), 0
for x in stream:
    window.append(x); s += x
    if len(window) > k:
        s -= window.popleft()
    avg = s / len(window)
```

### 11.5 Partition by predicate (stable)

```python
true_side = [x for x in lst if pred(x)]
false_side = [x for x in lst if not pred(x)]
lst = true_side + false_side
```

### 11.6 Stable grouping sort (e.g., status buckets)

```python
order = {"critical": 0, "high": 1, "medium": 2, "low": 3}
items.sort(key=lambda x: order.get(x.severity, 99))
```

### 11.7 Two‑pointer patterns

```python
# remove duplicates from sorted list in-place (return new length)
write = 0
for read in range(len(a)):
    if write == 0 or a[read] != a[write-1]:
        a[write] = a[read]
        write += 1
# a[:write] is deduped
```

### 11.8 Stable pagination & batching

```python
page = items[offset:offset+limit]
```

### 11.9 Top‑N per group

```python
from collections import defaultdict
import heapq
buckets: dict[str, list] = defaultdict(list)
for item in items:
    h = buckets[item.group]
    if len(h) < N:
        heapq.heappush(h, (item.score, item))
    else:
        heapq.heappushpop(h, (item.score, item))
```

### 11.10 Find first/last matching index

```python
# first True via bisect on bool key over sorted data
import bisect
idx = bisect.bisect_left(data, True, key=pred)  # Python 3.10+: use custom wrapper
```

---

## 12) Pitfalls & Gotchas

- `list * n` duplicates references for nested lists.
- `list.remove(x)` removes **first** occurrence only.
- `sort()` errors if elements are incomparable (e.g., `int` vs `str`). Provide `key`.
- `pop(0)` is O(n); use `deque`.
- Slicing creates copies (costly for big lists).
- Mutating while iterating can skip elements; iterate over a copy or build a new list.

---

## 13) Interfaces & Protocols to Know

- `Iterable`, `Iterator`, `Sequence`, `MutableSequence` (from `collections.abc`)
- Duck‑typing: any object implementing `__len__`, `__getitem__` is indexable/sequence-like.
- Magic methods: `__iter__`, `__contains__`, `__reversed__`, `__mul__`/`__rmul__`, `__add__` (concat).

---

## 14) Testing & Quality

- Property tests for idempotence (e.g., sort then stable key re-sort).
- Fuzz with random inputs; check invariants (lengths, element equality ignoring order when expected).
- Benchmark with `timeit` when choosing between patterns.

---

## 15) Quick Recipes (copy‑paste)

**Flatten deeply nested (small depth)**

```python
import itertools as it
flatten = list(it.chain.from_iterable(matrix))
```

**K-way intersection preserving order of first list**

```python
allowed = set(b)
out = [x for x in a if x in allowed]
```

**Stable, case‑insensitive unique emails**

```python
seen = set()
uniq = []
for e in emails:
    k = e.strip().lower()
    if k not in seen:
        seen.add(k); uniq.append(e)
```

**Argsort (indices that would sort the list)**

```python
idx = sorted(range(len(a)), key=a.__getitem__)
```

**Rotate deck with deque**

```python
from collections import deque
d = deque(cards)
d.rotate(k)
cards[:] = list(d)
```

---

## 16) When *Not* to Use a Python List

- Need O(1) front pops/pushes → `deque`
- Need fast membership & uniqueness → `set`
- Need key→value lookups → `dict`
- Need ordered mapping with fast by-key ops → `dict` (Py3.7+ preserves insertion order) or `OrderedDict`
- Need large numeric compute → `numpy.ndarray`
- Need memory‑compact homogeneous numbers → `array('i')`, `array('d')`

---

## 17) Cheatsheet Table

| Task                 | Best Tool           | Snippet                                                        |
| -------------------- | ------------------- | -------------------------------------------------------------- |
| Dedup preserve order | `set` + list        | `seen=set(); [x for x in a if not (x in seen or seen.add(x))]` |
| Top‑K                | `heapq`             | `heapq.nlargest(k, a, key=...)`                                |
| Binary search        | `bisect`            | `i=bisect_left(a,x)`                                           |
| Front queue          | `deque`             | `q.append(); q.popleft()`                                      |
| Sliding window       | `deque`             | `append/popleft + rolling sum`                                 |
| Chunking             | slicing             | `[a[i:i+n] for i in range(0,len(a),n)]`                        |
| Shuffle/Sample       | `random`            | `random.shuffle(a)` / `random.sample(a,k)`                     |
| Group by key         | `defaultdict(list)` | `by[k].append(x)`                                              |
| Merge sortedpri#     | `heapq.merge`       | `list(heapq.merge(*lists))`                                    |

---

**Next up suggestion**: *Strings & Text Processing* or *Dictionaries & Maps*. Let me know which topic to tackle next.

