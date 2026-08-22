Sliding window problems usually fall into a small number of patterns. If you recognize the pattern, you can solve most LeetCode sliding window questions with the same template.

---

# 1. Fixed-Size Sliding Window

### When to use

* Window size is fixed (`k`).
* Find maximum, minimum, average, sum, etc.

### Template

```python
def fixed_window(nums, k):
    window_sum = 0

    # Build first window
    for i in range(k):
        window_sum += nums[i]

    answer = window_sum

    # Slide
    for right in range(k, len(nums)):
        left = right - k

        window_sum += nums[right]
        window_sum -= nums[left]

        answer = max(answer, window_sum)

    return answer
```

### Example

**Maximum Sum Subarray of Size K**

Input

```python
nums = [2,1,5,1,3,2]
k = 3
```

Windows

```
2 1 5 = 8
1 5 1 = 7
5 1 3 = 9
1 3 2 = 6
```

Answer = **9**

---

# 2. Longest Window (Expand then Shrink)

### When to use

Find

* Longest substring
* Longest subarray
* "At most K"
* "No duplicates"

### Standard Template

```python
def longest_window(s):
    left = 0
    answer = 0

    window = {}

    for right in range(len(s)):
        # Add right character
        c = s[right]
        window[c] = window.get(c, 0) + 1

        # Shrink until valid
        while not valid(window):
            left_char = s[left]
            window[left_char] -= 1

            if window[left_char] == 0:
                del window[left_char]

            left += 1

        # Update answer
        answer = max(answer, right - left + 1)

    return answer
```

### Example

**Longest Substring Without Repeating Characters**

```
s = "abcabcbb"
```

Window movement

```
abc
bca
cab
abc
```

Longest length = **3**

---

# 3. Smallest Window (Expand then Shrink)

### When to use

Find

* Minimum length
* Smallest substring
* Minimum window

### Template

```python
def smallest_window(nums, target):
    left = 0
    current = 0
    answer = float('inf')

    for right in range(len(nums)):
        current += nums[right]

        while current >= target:
            answer = min(answer, right - left + 1)

            current -= nums[left]
            left += 1

    return 0 if answer == float('inf') else answer
```

### Example

**Minimum Size Subarray Sum**

```
nums = [2,3,1,2,4,3]
target = 7
```

Smallest valid window

```
4 3
```

Length = **2**

---

# 4. Variable Window with Frequency Map

### When to use

Problems involving

* Characters
* Frequencies
* Anagrams
* Permutations

### Template

```python
from collections import defaultdict

def frequency_window(s):
    left = 0
    freq = defaultdict(int)

    for right in range(len(s)):
        freq[s[right]] += 1

        while need_to_shrink(freq):
            freq[s[left]] -= 1
            if freq[s[left]] == 0:
                del freq[s[left]]
            left += 1
```

### Example

**Permutation in String**

```
s1 = "ab"
s2 = "eidbaooo"
```

Window

```
ei
id
db
ba  ← permutation found
```

Return **True**

---

# 5. At Most K Distinct

One of the most common interview patterns.

### Template

```python
from collections import defaultdict

def at_most_k(s, k):
    left = 0
    freq = defaultdict(int)
    answer = 0

    for right in range(len(s)):
        freq[s[right]] += 1

        while len(freq) > k:
            freq[s[left]] -= 1

            if freq[s[left]] == 0:
                del freq[s[left]]

            left += 1

        answer = max(answer, right - left + 1)

    return answer
```

### Example

**Longest Substring with At Most 2 Distinct Characters**

```
s = "eceba"
k = 2
```

Longest window

```
ece
```

Length = **3**

---

# 6. Exactly K Distinct

### Trick

Instead of writing new logic:

```
Exactly(K) =
AtMost(K) - AtMost(K-1)
```

### Template

```python
def exactly_k(nums, k):
    return at_most(nums, k) - at_most(nums, k - 1)
```

### Example

**Subarrays with Exactly K Distinct Integers**

```
nums = [1,2,1,2,3]
k = 2
```

Answer = **7**

---

# 7. Sliding Window Maximum (Monotonic Queue)

### When to use

Need the

* Maximum
* Minimum

for every window.

### Template

```python
from collections import deque

def max_sliding_window(nums, k):
    dq = deque()
    answer = []

    for right in range(len(nums)):
        while dq and nums[dq[-1]] <= nums[right]:
            dq.pop()

        dq.append(right)

        # Remove out-of-window index
        if dq[0] <= right - k:
            dq.popleft()

        if right >= k - 1:
            answer.append(nums[dq[0]])

    return answer
```

### Example

```
nums = [1,3,-1,-3,5,3,6,7]
k = 3
```

Output

```
[3,3,5,5,6,7]
```

---

# 8. Sliding Window with Counts (Anagrams)

### When to use

Need to compare frequencies of two strings.

### Template

```python
from collections import Counter

def find_anagrams(s, p):
    need = Counter(p)
    window = Counter()

    left = 0
    result = []

    for right in range(len(s)):
        window[s[right]] += 1

        # Keep window size fixed
        if right - left + 1 > len(p):
            window[s[left]] -= 1
            if window[s[left]] == 0:
                del window[s[left]]
            left += 1

        if window == need:
            result.append(left)

    return result
```

### Example

```
s = "cbaebabacd"
p = "abc"
```

Output

```
[0, 6]
```

---

# Recognition Cheat Sheet

| Pattern                | Typical clues                     | Core template                                    |
| ---------------------- | --------------------------------- | ------------------------------------------------ |
| Fixed-size window      | "Size K", average, max sum        | Slide by adding right, removing left             |
| Longest valid window   | Longest substring/subarray        | Expand → shrink until valid → update answer      |
| Smallest valid window  | Minimum length/window             | Expand → while valid, update answer and shrink   |
| Frequency map          | Characters, anagrams, duplicates  | Dictionary/Counter + sliding window              |
| At most K              | "At most K distinct/replacements" | Shrink while constraint is violated              |
| Exactly K              | "Exactly K distinct"              | `AtMost(K) - AtMost(K-1)`                        |
| Window maximum/minimum | Max/min in each window            | Monotonic deque                                  |
| Anagram/permutation    | Same character counts             | Fixed-size window + `Counter` or frequency array |

## Common problems by pattern

| Pattern                 | Representative LeetCode problems                          |
| ----------------------- | --------------------------------------------------------- |
| Fixed-size window       | 643. Maximum Average Subarray I                           |
| Longest valid window    | 3. Longest Substring Without Repeating Characters         |
| Smallest valid window   | 209. Minimum Size Subarray Sum                            |
| At most K distinct      | 340. Longest Substring with At Most K Distinct Characters |
| Exactly K distinct      | 992. Subarrays with K Different Integers                  |
| Sliding window maximum  | 239. Sliding Window Maximum                               |
| Anagrams                | 438. Find All Anagrams in a String                        |
| Minimum covering window | 76. Minimum Window Substring                              |

A useful mental model is:

* **Fixed-size problems:** add one element, remove one element.
* **Variable-size problems:** expand the window with `right`, then shrink with `left` until the window satisfies the constraint.
* **Frequency problems:** maintain a dictionary or `Counter` to track counts within the current window.
* **Window maximum/minimum:** use a monotonic deque instead of recomputing the max or min for each window.
