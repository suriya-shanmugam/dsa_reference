# 1. Lists

## Initialize

```python
arr = []
arr = [1, 2, 3]
arr = [0] * 5                 # [0, 0, 0, 0, 0]
arr = list(range(5))          # [0, 1, 2, 3, 4]
arr = list(range(2, 10, 2))   # [2, 4, 6, 8]
```

## 2D list

```python
grid = [[0] * cols for _ in range(rows)]   # correct
```

Avoid:

```python
grid = [[0] * cols] * rows   # bad: shared rows
```

## Common transforms

```python
squares = [x * x for x in arr]
evens = [x for x in arr if x % 2 == 0]
chars = list("hello")        # ['h', 'e', 'l', 'l', 'o']
nums = list(map(int, "1 2 3".split()))
```

## Reverse / sort

```python
arr.reverse()                # in-place
rev = arr[::-1]              # copy reversed

arr.sort()                   # in-place ascending
arr.sort(reverse=True)
sorted_arr = sorted(arr)     # new list
sorted_arr = sorted(arr, key=lambda x: x[1])
```

## Useful list tricks

```python
arr.append(x)
x = arr.pop()                # pop from end
x = arr.pop(0)               # O(n), avoid for queue use

arr.extend([4, 5, 6])
arr.insert(i, x)

first = arr[0]
last = arr[-1]
sub = arr[l:r]               # [l, r)
```

---

# 2. Strings

## Initialize / convert

```python
s = ""
s = str(123)
chars = list(s)
s2 = "".join(chars)
```

## Common transforms

```python
words = s.split()
parts = s.split(",")
joined = "-".join(["a", "b", "c"])

lower = s.lower()
upper = s.upper()
trimmed = s.strip()
replaced = s.replace("a", "b")
```

## Reverse string

```python
rev = s[::-1]
```

## Character / ASCII conversion

```python
code = ord('a')              # 97
ch = chr(97)                 # 'a'

idx = ord(c) - ord('a')      # char to 0..25
```

## Frequency

```python
from collections import Counter
freq = Counter(s)
```

---

# 3. Sets

## Initialize

```python
st = set()
st = {1, 2, 3}
st = set(arr)
```

## Common operations

```python
st.add(x)
st.remove(x)                 # error if missing
st.discard(x)                # no error if missing
exists = x in st
```

## Set algebra

```python
a | b    # union
a & b    # intersection
a - b    # difference
a ^ b    # symmetric difference
```

## Interview use cases

```python
seen = set()
for x in arr:
    if x in seen:
        print("duplicate")
    seen.add(x)
```

---

# 4. Dictionaries / Hash Maps

## Initialize

```python
d = {}
d = {"a": 1, "b": 2}
```

## Safe increment / counting

```python
d[x] = d.get(x, 0) + 1
```

## Iterate

```python
for k in d:
    print(k, d[k])

for k, v in d.items():
    print(k, v)
```

## Useful methods

```python
val = d.get(key, default)
d.setdefault(key, []).append(x)
```

## Dictionary comprehension

```python
squares = {x: x * x for x in range(5)}
```

## Sort dict items

```python
items = sorted(d.items())                    # by key
items = sorted(d.items(), key=lambda kv: kv[1])   # by value
```

---

# 5. `defaultdict`

Very common in interviews.

```python
from collections import defaultdict

d = defaultdict(int)         # default 0
d[x] += 1

groups = defaultdict(list)
groups[key].append(val)

sets = defaultdict(set)
sets[key].add(val)
```

---

# 6. `Counter`

Perfect for frequency maps.

```python
from collections import Counter

cnt = Counter(arr)
cnt = Counter("banana")

most_common = cnt.most_common(2)
```

Useful patterns:

```python
if cnt1 == cnt2:
    print("anagrams")
```

---

# 7. `deque`

Use for **queue**, **BFS**, sometimes sliding window.

