# Math Operations Reference for Programming and LeetCode

Most LeetCode math tricks come from a few repeated ideas: **division rounding**, **remainders**, **prefix sums**, **modulo**, **GCD**, **binary search math**, and **index conversion**.

---

## 1. Ceiling Division

Use this when you need to know **how many full units are needed**, even if the last one is only partially filled.

### Common situations

* Koko eating bananas
* Number of pages needed
* Number of buses needed
* Number of batches required
* Number of hours to finish work
* Splitting items into groups of size `k`

### Formula

For positive integers:

```python
ceil(a / b) = (a + b - 1) // b
```

Or:

```python
ceil(a / b) = a // b + (1 if a % b != 0 else 0)
```

### Example: Koko Eating Bananas

If Koko eats `speed` bananas per hour, and a pile has `pile` bananas:

```python
hours = (pile + speed - 1) // speed
```

Example:

```python
pile = 10
speed = 3

10 // 3 = 3
10 % 3 = 1
```

There is a remainder, so Koko needs one extra hour.

```python
hours = 4
```

Using the formula:

```python
(10 + 3 - 1) // 3
= 12 // 3
= 4
```

### Pattern

```python
total = 0

for pile in piles:
    total += (pile + speed - 1) // speed
```

---

## 2. Quotient and Remainder

Use this when you want to split a number into complete groups and leftover items.

```python
quotient = n // k
remainder = n % k
```

Example:

```python
n = 17
k = 5

17 // 5 = 3
17 % 5 = 2
```

Meaning:

```text
17 = 5 * 3 + 2
```

So there are:

```text
3 full groups
2 leftover items
```

### Common uses

```python
if n % k == 0:
    # n is divisible by k
```

```python
groups = n // k
leftover = n % k
```

```python
answer = n // k + (1 if n % k else 0)
```

---

## 3. Floor Division

Floor division gives the number of complete groups.

```python
n // k
```

Example:

```python
13 // 5 = 2
```

Because only two full groups of `5` fit into `13`.

### Common situations

* Number of full rows
* Number of complete groups
* Number of completed cycles
* Parent index in a heap
* Binary search midpoint

---

## 4. Modulo

Modulo gives the remainder after division.

```python
n % k
```

Example:

```python
17 % 5 = 2
```

### Common uses

#### Check even or odd

```python
if n % 2 == 0:
    print("even")
else:
    print("odd")
```

#### Wrap around circular arrays

```python
next_index = (i + 1) % n
prev_index = (i - 1 + n) % n
```

Example:

```python
arr = [10, 20, 30]
```

If you are at index `2`, then:

```python
(2 + 1) % 3 = 0
```

So the next index wraps back to `0`.

#### Keep numbers within a limit

Common in counting, hashing, and large-number problems:

```python
MOD = 10**9 + 7
answer = answer % MOD
```

---

## 5. Divisibility Checks

Use `%` to check whether one number divides another.

```python
if n % k == 0:
    print("divisible")
```

### Examples

```python
12 % 3 == 0
```

So `12` is divisible by `3`.

```python
14 % 3 == 2
```

So `14` is not divisible by `3`.

### Common LeetCode patterns

```python
if num % 2 == 0:
    # even number
```

```python
if num % 3 == 0:
    # multiple of 3
```

```python
if n % len(arr) == 0:
    # exactly fits into chunks
```

---

## 6. Binary Search Midpoint

Basic midpoint:

```python
mid = (left + right) // 2
```

In languages like Java or C++, this can overflow if `left + right` is too large.

Safer version:

```python
mid = left + (right - left) // 2
```

### Lower mid

```python
mid = left + (right - left) // 2
```

### Upper mid

Useful when avoiding infinite loops:

```python
mid = left + (right - left + 1) // 2
```

Example:

```python
left = 4
right = 5

mid = (4 + 5) // 2 = 4
upper_mid = (4 + 5 + 1) // 2 = 5
```

---

## 7. Min and Max

Use these to keep track of best or worst values.

```python
smallest = min(a, b)
largest = max(a, b)
```

### Common patterns

#### Track minimum

```python
min_value = float("inf")

for x in nums:
    min_value = min(min_value, x)
```

#### Track maximum

```python
max_value = float("-inf")

for x in nums:
    max_value = max(max_value, x)
```

#### Clamp a value

Keep `x` between `low` and `high`.

```python
x = max(low, min(x, high))
```

Example:

