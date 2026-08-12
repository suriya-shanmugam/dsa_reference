Great. Now that we understand the problem, let's build the solution step by step.

# Solution Idea

We need two things:

1. **Find the history of a key quickly.**
2. **Find the correct version within that history quickly.**

These two requirements naturally suggest using two different data structures:

* **Hash Map** → Find a key in O(1)
* **Sorted Array (List)** → Store versions in timestamp order for binary search

---

# Step 1: Hash Map

Instead of storing a single value for each key:

```text
name -> Alice
```

We store **all versions**.

```text
name ->
```

```text
[
    (1, Alice),
    (5, Bob),
    (8, Charlie)
]
```

Another key:

```text
city ->
```

```text
[
    (2, London),
    (6, Paris)
]
```

Overall structure:

```text
HashMap

name ------------------------+
                             |
                             v
                   [(1,Alice),
                    (5,Bob),
                    (8,Charlie)]

city ------------------------+
                             |
                             v
                   [(2,London),
                    (6,Paris)]
```

The hash map gives us the version history for a key in **O(1)** average time.

---

# Step 2: Why an Array?

Suppose we insert timestamps in chronological order:

```text
set("name", "Alice", 1)
set("name", "Bob", 5)
set("name", "Charlie", 8)
```

The list becomes

```text
[(1,Alice), (5,Bob), (8,Charlie)]
```

Notice something important:

The timestamps are already sorted.

No sorting is required.

Each new update is simply appended.

```text
Before

[(1,Alice), (5,Bob)]

append

(8,Charlie)

After

[(1,Alice), (5,Bob), (8,Charlie)]
```

Appending to a dynamic array takes **O(1)** amortized time.

So the `set` operation is very efficient.

---

# Step 3: Reading Data

Suppose we need

```text
get("name", 6)
```

First, the hash map finds

```text
[(1,Alice),
 (5,Bob),
 (8,Charlie)]
```

Now we need the value whose timestamp is the **largest timestamp ≤ 6**.

Looking at the list:

```text
1
5
8
```

The answer is

```text
5
```

which corresponds to

```text
Bob
```

---

# Can We Scan the List?

Yes.

```text
1
5
8
```

Check each timestamp:

```text
1 ✓
5 ✓
8 ✗
```

Return the previous one.

This works.

But what if there are a million versions?

```text
1
2
3
4
5
6
...
999999
1000000
```

Finding

```text
get(key, 723456)
```

would require scanning hundreds of thousands of entries.

Time complexity:

```text
O(n)
```

Too slow for frequent reads.

---

# Step 4: Key Observation

The timestamps are sorted:

```text
1
5
8
15
20
31
45
```

Whenever data is sorted, we should think of **binary search**.

Instead of checking every timestamp:

```text
1
5
8
15
20
31
45
```

Binary search repeatedly halves the search space.

For example, to find the latest timestamp ≤ 18:

```text
1   5   8   15   20   31   45
            ^
          Middle = 15
```

Since `15 ≤ 18`, 15 is a valid candidate. But there might be a closer timestamp on the right, so we continue searching the right half:

```text
20   31   45
 ^
20 > 18
```

Now we discard everything to the right of 20 and continue between 15 and 20. The search ends with **15** as the largest timestamp ≤ 18.

Instead of checking every element, binary search finds the answer in **O(log n)** time.

---

# Complete Data Structure

```text
HashMap

"name"
   |
   v
[(1,Alice),
 (5,Bob),
 (8,Charlie),
 (12,David)]

"city"
   |
   v
[(2,London),
 (6,Paris),
 (15,Rome)]
```

* **Hash Map** quickly locates the version list for a key.
* **Sorted Array** stores versions in increasing timestamp order.
* **Binary Search** efficiently finds the latest version at or before a given timestamp.

---

# Time Complexity

| Operation                    | How it works                                        | Complexity                   |
| ---------------------------- | --------------------------------------------------- | ---------------------------- |
| `set(key, value, timestamp)` | Hash map lookup + append to the key's version list  | **O(1)** average (amortized) |
| `get(key, timestamp)`        | Hash map lookup + binary search on the version list | **O(log n)**                 |

This combination—**hash map + sorted arrays + binary search**—is the standard and elegant solution to the Versioned Key-Value Store problem.

The next step is to walk through the **binary search logic** for `get()` in detail, including why we search for the **rightmost timestamp ≤ target** and how to implement it correctly.

