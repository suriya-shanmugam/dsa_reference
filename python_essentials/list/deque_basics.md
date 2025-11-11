## 🔹 1. What Is `deque`?

`deque` stands for **double-ended queue**.
It is provided by the `collections` module:

```python
from collections import deque
```

### ✅ Key Features:

* **Ordered** (like a list)
* **Mutable**
* **Fast append/pop from both ends** (O(1))
* Supports iteration, indexing, and slicing (partially)

Unlike a list, adding/removing elements at the front is fast (`O(1)`), whereas lists are slow for `insert(0, x)` or `pop(0)` (O(n)).

---

## 🔹 2. Creating a `deque`

```python
from collections import deque

dq = deque([1, 2, 3, 4])
print(dq)  # deque([1, 2, 3, 4])
```

* You can also create an empty deque:

```python
dq = deque()
```

---

## 🔹 3. Adding Elements

### Add to the right (like list append)

```python
dq.append(5)
print(dq)  # deque([1, 2, 3, 4, 5])
```

### Add to the left

```python
dq.appendleft(0)
print(dq)  # deque([0, 1, 2, 3, 4, 5])
```

### Extend multiple elements

```python
dq.extend([6, 7])
dq.extendleft([-2, -1])
print(dq)
# deque([-1, -2, 0, 1, 2, 3, 4, 5, 6, 7])
```

⚠️ Note: `extendleft` adds elements **in reverse order** of the iterable.

---

## 🔹 4. Removing Elements

### Remove from the right

```python
dq.pop()
print(dq)  # removes 7
```

### Remove from the left

```python
dq.popleft()
print(dq)  # removes -1
```

### Remove specific element (like list)

```python
dq.remove(3)
print(dq)
```

### Clear all elements

```python
dq.clear()
print(dq)  # deque([])
```

---

## 🔹 5. Accessing Elements

* You **can index** like a list:

```python
dq = deque([10, 20, 30])
print(dq[0])  # 10
print(dq[-1]) # 30
```

* Slicing **is not supported** directly; convert to list first:

```python
print(list(dq)[0:2])  # [10, 20]
```

---

## 🔹 6. Rotating a deque

`rotate(n)` shifts elements to the right by `n` steps (negative `n` rotates left):

```python
dq = deque([1, 2, 3, 4, 5])
dq.rotate(2)
print(dq)  # deque([4, 5, 1, 2, 3])

dq.rotate(-3)
print(dq)  # deque([2, 3, 4, 5, 1])
```

---

## 🔹 7. Limiting Size

You can create a **deque with a max length**. When full, it discards elements from the opposite end automatically:

```python
dq = deque(maxlen=3)
dq.extend([1, 2, 3])
print(dq)  # deque([1, 2, 3], maxlen=3)

dq.append(4)
print(dq)  # deque([2, 3, 4], maxlen=3)
```

---

## 🔹 8. Iterating

```python
dq = deque([10, 20, 30])
for x in dq:
    print(x)
```

You can also reverse iterate efficiently:

```python
for x in reversed(dq):
    print(x)
```

---

## 🔹 9. Use Cases for `deque`

1. **Queue (FIFO)**:

```python
queue = deque()
queue.append('task1')
queue.append('task2')
task = queue.popleft()
```

2. **Stack (LIFO)**:

```python
stack = deque()
stack.append('a')
stack.append('b')
stack.pop()  # 'b'
```

3. **Sliding window / fixed-length buffer**:

```python
window = deque(maxlen=3)
for i in range(5):
    window.append(i)
    print(window)
```

4. **Fast rotations for circular buffers**:

```python
dq = deque([1,2,3,4,5])
dq.rotate(1)
```

---

### 🔹 Summary of Key Methods

| Method                 | Description                            |
| ---------------------- | -------------------------------------- |
| `append(x)`            | Add to right                           |
| `appendleft(x)`        | Add to left                            |
| `pop()`                | Remove from right                      |
| `popleft()`            | Remove from left                       |
| `extend(iterable)`     | Add multiple to right                  |
| `extendleft(iterable)` | Add multiple to left (reversed)        |
| `rotate(n)`            | Rotate elements                        |
| `clear()`              | Remove all                             |
| `remove(x)`            | Remove first occurrence                |
| `maxlen`               | Fixed-size deque (auto-discard oldest) |

---

`deque` is incredibly versatile for **queues, stacks, sliding windows, and any operation where you need efficient front/back operations**.

---