```python
low = 0
high = 10
x = 15

x = max(0, min(15, 10))
x = 10
```

---

## 8. Absolute Difference

Use `abs()` when distance or difference matters.

```python
diff = abs(a - b)
```

### Common situations

* Distance between two numbers
* Closest value
* Minimum absolute difference
* Manhattan distance

Example:

```python
a = 7
b = 12

abs(a - b) = 5
```

### Manhattan distance

Used in grid problems:

```python
distance = abs(r1 - r2) + abs(c1 - c2)
```

---

## 9. Prefix Sum

Use prefix sum when you need fast range sum queries.

### Basic idea

Instead of summing every range repeatedly, precompute cumulative sums.

```python
prefix[i] = sum of nums[0] through nums[i - 1]
```

### Build prefix sum

```python
prefix = [0]

for num in nums:
    prefix.append(prefix[-1] + num)
```

For:

```python
nums = [2, 4, 6, 8]
```

Prefix becomes:

```python
[0, 2, 6, 12, 20]
```

### Range sum from index `l` to `r`

Inclusive:

```python
range_sum = prefix[r + 1] - prefix[l]
```

Example:

```python
nums = [2, 4, 6, 8]
l = 1
r = 3
```

Sum is:

```python
4 + 6 + 8 = 18
```

Using prefix:

```python
prefix[4] - prefix[1]
= 20 - 2
= 18
```

---

## 10. Difference Array

Use this when many range updates are needed.

### Problem type

“Add `x` to every element from index `l` to `r`.”

Instead of updating every element one by one, mark the start and end.

```python
diff[l] += x
diff[r + 1] -= x
```

Then take prefix sum of `diff`.

### Example

```python
nums = [0, 0, 0, 0, 0]
```

Add `3` from index `1` to `3`.

```python
diff[1] += 3
diff[4] -= 3
```

Then prefix sum gives:

```python
[0, 3, 3, 3, 0]
```

### Template

```python
diff = [0] * (n + 1)

for l, r, x in updates:
    diff[l] += x
    diff[r + 1] -= x

arr = [0] * n
current = 0

for i in range(n):
    current += diff[i]
    arr[i] = current
```

---

## 11. Counting Frequencies

Use a hash map or array to count items.

### Dictionary frequency

```python
freq = {}

for x in nums:
    freq[x] = freq.get(x, 0) + 1
```

### Using Counter

```python
from collections import Counter

freq = Counter(nums)
```

### Common uses

* Find duplicates
* Check anagrams
* Count pairs
* Majority element
* Frequency sorting
* Sliding window problems

Example:

```python
nums = [1, 2, 2, 3, 3, 3]

freq = {
    1: 1,
    2: 2,
    3: 3
}
```

---

## 12. GCD

GCD means greatest common divisor.

```python
import math

g = math.gcd(a, b)
```

Example:

```python
math.gcd(12, 18) = 6
```

### Common uses

* Simplifying fractions
* Ratio problems
* Number theory
* Repeated pattern problems
* Checking if two numbers can be reduced

### Euclidean algorithm

```python
def gcd(a, b):
    while b:
        a, b = b, a % b
    return a
```

---

## 13. LCM

LCM means least common multiple.

Formula:

```python
lcm(a, b) = abs(a * b) // gcd(a, b)
```

Python:

```python
import math

l = abs(a * b) // math.gcd(a, b)
```

Example:

```python
a = 12
b = 18

gcd = 6
lcm = 12 * 18 // 6 = 36
```

### Common uses

* Repeating cycles
* Scheduling
* Periodic events
* Number theory

---

## 14. Power and Square Root

### Power

```python
x ** y
```

Example:

```python
2 ** 5 = 32
```

### Modular power

Very common in large-number problems:

```python
pow(base, exponent, MOD)
```

Example:

```python
pow(2, 10, 1000)
```

This means:

```python
2^10 % 1000
```

Result:

```python
24
```

Because:

```python
2^10 = 1024
1024 % 1000 = 24
```

### Square root

```python
import math

root = math.isqrt(n)
```

`math.isqrt(n)` gives the integer square root.

Example:

```python
math.isqrt(10) = 3
```

Because:

```python
3 * 3 <= 10
4 * 4 > 10
```

Useful for:

* Prime checking
* Perfect square checking
* Binary search over numbers

---

## 15. Perfect Square Check

Avoid floating-point errors by using integer square root.

```python
import math

root = math.isqrt(n)

if root * root == n:
    print("perfect square")
```

