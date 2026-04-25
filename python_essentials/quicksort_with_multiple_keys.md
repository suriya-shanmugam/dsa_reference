# 1. Basic Quicksort (Single Key)

### Idea

Quicksort is a **divide-and-conquer** algorithm:

1. Pick a **pivot**
2. Partition into:

   * elements **less than pivot**
   * elements **greater than or equal to pivot**
3. Recursively sort both sides

---

### Example

```python
arr = [8, 3, 1, 7, 0, 10, 2]
```

Pick pivot = `7`

Partition:

* Left: `[3, 1, 0, 2]`
* Right: `[8, 10]`

Repeat until sorted.

---

### Simple Implementation

```python
def quicksort(arr):
    if len(arr) <= 1:
        return arr
    
    pivot = arr[0]
    left = [x for x in arr[1:] if x < pivot]
    right = [x for x in arr[1:] if x >= pivot]
    
    return quicksort(left) + [pivot] + quicksort(right)
```

---

# 2. Extending to Multiple Keys

### Problem

Now elements have multiple attributes.

Example:

```python
people = [
    ("Alice", 25),
    ("Bob", 20),
    ("Charlie", 25),
    ("Dave", 20)
]
```

### Goal

Sort by:

1. Age
2. Name

---

### Key Insight

Quicksort does not change.

> Only the **comparison** changes.

---

# 3. Using Tuple as a Composite Key

We combine multiple fields into a single tuple:

```python
(age, name)
```

So each element gets a key like:

```python
("Alice", 25) → (25, "Alice")
```

---

### Modified Quicksort

```python
def quicksort(arr):
    if len(arr) <= 1:
        return arr
    
    pivot = arr[0]
    pivot_key = (pivot[1], pivot[0])  # (age, name)
    
    left = []
    right = []
    
    for x in arr[1:]:
        key = (x[1], x[0])
        if key < pivot_key:
            left.append(x)
        else:
            right.append(x)
    
    return quicksort(left) + [pivot] + quicksort(right)
```

---

# 4. Example Walkthrough

Initial:

```python
[("Alice",25), ("Bob",20), ("Charlie",25), ("Dave",20)]
```

### Step 1: Pivot

`("Alice",25)` → key `(25, "Alice")`

### Step 2: Partition

Compare using tuple keys:

* ("Bob",20) → (20,"Bob") < (25,"Alice") → left
* ("Charlie",25) → (25,"Charlie") > (25,"Alice") → right
* ("Dave",20) → (20,"Dave") < (25,"Alice") → left

Result:

```python
left  = [("Bob",20), ("Dave",20)]
right = [("Charlie",25)]
```

Continue recursively.

---

# 5. How Tuple Comparison Works Internally

When comparing:

```python
(x1, y1) < (x2, y2)
```

Python performs:

```python
for a, b in zip((x1, y1), (x2, y2)):
    if a < b:
        return True
    elif a > b:
        return False

return len(tuple1) < len(tuple2)
```

---

### Step-by-step Example

```python
(25, "Alice") < (25, "Charlie")
```

1. Compare `25` vs `25` → equal
2. Compare `"Alice"` vs `"Charlie"` → `"Alice"` is smaller
3. Return True

---

# 6. Key Properties of Tuple Comparison

1. Comparison is **left to right**
2. Stops at the **first difference**
3. Uses each element’s own comparison
4. If all equal → shorter tuple is smaller
5. Fails if elements are not comparable

---

# 7. Why This Works for Multiple Keys

Tuple structure encodes priority:

```python
(age, name)
```

Means:

* First compare age
* If equal → compare name

No extra logic needed.

---

# 8. Descending Order Variation

To sort by:

* Age descending
* Name ascending

Use:

```python
(-age, name)
```

---

# 9. Interview Summary

* Quicksort logic remains unchanged
* Replace single value comparison with **tuple comparison**
* Tuple comparison is **lexicographic**
* Efficient due to **early stopping (short-circuiting)**

---

# 10. Memory Shortcut

* Quicksort: “Pick → Partition → Recurse”
* Multiple keys: “Combine into tuple”
* Tuple: “Compare left to right, first difference decides”