```python
from collections import deque

q = deque()
q.append(1)          # push right
q.appendleft(0)      # push left

x = q.pop()          # pop right
x = q.popleft()      # pop left
```

## BFS template

```python
from collections import deque

q = deque([start])
seen = {start}

while q:
    node = q.popleft()
    for nei in graph[node]:
        if nei not in seen:
            seen.add(nei)
            q.append(nei)
```

---

# 8. Heap / Priority Queue

Python uses min-heap.

```python
import heapq

heap = []
heapq.heappush(heap, 3)
heapq.heappush(heap, 1)
heapq.heappush(heap, 2)

x = heapq.heappop(heap)      # smallest
smallest = heap[0]
```

## Heapify existing list

```python
arr = [3, 1, 5, 2]
heapq.heapify(arr)
```

## Max heap trick

```python
heapq.heappush(heap, -x)
x = -heapq.heappop(heap)
```

## Top k smallest / largest

```python
import heapq

smallest_k = heapq.nsmallest(k, arr)
largest_k = heapq.nlargest(k, arr)
```

---

# 9. Stack patterns

Usually just use list.

```python
stack = []
stack.append(x)
top = stack[-1]
x = stack.pop()
```

## Monotonic stack starter

```python
stack = []
for i, x in enumerate(arr):
    while stack and arr[stack[-1]] < x:
        j = stack.pop()
    stack.append(i)
```

---

# 10. Tuple tricks

Useful for coordinates, heap items, hashmap keys.

```python
pt = (r, c)
d[pt] = 1
visited.add((r, c))
```

## Sorting by multiple keys

```python
pairs.sort(key=lambda x: (x[0], -x[1]))
```

---

# 11. Basic numeric helpers

## Min / max / sum

```python
total = sum(arr)
mn = min(arr)
mx = max(arr)
```

## Count truthy / conditions

```python
count = sum(1 for x in arr if x % 2 == 0)
count = sum(x == target for x in arr)
```

## Prefix sum

```python
prefix = [0]
for x in arr:
    prefix.append(prefix[-1] + x)

# sum of arr[l:r+1]
range_sum = prefix[r + 1] - prefix[l]
```

## Running sum

```python
running = 0
for x in arr:
    running += x
```

---

# 12. Division / modulo gotchas

## Integer division

```python
q = a // b
r = a % b
```

## Ceiling division

```python
ceil_div = (a + b - 1) // b          # for positive integers
```

Alternative:

```python
import math
ceil_div = math.ceil(a / b)
```

## Check even / odd

```python
x % 2 == 0
x % 2 == 1
```

---

# 13. Common math functions

```python
import math

math.sqrt(x)
math.gcd(a, b)
math.lcm(a, b)
math.factorial(n)
math.inf
```

## Absolute value

```python
abs(x)
```

## Power

```python
x ** 2
pow(x, n)
pow(x, n, mod)      # modular exponentiation
```

Very interview-useful:

```python
pow(2, 10, 1000)
```

---

# 14. Infinity initialization

Super common for DP / shortest path / min-max problems.

```python
INF = float('inf')
NEG_INF = float('-inf')

best = INF
worst = NEG_INF
```

---

# 15. Swap values

```python
a, b = b, a
```

---

# 16. Enumerate / zip

## Enumerate

```python
for i, x in enumerate(arr):
    ...
```

## Zip

```python
for a, b in zip(arr1, arr2):
    ...
```

## Unzip

```python
pairs = [(1, 2), (3, 4)]
a, b = zip(*pairs)
```

---

# 17. Transpose matrix

```python
matrix = [
    [1, 2, 3],
    [4, 5, 6]
]

transposed = list(zip(*matrix))
# [(1, 4), (2, 5), (3, 6)]
```

If you want lists:

```python
transposed = [list(row) for row in zip(*matrix)]
```

---

# 18. Flatten list

## 2D to 1D

```python
flat = [x for row in grid for x in row]
```

