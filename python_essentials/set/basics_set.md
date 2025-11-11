## 🔹 1. What is a Set?

A **set** is an **unordered collection of unique elements**.

* **Unordered** → no indexing, no slicing
* **Unique** → duplicates are automatically removed
* **Mutable** → you can add or remove elements

### Creating Sets

```python
# Using curly braces
fruits = {'apple', 'banana', 'cherry'}
print(fruits)

# Using the set() constructor
numbers = set([1, 2, 3, 3, 2])
print(numbers)  # duplicates removed: {1, 2, 3}

# Empty set
empty = set()
```

⚠️ Note: `{}` creates an empty **dict**, not a set. Use `set()`.

---

## 🔹 2. Adding Elements

```python
fruits.add('orange')
fruits.update(['kiwi', 'mango'])  # add multiple elements
print(fruits)
```

* `add(x)` → add a single element
* `update(iterable)` → add multiple elements at once

---

## 🔹 3. Removing Elements

```python
fruits.remove('banana')  # raises KeyError if not present
fruits.discard('grape')  # no error if not present
fruits.pop()             # removes and returns a random element
fruits.clear()           # remove all elements
```

---

## 🔹 4. Set Operations

### 4.1 Union

Combine elements from both sets:

```python
A = {1, 2, 3}
B = {3, 4, 5}

print(A | B)  # {1, 2, 3, 4, 5}
print(A.union(B))
```

---

### 4.2 Intersection

Elements common to both sets:

```python
print(A & B)  # {3}
print(A.intersection(B))
```

---

### 4.3 Difference

Elements in one set but not the other:

```python
print(A - B)  # {1, 2}
print(A.difference(B))
```

---

### 4.4 Symmetric Difference

Elements in either set, but not in both:

```python
print(A ^ B)  # {1, 2, 4, 5}
print(A.symmetric_difference(B))
```

---

## 🔹 5. Membership Testing

```python
print(2 in A)   # True
print(5 in A)   # False
print(5 not in A)  # True
```

* **Very fast** → O(1) on average

---

## 🔹 6. Iterating over a Set

```python
for fruit in fruits:
    print(fruit)
```

* Iteration order is **arbitrary**, since sets are unordered.

---

## 🔹 7. Set Comprehensions

Like list comprehensions, but produce a set:

```python
squared = {x**2 for x in range(5)}
print(squared)  # {0, 1, 4, 9, 16}
```

---

## 🔹 8. Frozenset

An **immutable version of set**:

```python
fs = frozenset([1, 2, 3])
# fs.add(4) ❌ → TypeError
```

* Can be used as **dict keys** or in other sets

---

## 🔹 9. Use Cases for Sets

1. Remove duplicates from a list:

```python
nums = [1, 2, 2, 3, 4, 4]
unique_nums = list(set(nums))
```

2. Fast membership testing:

```python
lookup = {'apple', 'banana', 'cherry'}
if 'apple' in lookup:
    print("Found")
```

3. Mathematical operations (union, intersection, difference):

```python
students_a = {'Alice', 'Bob', 'Charlie'}
students_b = {'Bob', 'Diana'}
common = students_a & students_b  # {'Bob'}
```

4. Graph algorithms, caching, or any case where uniqueness matters.

---

### 🔹 Summary

| Feature         | Set  | List   | Tuple  |
| --------------- | ---- | ------ | ------ |
| Ordered         | ❌    | ✅      | ✅      |
| Mutable         | ✅    | ✅      | ❌      |
| Duplicates      | ❌    | ✅      | ✅      |
| Indexing        | ❌    | ✅      | ✅      |
| Membership Test | Fast | Slower | Slower |

---
