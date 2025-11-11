## 🔹 1. What Is a List?

A **list** is an *ordered, mutable* collection that can hold items of **any type**, even mixed types.

```python
nums = [1, 2, 3, 4]
mixed = [1, "hello", 3.14, True]
```

### ✅ Key properties:

* **Ordered:** items maintain insertion order (Python 3.7+ guarantees this)
* **Mutable:** you can modify elements
* **Indexable & sliceable**
* **Can contain duplicates**

---

## 🔹 2. Creating Lists

### Basic:

```python
lst = [1, 2, 3]
```

### From other iterables:

```python
lst = list("abc")       # ['a', 'b', 'c']
lst = list(range(5))    # [0, 1, 2, 3, 4]
```

### Empty list:

```python
lst = []     # or list()
```

---

## 🔹 3. Accessing Elements

### By index:

```python
nums = [10, 20, 30, 40]
nums[0]    # 10
nums[-1]   # 40 (last element)
```

### Slicing:

```python
nums[1:3]    # [20, 30]
nums[:2]     # [10, 20]
nums[::2]    # [10, 30]
nums[::-1]   # reversed list
```

---

## 🔹 4. Modifying Lists (Mutability)

You can change elements in place:

```python
nums = [1, 2, 3]
nums[1] = 99           # [1, 99, 3]
```

You can also modify slices:

```python
nums[0:2] = [10, 20]   # replaces first two
```

---

## 🔹 5. Adding and Removing Elements

### Add:

```python
nums.append(4)          # adds to end
nums.insert(1, 15)      # insert at position
nums.extend([5, 6, 7])  # adds multiple elements
```

### Remove:

```python
nums.pop()              # removes last, returns it
nums.pop(1)             # remove by index
nums.remove(15)         # remove by value
del nums[0]             # delete element or slice
nums.clear()            # remove all
```

---

## 🔹 6. Searching and Counting

```python
nums = [1, 2, 3, 2]
nums.index(2)      # 1 (first occurrence)
nums.count(2)      # 2
```

Check membership:

```python
if 3 in nums:
    print("found")
```

---

## 🔹 7. Iterating Over Lists

```python
for item in nums:
    print(item)
```

Or with index:

```python
for i, val in enumerate(nums):
    print(i, val)
```

---

## 🔹 8. List Comprehensions (Pythonic way)

A concise, powerful way to build lists:

```python
squares = [x*x for x in range(5)]
evens = [x for x in range(10) if x % 2 == 0]
```

Nested comprehension:

```python
matrix = [[i*j for j in range(3)] for i in range(3)]
```

---

## 🔹 9. Copying Lists (Important!)

```python
a = [1, 2, 3]
b = a              # ❌ both refer to same list
c = a.copy()       # ✅ shallow copy
d = list(a)        # ✅ also shallow copy
```

Use `copy.deepcopy()` for nested structures.

---

## 🔹 10. Sorting & Reversing

```python
nums.sort()                # in-place
nums.sort(reverse=True)
sorted_nums = sorted(nums) # returns a new list

nums.reverse()             # reverse in-place
reversed_list = list(reversed(nums))
```

Custom sort:

```python
words = ["apple", "Banana", "cherry"]
words.sort(key=str.lower)
```

---

## 🔹 11. Useful Built-in Functions

| Function                | Description          | Example                     |
| ----------------------- | -------------------- | --------------------------- |
| `len(lst)`              | Number of elements   | `len([1,2,3]) → 3`          |
| `sum(lst)`              | Sum of numeric items | `sum([1,2,3]) → 6`          |
| `min(lst)` / `max(lst)` | Min/max values       | `min([3,1,2]) → 1`          |
| `sorted(lst)`           | Returns sorted copy  | `sorted([3,1,2]) → [1,2,3]` |
| `any(lst)` / `all(lst)` | Boolean checks       | `any([0,1,0]) → True`       |

---

## 🔹 12. Nested Lists (2D Lists)

```python
matrix = [
    [1, 2, 3],
    [4, 5, 6],
    [7, 8, 9]
]
print(matrix[1][2])  # 6
```

List comprehension for flattening:

```python
flat = [x for row in matrix for x in row]
```

---

## 🔹 13. Common Pitfalls

1. **Shared references**

   ```python
   a = [[0]*3]*3   # ❌ same inner list repeated
   a[0][0] = 99    # changes all rows
   # Correct:
   a = [[0]*3 for _ in range(3)]
   ```

2. **Modifying while iterating**

   ```python
   for x in lst:
       if x < 0:
           lst.remove(x)  # can skip elements accidentally
   ```

---

## 🔹 14. Lists vs Other Collections

| Type      | Ordered    | Mutable | Allows Duplicates | Indexed   |
| --------- | ---------- | ------- | ----------------- | --------- |
| **list**  | ✅          | ✅       | ✅                 | ✅         |
| **tuple** | ✅          | ❌       | ✅                 | ✅         |
| **set**   | ❌          | ✅       | ❌                 | ❌         |
| **dict**  | ✅ (by key) | ✅       | ❌ (by key)        | Key-based |

---

## 🔹 15. Performance Notes

* Appending (`.append()`) → O(1) amortized
* Indexing → O(1)
* Inserting/removing in middle → O(n)
* Searching (`in`, `.index()`) → O(n)

If you need **faster inserts/removals** at both ends, use `collections.deque`.

---