Let's focus on the most important part: **binary search for the rightmost timestamp ≤ target timestamp**.

This is the part where most implementation mistakes happen.

---

# Goal of `get(key, timestamp)`

Suppose we have:

```text
versions:

index:       0        1        2        3        4
          +--------+--------+--------+--------+--------+
time:     |   2    |   5    |   9    |   12   |   20   |
value:    |  A     |   B    |   C    |   D    |   E    |
          +--------+--------+--------+--------+--------+
```

Query:

```text
get(key, 10)
```

We need:

```
largest timestamp <= 10
```

Candidates:

```
2 ✓
5 ✓
9 ✓
12 ✗
20 ✗
```

Answer:

```
timestamp = 9
value = C
```

So we are not searching for an exact match.

We are searching for:

> The rightmost position where timestamp <= target.

---

# Why Normal Binary Search Does Not Work

Normal binary search searches for an exact value.

Example:

```text
find timestamp 9
```

It returns index 2.

But our problem is different.

Example:

```text
get(key, 10)
```

There is no timestamp 10.

We need:

```
9
```

Example:

```text
get(key, 11)
```

Again:

```
9
```

Example:

```text
get(key, 15)
```

Answer:

```
12
```

So we need a modified binary search.

---

# Binary Search Strategy

Maintain:

```
left
right
answer
```

Initially:

```
left = 0
right = versions.length - 1
answer = -1
```

`answer` stores the best timestamp found so far.

---

# Example Walkthrough

Array:

```
[2, 5, 9, 12, 20]
```

Target:

```
10
```

Initial:

```
left = 0
right = 4
answer = -1
```

---

## Iteration 1

Calculate middle:

```
mid = (0 + 4) / 2

mid = 2
```

Timestamp:

```
versions[2] = 9
```

Compare:

```
9 <= 10
```

This is a valid answer.

Store it:

```
answer = 2
```

But maybe there is a larger timestamp closer to 10.

Search right side:

```
left = mid + 1

left = 3
```

Now:

```
[12,20]
```

---

## Iteration 2

```
left = 3
right = 4

mid = 3
```

Timestamp:

```
12
```

Compare:

```
12 > 10
```

Too large.

Move left:

```
right = mid - 1

right = 2
```

---

Now:

```
left = 3
right = 2
```

Loop ends.

Return:

```
answer = 2
```

Value:

```
versions[2].value

C
```

---

# Java Implementation

```java
class TimeMap {

    private Map<String, List<Pair<Integer, String>>> map;

    public TimeMap() {
        map = new HashMap<>();
    }

    public void set(String key, String value, int timestamp) {

        map.putIfAbsent(key, new ArrayList<>());

        map.get(key).add(
            new Pair<>(timestamp, value)
        );
    }


    public String get(String key, int timestamp) {

        if (!map.containsKey(key)) {
            return "";
        }

        List<Pair<Integer,String>> versions = map.get(key);

        int left = 0;
        int right = versions.size() - 1;

        int answer = -1;


        while (left <= right) {

            int mid = left + (right - left) / 2;

            int currentTime = versions.get(mid).getKey();


            if (currentTime <= timestamp) {

                answer = mid;

                // look for a later valid timestamp
                left = mid + 1;

            } else {

                // timestamp too large
                right = mid - 1;
            }
        }


        if (answer == -1) {
            return "";
        }

        return versions.get(answer).getValue();
    }
}
```

---

# The Key Pattern

This binary search pattern appears everywhere:

Find:

```
largest value <= target
```

Examples:

* Versioned databases
* Finding previous stock price
* Calendar events before a date
* Nearest checkpoint
* Floor operation in sorted sets

The mental template is:

```
if current value <= target:

    save answer
    move right

else:

    move left
```

Because we want the **rightmost valid candidate**.

---

# Full System View

The final design:

```
                 get("user", 50)
                         |
                         v

                 HashMap lookup

                         |
                         v

        user -> [(10,A),
                 (20,B),
                 (40,C),
                 (70,D)]

                         |
                         v

              Binary Search

                         |
                         v

              largest timestamp <= 50

                         |
                         v

                       (40,C)
```

Complexities:

```
Write:
O(1)

Read:
O(log n)
```

This is the core design behind many simple **log-structured storage systems** and historical data access mechanisms.
