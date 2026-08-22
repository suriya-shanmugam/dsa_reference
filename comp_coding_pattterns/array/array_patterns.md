Array problems in programming tend to fall into a relatively small set of recurring patterns. Recognizing the pattern is often more important than memorizing individual problems.

Below are the most common array problem patterns, how to identify them, and reusable Python templates.

---

# 1. Traversal

### When to use

* Visit every element
* Count occurrences
* Find max/min
* Calculate sum

### Time Complexity

* O(n)

### Template

```python
def traverse(nums):
    for num in nums:
        # process
        pass
```

Or

```python
def traverse(nums):
    for i in range(len(nums)):
        # nums[i]
        pass
```

Example

```python
def find_max(nums):
    maximum = nums[0]

    for num in nums:
        if num > maximum:
            maximum = num

    return maximum
```

---

# 2. Two Pointers (Opposite Ends)

### When to use

* Sorted arrays
* Reverse array
* Pair sum
* Palindrome
* Remove duplicates

### Complexity

* O(n)

### Template

```python
left = 0
right = len(nums) - 1

while left < right:

    if condition:
        left += 1

    elif another_condition:
        right -= 1

    else:
        # do work
        left += 1
        right -= 1
```

Example

```python
def reverse(nums):
    left = 0
    right = len(nums)-1

    while left < right:
        nums[left], nums[right] = nums[right], nums[left]
        left += 1
        right -= 1

    return nums
```

---

# 3. Fast & Slow Pointers

### When to use

* Remove duplicates
* Remove elements
* Compress array
* Move zeros

### Complexity

* O(n)

### Template

```python
slow = 0

for fast in range(len(nums)):

    if condition:
        nums[slow] = nums[fast]
        slow += 1

return slow
```

Example

Move zeros

```python
def move_zeroes(nums):

    slow = 0

    for fast in range(len(nums)):
        if nums[fast] != 0:
            nums[slow], nums[fast] = nums[fast], nums[slow]
            slow += 1

    return nums
```

---

# 4. Sliding Window (Fixed Size)

### When to use

* Maximum average
* Fixed-size subarray
* Window statistics

### Complexity

* O(n)

### Template

```python
window_sum = sum(nums[:k])
answer = window_sum

for i in range(k, len(nums)):
    window_sum += nums[i]
    window_sum -= nums[i-k]

    answer = max(answer, window_sum)

return answer
```

Example

Maximum sum of size k

```python
def max_sum(nums, k):

    window = sum(nums[:k])
    best = window

    for i in range(k, len(nums)):
        window += nums[i]
        window -= nums[i-k]
        best = max(best, window)

    return best
```

---

# 5. Sliding Window (Variable Size)

### When to use

* Longest substring
* Smallest subarray
* At most K
* At least K

### Complexity

* O(n)

### Template

```python
left = 0

for right in range(len(nums)):

    # expand window

    while invalid_window:
        left += 1

    # update answer
```

Example

Smallest subarray ≥ target

```python
def min_subarray(target, nums):

    left = 0
    total = 0
    ans = float("inf")

    for right in range(len(nums)):
        total += nums[right]

        while total >= target:
            ans = min(ans, right-left+1)
            total -= nums[left]
            left += 1

    return ans if ans != float("inf") else 0
```

---

# 6. Prefix Sum

### When to use

* Range sums
* Many sum queries
* Subarray sums

### Complexity

Build: O(n)

Query: O(1)

### Template

```python
prefix = [0]

for num in nums:
    prefix.append(prefix[-1] + num)
```

Range query

```python
sum_lr = prefix[r+1] - prefix[l]
```

Example

```python
def build_prefix(nums):

    prefix = [0]

    for num in nums:
        prefix.append(prefix[-1] + num)

    return prefix
```

---

# 7. Difference Array

### When to use

* Multiple range updates

### Complexity

* O(n)

### Template

```python
diff = [0]*(n+1)

diff[l] += val

if r+1 < len(diff):
    diff[r+1] -= val

result = []
current = 0

for x in diff[:-1]:
    current += x
    result.append(current)
```

---

# 8. Hash Map / Frequency Counting

### When to use

* Counting
* Duplicates
* Two Sum
* Most frequent

### Complexity

* O(n)

### Template

```python
count = {}

for num in nums:
    count[num] = count.get(num, 0) + 1
```

Example

```python
def frequency(nums):

    freq = {}

    for n in nums:
        freq[n] = freq.get(n, 0) + 1

    return freq
```

---

# 9. Monotonic Stack

### When to use