Example:

```python
n = 49
root = 7
7 * 7 == 49
```

So `49` is a perfect square.

---

## 16. Prime Check

To check if `n` is prime, test divisors only up to `sqrt(n)`.

```python
def is_prime(n):
    if n < 2:
        return False

    d = 2

    while d * d <= n:
        if n % d == 0:
            return False
        d += 1

    return True
```

Why only up to square root?

If `n = a * b`, at least one of `a` or `b` must be less than or equal to `sqrt(n)`.

---

## 17. Digit Extraction

Use division and modulo to process digits.

### Get last digit

```python
digit = n % 10
```

### Remove last digit

```python
n = n // 10
```

### Example

```python
n = 472
```

Step by step:

```python
472 % 10 = 2
472 // 10 = 47

47 % 10 = 7
47 // 10 = 4

4 % 10 = 4
4 // 10 = 0
```

Digits from right to left:

```python
2, 7, 4
```

### Common uses

* Reverse integer
* Sum of digits
* Palindrome number
* Digital root
* Armstrong number

---

## 18. Reverse a Number

```python
rev = 0

while n > 0:
    digit = n % 10
    rev = rev * 10 + digit
    n //= 10
```

Example:

```python
n = 123
```

Steps:

```python
rev = 0

digit = 3
rev = 0 * 10 + 3 = 3

digit = 2
rev = 3 * 10 + 2 = 32

digit = 1
rev = 32 * 10 + 1 = 321
```

---

## 19. Convert 2D Index to 1D Index

For a grid with `rows` and `cols`:

```python
index = row * cols + col
```

Example:

```python
row = 2
col = 3
cols = 5

index = 2 * 5 + 3 = 13
```

### Common uses

* Flattening a matrix
* Union Find on a grid
* Graph representation of grids

---

## 20. Convert 1D Index to 2D Index

```python
row = index // cols
col = index % cols
```

Example:

```python
index = 13
cols = 5

row = 13 // 5 = 2
col = 13 % 5 = 3
```

So:

```python
index 13 -> row 2, col 3
```

---

## 21. Matrix Neighbor Movement

Use direction arrays.

```python
directions = [
    (1, 0),   # down
    (-1, 0),  # up
    (0, 1),   # right
    (0, -1)   # left
]
```

Loop:

```python
for dr, dc in directions:
    nr = r + dr
    nc = c + dc

    if 0 <= nr < rows and 0 <= nc < cols:
        # valid neighbor
```

For 8 directions:

```python
directions = [
    (1, 0), (-1, 0), (0, 1), (0, -1),
    (1, 1), (1, -1), (-1, 1), (-1, -1)
]
```

---

## 22. Arithmetic Series Sum

Sum of numbers from `1` to `n`:

```python
total = n * (n + 1) // 2
```

Example:

```python
1 + 2 + 3 + 4 + 5 = 15
```

Formula:

```python
5 * 6 // 2 = 15
```

### Sum from `l` to `r`

```python
sum_l_to_r = r * (r + 1) // 2 - (l - 1) * l // 2
```

Example:

```python
sum from 3 to 7
= 3 + 4 + 5 + 6 + 7
= 25
```

Formula:

```python
7 * 8 // 2 - 2 * 3 // 2
= 28 - 3
= 25
```

---

## 23. Count Pairs

Number of ways to choose 2 items from `n` items:

```python
pairs = n * (n - 1) // 2
```

Example:

```python
n = 4
```

Items:

```python
A, B, C, D
```

Pairs:

```python
AB, AC, AD, BC, BD, CD
```

Total:

```python
4 * 3 // 2 = 6
```

### Common uses

* Count equal pairs
* Count combinations
* Count edges in a complete graph
* Count duplicate pairs

---

## 24. Count Subarrays

Number of subarrays in an array of length `n`:

```python
subarrays = n * (n + 1) // 2
```

Example:

```python
nums = [1, 2, 3]
```

Subarrays:

```python
[1]
[2]
[3]
[1, 2]
[2, 3]
[1, 2, 3]
```

Total:

```python
3 * 4 // 2 = 6
```

---

## 25. Powers of Two

### Check if `n` is a power of two

```python
if n > 0 and n & (n - 1) == 0:
    print("power of two")
```

Examples:

```python
8  = 1000
7  = 0111
8 & 7 = 0000
```

So `8` is a power of two.

