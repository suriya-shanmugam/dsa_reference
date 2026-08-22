Prefix sums are one of the highest-value patterns in LeetCode. Once you recognize the pattern, many medium problems become straightforward.

---

# Pattern 1: Basic Prefix Sum

**When to use**

* Range sum queries
* Sum between indices
* Static arrays

### Template

```python
nums = [1, 2, 3, 4, 5]

prefix = [0] * (len(nums) + 1)

for i in range(len(nums)):
    prefix[i + 1] = prefix[i] + nums[i]

# Sum from l to r (inclusive)
def range_sum(l, r):
    return prefix[r + 1] - prefix[l]
```

Time:

* Build: O(n)
* Query: O(1)

---

Example problems

* 303. Range Sum Query
* 724. Find Pivot Index

---

# Pattern 2: Running Prefix Sum (No Array Needed)

Sometimes you only need the cumulative sum.

```python
prefix = 0

for num in nums:
    prefix += num
```

Useful for

* Running totals
* Kadane variants
* Prefix hashmap problems

---

# Pattern 3: Prefix Sum + HashMap (Most Important)

Recognize this whenever the problem says:

> Count subarrays...

or

> Find subarray with sum ...

### Core Template

```python
from collections import defaultdict

count = defaultdict(int)
count[0] = 1

prefix = 0
answer = 0

for num in nums:
    prefix += num

    answer += count[prefix - target]

    count[prefix] += 1

return answer
```

---

Why does this work?

Suppose

```
prefix = current prefix sum

Need subarray sum = target

current_prefix - previous_prefix = target

previous_prefix = current_prefix - target
```

So we store every prefix we've seen.

---

Problems

* 560. Subarray Sum Equals K
* 930. Binary Subarrays With Sum
* 1248. Count Number of Nice Subarrays

---

# Pattern 4: Longest Subarray Using Prefix HashMap

Instead of counting frequencies, store the **first occurrence**.

```python
first = {0: -1}

prefix = 0
best = 0

for i, num in enumerate(nums):
    prefix += num

    if prefix - target in first:
        best = max(best, i - first[prefix - target])

    if prefix not in first:
        first[prefix] = i

return best
```

Store only the first index because it gives the longest span.

---

Problems

* 325. Maximum Size Subarray Sum Equals k

---

# Pattern 5: Prefix XOR

For XOR problems.

```python
from collections import defaultdict

count = defaultdict(int)
count[0] = 1

prefix = 0
ans = 0

for num in nums:
    prefix ^= num

    ans += count[prefix ^ target]

    count[prefix] += 1
```

Notice

```
a ^ b = c

a = b ^ c
```

Problems

* 1442
* 1310

---

# Pattern 6: Prefix Modulo

Recognize:

* Divisible by K
* Multiple of K

### Template

```python
from collections import defaultdict

count = defaultdict(int)
count[0] = 1

prefix = 0
ans = 0

for num in nums:
    prefix += num

    mod = prefix % k

    ans += count[mod]

    count[mod] += 1

return ans
```

Reason

```
(prefix2 - prefix1) % k == 0

↓

prefix2 % k == prefix1 % k
```

Problems

* 974. Subarray Sums Divisible by K

---

# Pattern 7: Prefix Balance (Convert Values)

Sometimes convert values before taking prefix sums.

Example:

```
1 -> +1
0 -> -1
```

Then compute prefix.

```python
first = {0: -1}

prefix = 0
best = 0

for i, num in enumerate(nums):
    if num == 1:
        prefix += 1
    else:
        prefix -= 1

    if prefix in first:
        best = max(best, i - first[prefix])
    else:
        first[prefix] = i
```

Problems

* 525. Contiguous Array

---

# Pattern 8: 2D Prefix Sum

For matrix range queries.

### Build

```python
m = len(matrix)
n = len(matrix[0])

prefix = [[0] * (n + 1) for _ in range(m + 1)]

for i in range(m):
    for j in range(n):
        prefix[i + 1][j + 1] = (
            matrix[i][j]
            + prefix[i][j + 1]
            + prefix[i + 1][j]
            - prefix[i][j]
        )
```

### Query

```python
def region(r1, c1, r2, c2):
    return (
        prefix[r2 + 1][c2 + 1]
        - prefix[r1][c2 + 1]
        - prefix[r2 + 1][c1]
        + prefix[r1][c1]
    )
```

Problems

* 304. Range Sum Query 2D

---

# Pattern 9: Difference Array (Reverse Prefix Sum)

Useful for range updates.

```python
diff = [0] * (n + 1)

# Add val to [l, r]
diff[l] += val

if r + 1 < n:
    diff[r + 1] -= val

nums = [0] * n

nums[0] = diff[0]

for i in range(1, n):
    nums[i] = nums[i - 1] + diff[i]
```

Problems

* 370. Range Addition
* 1094. Car Pooling

---

# Pattern 10: Prefix Minimum / Maximum

Maintain the best prefix seen so far.

```python
prefix = 0
min_prefix = 0
best = float("-inf")

for num in nums:
    prefix += num

    best = max(best, prefix - min_prefix)

    min_prefix = min(min_prefix, prefix)
```

Equivalent idea behind Kadane's algorithm.

Problems

* 53. Maximum Subarray
* 918. Maximum Sum Circular Subarray

---

# Recognition Cheat Sheet

| Problem says...               | Pattern                        |
| ----------------------------- | ------------------------------ |
| Sum between indices           | Basic prefix array             |
| Count subarrays with sum = K  | Prefix + hashmap (frequency)   |
| Longest subarray with sum = K | Prefix + hashmap (first index) |
| Sum divisible by K            | Prefix modulo                  |
| XOR equals K                  | Prefix XOR                     |
| Equal numbers of two values   | Convert to ±1 + prefix         |
| Matrix rectangle sum          | 2D prefix                      |
| Many range updates            | Difference array               |
| Maximum subarray              | Prefix minimum                 |
| Running cumulative value      | Running prefix                 |

---

## Interview Recognition Rule

If the problem involves a **contiguous subarray** and asks about:

* exact sum,
* count of subarrays,
* longest/shortest subarray,
* divisibility,
* parity,
* equal counts,
* XOR,

first ask yourself:

> **Can I represent the property as a prefix value, and does `current_prefix - previous_prefix` (or an analogous operation like XOR or modulo) characterize the desired subarray?**

If the answer is yes, a prefix-sum (or prefix-XOR/modulo) solution with a hash map is often the optimal approach.