* Next greater element
* Previous smaller
* Histogram
* Daily temperatures

### Complexity

* O(n)

### Template

```python
stack = []

for i in range(len(nums)):

    while stack and nums[stack[-1]] < nums[i]:
        index = stack.pop()
        # process

    stack.append(i)
```

---

# 10. Monotonic Queue (Deque)

### When to use

* Sliding window maximum
* Minimum in window

### Complexity

* O(n)

### Template

```python
from collections import deque

dq = deque()

for i in range(len(nums)):

    while dq and nums[dq[-1]] <= nums[i]:
        dq.pop()

    dq.append(i)

    if dq[0] <= i-k:
        dq.popleft()

    if i >= k-1:
        answer = nums[dq[0]]
```

---

# 11. Binary Search

### When to use

* Sorted arrays
* Search answer
* First/last occurrence

### Complexity

* O(log n)

### Template

```python
left = 0
right = len(nums)-1

while left <= right:

    mid = (left + right)//2

    if nums[mid] == target:
        return mid

    elif nums[mid] < target:
        left = mid + 1

    else:
        right = mid - 1

return -1
```

---

# 12. Binary Search on Answer

### When to use

* Minimize maximum
* Capacity problems
* Allocate books
* Shipping packages

### Template

```python
left = minimum_possible
right = maximum_possible

while left < right:

    mid = (left + right)//2

    if feasible(mid):
        right = mid
    else:
        left = mid + 1

return left
```

---

# 13. Kadane's Algorithm

### When to use

* Maximum subarray
* Maximum profit
* Best contiguous sum

### Complexity

* O(n)

### Template

```python
current = nums[0]
best = nums[0]

for num in nums[1:]:
    current = max(num, current + num)
    best = max(best, current)

return best
```

---

# 14. Merge Intervals

### When to use

* Overlapping intervals
* Calendar problems
* Scheduling

### Complexity

* O(n log n)

### Template

```python
intervals.sort()

merged = []

for interval in intervals:

    if not merged or merged[-1][1] < interval[0]:
        merged.append(interval)

    else:
        merged[-1][1] = max(merged[-1][1], interval[1])

return merged
```

---

# 15. Greedy Scan

### When to use

* Jump Game
* Gas Station
* Stock problems

### Complexity

* O(n)

### Template

```python
answer = initial

for x in nums:

    # make local optimal choice

return answer
```

---

# 16. Cyclic Sort

### When to use

* Numbers from 1…n
* Missing number
* Duplicate number

### Complexity

* O(n)

### Template

```python
i = 0

while i < len(nums):

    correct = nums[i] - 1

    if nums[i] != nums[correct]:
        nums[i], nums[correct] = nums[correct], nums[i]
    else:
        i += 1
```

---

# 17. Partitioning (Dutch National Flag)

### When to use

* Sort colors
* Three-way partition
* Pivot partition

### Complexity

* O(n)

### Template

```python
low = 0
mid = 0
high = len(nums)-1

while mid <= high:

    if nums[mid] == 0:
        nums[low], nums[mid] = nums[mid], nums[low]
        low += 1
        mid += 1

    elif nums[mid] == 1:
        mid += 1

    else:
        nums[mid], nums[high] = nums[high], nums[mid]
        high -= 1
```

---

# 18. Heap (Top K)

### When to use

* K largest
* K smallest
* Streaming data

### Complexity

* O(n log k)

### Template

```python
import heapq

heap = []

for num in nums:

    heapq.heappush(heap, num)

    if len(heap) > k:
        heapq.heappop(heap)

return heap
```

---

# Pattern Recognition Cheat Sheet

| If the problem says...              | Pattern                 |
| ----------------------------------- | ----------------------- |
| Pair in sorted array                | Two Pointers            |
| Reverse array                       | Two Pointers            |
| Remove duplicates                   | Fast & Slow Pointers    |
| Longest/shortest contiguous segment | Sliding Window          |
| Maximum/minimum of every window     | Monotonic Queue         |
| Range sum queries                   | Prefix Sum              |
| Many range updates                  | Difference Array        |
| Frequency/count occurrences         | Hash Map                |
| Next greater/smaller element        | Monotonic Stack         |
| Sorted array search                 | Binary Search           |
| Minimize/maximize an answer         | Binary Search on Answer |
| Maximum contiguous sum              | Kadane's Algorithm      |
| Merge overlapping ranges            | Merge Intervals         |
| Numbers 1…n with missing/duplicate  | Cyclic Sort             |
| Three categories to partition       | Dutch National Flag     |
| Top K elements                      | Heap                    |