```python
10 = 1010
9  = 1001
10 & 9 = 1000
```

So `10` is not a power of two.

---

## 26. Bit Operations

Bit operations are useful for sets, masks, parity, and optimization.

### Check if bit `i` is set

```python
if n & (1 << i):
    print("bit is set")
```

### Set bit `i`

```python
n = n | (1 << i)
```

### Clear bit `i`

```python
n = n & ~(1 << i)
```

### Toggle bit `i`

```python
n = n ^ (1 << i)
```

### Count set bits

```python
count = n.bit_count()
```

Example:

```python
13 = 1101
```

Number of set bits:

```python
3
```

---

## 27. XOR Tricks

XOR is very common in LeetCode.

Rules:

```python
x ^ x = 0
x ^ 0 = x
```

### Find single number

If every number appears twice except one:

```python
ans = 0

for x in nums:
    ans ^= x
```

Example:

```python
nums = [4, 1, 2, 1, 2]
```

Process:

```python
4 ^ 1 ^ 2 ^ 1 ^ 2
```

Duplicates cancel out:

```python
1 ^ 1 = 0
2 ^ 2 = 0
```

Answer:

```python
4
```

---

## 28. Sliding Window Math

Used for subarray or substring problems.

### Fixed-size window sum

```python
window_sum = sum(nums[:k])
best = window_sum

for right in range(k, len(nums)):
    window_sum += nums[right]
    window_sum -= nums[right - k]
    best = max(best, window_sum)
```

### Variable-size window

```python
left = 0
current = 0

for right in range(len(nums)):
    current += nums[right]

    while current > target:
        current -= nums[left]
        left += 1
```

Window length:

```python
length = right - left + 1
```

---

## 29. Fast Pair Counting with Complements

Many problems ask for pairs that sum to a target.

Instead of checking every pair, store what you have seen.

```python
seen = set()

for x in nums:
    need = target - x

    if need in seen:
        return True

    seen.add(x)
```

### Example

```python
nums = [2, 7, 11, 15]
target = 9
```

When `x = 7`:

```python
need = 9 - 7 = 2
```

`2` was already seen, so pair found.

---

## 30. Modulo for Pair Problems

If two numbers must sum to a multiple of `k`, use remainders.

For a number `x`:

```python
rem = x % k
```

You need another number with remainder:

```python
need = (k - rem) % k
```

Example:

```python
k = 5
x = 7

7 % 5 = 2
need = (5 - 2) % 5 = 3
```

So `7` needs a number whose remainder is `3`.

Because:

```python
2 + 3 = 5
```

Which is divisible by `5`.

---

## 31. Common Formula Summary

| Operation                 | Formula                          |
| ------------------------- | -------------------------------- |
| Quotient                  | `a // b`                         |
| Remainder                 | `a % b`                          |
| Ceiling division          | `(a + b - 1) // b`               |
| Divisible check           | `a % b == 0`                     |
| Even check                | `n % 2 == 0`                     |
| Odd check                 | `n % 2 == 1`                     |
| Range length              | `right - left + 1`               |
| Midpoint                  | `left + (right - left) // 2`     |
| Upper midpoint            | `left + (right - left + 1) // 2` |
| Sum `1` to `n`            | `n * (n + 1) // 2`               |
| Count pairs               | `n * (n - 1) // 2`               |
| Count subarrays           | `n * (n + 1) // 2`               |
| 2D to 1D index            | `row * cols + col`               |
| 1D to 2D row              | `index // cols`                  |
| 1D to 2D col              | `index % cols`                   |
| Manhattan distance        | `abs(r1 - r2) + abs(c1 - c2)`    |
| LCM                       | `a * b // gcd(a, b)`             |
| Power of two check        | `n > 0 and n & (n - 1) == 0`     |
| Complement for target sum | `target - x`                     |
| Complement remainder      | `(k - rem) % k`                  |

---

## 32. The Most Important Pattern to Remember

When you divide and need to include a partial group, use **ceiling division**.

### Long form

```python
q = n // k
r = n % k

if r > 0:
    q += 1
```

### Short form

```python
q = (n + k - 1) // k
```

### Example

```python
n = 25
k = 4
```

Regular division:

```python
25 // 4 = 6
25 % 4 = 1
```

There are 6 full groups and 1 leftover, so you need 7 groups.

Formula:

```python
(25 + 4 - 1) // 4
= 28 // 4
= 7
```

This is the same idea used in **Koko Eating Bananas**.
