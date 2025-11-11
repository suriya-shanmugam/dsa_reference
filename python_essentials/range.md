### 🔹 What `range()` Is

`range()` is a **built-in function** in Python that generates a sequence of numbers.
It’s **lazy**, meaning it doesn’t actually create a list of numbers — it creates an *iterator* that produces numbers on demand.

You’ll usually see it used in loops or when you need a sequence of integer values.

---

### 🔹 Syntax

```python
range(stop)
range(start, stop)
range(start, stop, step)
```

| Parameter | Meaning                                           |
| --------- | ------------------------------------------------- |
| `start`   | The first number in the sequence (default = 0)    |
| `stop`    | The number *just before* which the sequence stops |
| `step`    | The difference between each number (default = 1)  |

---

### 🔹 Basic Examples

#### 1. One argument: `range(stop)`

```python
for i in range(5):
    print(i)
```

**Output:**

```
0
1
2
3
4
```

→ Generates numbers from **0 up to (but not including)** 5.

---

#### 2. Two arguments: `range(start, stop)`

```python
for i in range(2, 6):
    print(i)
```

**Output:**

```
2
3
4
5
```

→ Starts from 2, stops before 6.

---

#### 3. Three arguments: `range(start, stop, step)`

```python
for i in range(0, 10, 2):
    print(i)
```

**Output:**

```
0
2
4
6
8
```

→ Counts by twos.

You can also go *backwards*:

```python
for i in range(10, 0, -1):
    print(i)
```

→ Counts down from 10 to 1.

---

### 🔹 Common Usage Patterns

1. **Looping a fixed number of times**

   ```python
   for _ in range(10):  # underscore = loop variable not used
       print("Hello")
   ```

2. **Looping over indices**

   ```python
   names = ["Alice", "Bob", "Charlie"]
   for i in range(len(names)):
       print(i, names[i])
   ```

3. **Creating numeric lists**

   ```python
   numbers = list(range(5))        # [0, 1, 2, 3, 4]
   evens = list(range(0, 10, 2))   # [0, 2, 4, 6, 8]
   ```

4. **Reverse iteration**

   ```python
   for i in range(5, 0, -1):
       print(i)
   ```

5. **Index-based iteration with enumerate (better pattern)**

   ```python
   for i, name in enumerate(names):
       print(i, name)
   ```

   (This is often better than `range(len(...))`.)

---

### 🔹 Performance Note

`range()` is **memory efficient** because it doesn’t store all numbers — it computes them on demand.
Compare:

```python
range(1_000_000)   # lightweight
list(range(1_000_000))  # uses lots of memory
```

---

### 🔹 Summary Table

| Use Case     | Example                 | Output            |
| ------------ | ----------------------- | ----------------- |
| Basic range  | `list(range(5))`        | `[0, 1, 2, 3, 4]` |
| Custom start | `list(range(2, 6))`     | `[2, 3, 4, 5]`    |
| Custom step  | `list(range(0, 10, 3))` | `[0, 3, 6, 9]`    |
| Reverse      | `list(range(5, 0, -1))` | `[5, 4, 3, 2, 1]` |

---