---

# 19. Index maps

Useful for quick lookup.

```python
idx_map = {x: i for i, x in enumerate(arr)}
```

For duplicates:

```python
from collections import defaultdict

pos = defaultdict(list)
for i, x in enumerate(arr):
    pos[x].append(i)
```

---

# 20. Sorting patterns that show up a lot

## Sort intervals by start then end

```python
intervals.sort(key=lambda x: (x[0], x[1]))
```

## Sort strings by length

```python
words.sort(key=len)
```

## Sort by frequency then value

```python
from collections import Counter

cnt = Counter(arr)
arr.sort(key=lambda x: (cnt[x], x))          # low freq first
arr.sort(key=lambda x: (-cnt[x], x))         # high freq first
```

---

# 21. Binary tricks

## Check power of 2

```python
x > 0 and (x & (x - 1)) == 0
```

## Get last bit

```python
bit = x & 1
```

## Shift

```python
x << 1    # multiply by 2
x >> 1    # divide by 2
```

---

# 22. Range loops

```python
for i in range(n):
    ...

for i in range(n - 1, -1, -1):
    ...

for i in range(l, r + 1):
    ...
```

---

# 23. Common matrix traversal

```python
dirs4 = [(1, 0), (-1, 0), (0, 1), (0, -1)]
dirs8 = [
    (1, 0), (-1, 0), (0, 1), (0, -1),
    (1, 1), (1, -1), (-1, 1), (-1, -1)
]

for dr, dc in dirs4:
    nr, nc = r + dr, c + dc
```

---

# 24. Useful one-liners

## Check all / any

```python
all(x > 0 for x in arr)
any(x == 0 for x in arr)
```

## Remove duplicates while preserving order

```python
unique = list(dict.fromkeys(arr))
```

## Frequency array for lowercase letters

```python
freq = [0] * 26
for c in s:
    freq[ord(c) - ord('a')] += 1
```

## Compare anagrams

```python
from collections import Counter
Counter(s1) == Counter(s2)
```

---

# 25. Small interview templates

## Two-sum hashmap

```python
seen = {}
for i, x in enumerate(nums):
    need = target - x
    if need in seen:
        return [seen[need], i]
    seen[x] = i
```

## Group anagrams

```python
from collections import defaultdict

groups = defaultdict(list)
for word in words:
    key = tuple(sorted(word))
    groups[key].append(word)

result = list(groups.values())
```

## Merge intervals

```python
intervals.sort(key=lambda x: x[0])
merged = []

for start, end in intervals:
    if not merged or merged[-1][1] < start:
        merged.append([start, end])
    else:
        merged[-1][1] = max(merged[-1][1], end)
```

## Prefix sum hashmap

```python
count = 0
prefix = 0
seen = {0: 1}

for x in nums:
    prefix += x
    count += seen.get(prefix - k, 0)
    seen[prefix] = seen.get(prefix, 0) + 1
```

---

# 26. Things interviewers love seeing

These are the “nice, clean Python” moves:

```python
from collections import Counter, defaultdict, deque
import heapq
import math
```

And these patterns:

```python
d.get(key, 0)
defaultdict(list)
Counter(nums)
deque([...])
heapq.heapify(arr)
enumerate(arr)
zip(a, b)
prefix[r+1] - prefix[l]
float('inf')
```

---

# 27. Tiny “memorize these” section

If you only memorize a handful:

```python
# counting
d[x] = d.get(x, 0) + 1

# grouping
from collections import defaultdict
g = defaultdict(list)

# queue / bfs
from collections import deque
q = deque()

# heap
import heapq

# reverse
arr[::-1]

# sort by key
arr.sort(key=lambda x: x[1])

# prefix sum
prefix.append(prefix[-1] + x)

# safe 2D array
grid = [[0] * cols for _ in range(rows)]

# char index
ord(c) - ord('a')

# infinity
float('inf')
```

---