Excellent. These are exactly the kinds of follow-up questions that often come after implementing a basic priority scheduler.

We'll build a production-style scheduler in Python with these features:

1. ✅ Add a task
2. ✅ Execute the highest-priority task
3. ✅ Update a task's priority
4. ✅ Cancel a task
5. ✅ FIFO ordering for tasks with the same priority

---

# Challenge 1: Why the Basic Heap Isn't Enough

Python's `heapq` supports:

```python
heappush()
heappop()
```

But it **does not** support:

* Remove an arbitrary task
* Update an existing task

Searching the heap would take **O(n)**, which defeats the purpose.

---

# Solution: Add an Index

We'll maintain two data structures:

```text
               Scheduler

          +-------------------+
          |      Heap         |
          +-------------------+
             (-10,0,Task2)
             (-8,1,Task4)
             (-4,2,Task1)

                    |
                    |
                    v

          +-------------------+
          | task_map          |
          +-------------------+
          |1 -> Task1|
          |2 -> Task2|
          |4 -> Task4|
```

* Heap → efficient scheduling
* Dictionary → fast lookup by ID

---

# Step 1: Task Class

```python
from dataclasses import dataclass

@dataclass
class Task:
    task_id: int
    priority: int
    name: str
```

---

# Step 2: Scheduler

```python
import heapq

class TaskScheduler:

    def __init__(self):
        self.heap = []
        self.task_map = {}
        self.counter = 0
```

### Why `counter`?

Suppose:

```
Task A priority 10

Task B priority 10
```

Which executes first?

Without a tie-breaker, ordering is undefined.

We'll use insertion order.

---

# Heap Entry

Each heap element is:

```text
(-priority,
 insertion_order,
 task)
```

Example

```
(-10,0,Payment)

(-10,1,Email)

(-5,2,Backup)
```

The smaller tuple comes first.

Since priorities are negated:

```
-10 < -5
```

Higher priorities are returned first.

---

# Add Task

```python
def add_task(self, task_id, priority, name):

    task = Task(task_id, priority, name)

    self.task_map[task_id] = task

    heapq.heappush(
        self.heap,
        (-priority, self.counter, task)
    )

    self.counter += 1
```

Complexity

```
O(log n)
```

---

# Execute Task

```python
def execute_next(self):

    while self.heap:

        neg_priority, order, task = heapq.heappop(self.heap)

        if task.task_id in self.task_map:
            del self.task_map[task.task_id]
            return task

    return None
```

Notice the `while`.

It will become important when we discuss cancellation.

---

# Peek

```python
def peek(self):

    while self.heap:

        _, _, task = self.heap[0]

        if task.task_id in self.task_map:
            return task

        heapq.heappop(self.heap)

    return None
```

Complexity

```
O(1)
```

(amortized, with occasional cleanup of invalid entries)

---

# Follow-up 1: Cancel Task

Removing from the middle of a heap is expensive.

Instead:

```python
del self.task_map[task_id]
```

That's it.

```python
def cancel_task(self, task_id):

    if task_id in self.task_map:
        del self.task_map[task_id]
```

The heap still contains the old entry.

Example

```
Heap

Task 10

Task 8

Task 5
```

Cancel

```
Task 8
```

Heap becomes

```
Task10

Task8  ← stale

Task5
```

When popped,

the scheduler checks

```python
if task.task_id in task_map
```

If not,

it skips it.

This technique is called **lazy deletion**.

Complexity

```
O(1)
```

---

# Follow-up 2: Update Priority

Heaps cannot modify elements in place efficiently.

Instead:

Remove the old task logically.

Insert a new version.

```python
def update_priority(self, task_id, new_priority):

    if task_id not in self.task_map:
        return

    task = self.task_map[task_id]

    del self.task_map[task_id]

    self.add_task(
        task_id,
        new_priority,
        task.name
    )
```

Example

```
Email

Priority 4
```

becomes

```
Email

Priority 20
```

The old heap entry remains but is ignored when encountered because it was removed from `task_map`.

Complexity

```
O(log n)
```

---

# Follow-up 3: FIFO for Same Priority

Suppose

```
Task A priority 10

Task B priority 10

Task C priority 10
```

Desired order

```
A

B

C
```

The heap tuple

```python
(-priority, counter, task)
```

achieves this automatically.

Example

```
(-10,0,A)

(-10,1,B)

(-10,2,C)
```

Since the priorities are equal, the heap compares the second field (`counter`), preserving insertion order.

---

# Complete Scheduler

```python
import heapq
from dataclasses import dataclass


@dataclass
class Task:
    task_id: int
    priority: int
    name: str


class TaskScheduler:

    def __init__(self):
        self.heap = []
        self.task_map = {}
        self.counter = 0

    def add_task(self, task_id, priority, name):
        task = Task(task_id, priority, name)
        self.task_map[task_id] = task
        heapq.heappush(
            self.heap,
            (-priority, self.counter, task)
        )
        self.counter += 1

    def execute_next(self):
        while self.heap:
            _, _, task = heapq.heappop(self.heap)

            if task.task_id in self.task_map:
                del self.task_map[task.task_id]
                return task

        return None

    def peek(self):
        while self.heap:
            _, _, task = self.heap[0]

            if task.task_id in self.task_map:
                return task

            heapq.heappop(self.heap)

        return None

    def cancel_task(self, task_id):
        self.task_map.pop(task_id, None)

    def update_priority(self, task_id, new_priority):
        if task_id not in self.task_map:
            return

        task = self.task_map[task_id]
        del self.task_map[task_id]

        self.add_task(
            task_id,
            new_priority,
            task.name
        )
```

---

# Example

```python
scheduler = TaskScheduler()

scheduler.add_task(1, 5, "Email")
scheduler.add_task(2, 10, "Payment")
scheduler.add_task(3, 2, "Backup")

scheduler.update_priority(1, 20)

scheduler.cancel_task(3)

while True:
    task = scheduler.execute_next()

    if task is None:
        break

    print(task)
```

Output:

```text
Task(task_id=1, priority=20, name='Email')
Task(task_id=2, priority=10, name='Payment')
```

The canceled task is skipped, and the updated priority is honored.

---

## Complexity Summary

| Operation         | Time                 | Notes                                                     |
| ----------------- | -------------------- | --------------------------------------------------------- |
| `add_task`        | `O(log n)`           | Heap insertion                                            |
| `peek`            | `O(1)` amortized     | May discard stale entries                                 |
| `execute_next`    | `O(log n)` amortized | Heap removal plus lazy cleanup                            |
| `cancel_task`     | `O(1)`               | Dictionary removal only                                   |
| `update_priority` | `O(log n)`           | Lazy delete + new heap entry                              |
| Space             | `O(n)`               | Active tasks plus any stale heap entries awaiting cleanup |

This pattern—**heap + hash map + lazy deletion**—is widely used in production systems such as job schedulers, timer queues, and event loops because it avoids expensive heap mutations while keeping common operations efficient.

This is the key insight behind **lazy deletion**. Let's visualize it.

## Step 1: Add a task

```python
scheduler.add_task(1, 5, "Email")
```

We create a `Task` object:

```python
old_task = Task(1, 5, "Email")
```

Heap:

```text
(-5, old_task)
```

Dictionary:

```text
{
    1 -> old_task
}
```

Notice the dictionary stores a **reference to the exact object**, not just its data.

```
          task_map
       +------------+
1 ----> | old_task  |
       +------------+

Heap
+----------------+
| (-5, old_task) |
+----------------+
```

Both point to the **same object**.

---

## Step 2: Update the priority

Now we call:

```python
update_priority(1, 20)
```

Instead of modifying `old_task`, we create a **new object**.

```python
new_task = Task(1, 20, "Email")
```

Update the dictionary:

```python
task_map[1] = new_task
```

Heap becomes:

```text
(-20, new_task)
(-5, old_task)
```

Dictionary:

```text
{
    1 -> new_task
}
```

Diagram:

```
Heap

(-20, new_task)
(-5, old_task)

task_map

1 ----> new_task
```

Notice:

* `old_task` is still in the heap.
* The dictionary **no longer points to it**.

---

## Step 3: Pop from the heap

Suppose the heap pops:

```python
task = old_task
```

Now we check:

```python
if self.task_map.get(task.task_id) is not task:
    continue
```

Substitute the values:

```python
if new_task is not old_task:
```

Python compares **object identity**.

```
new_task  ---> memory address 0x2000

old_task  ---> memory address 0x1000
```

Different objects.

So:

```python
new_task is old_task
```

returns

```python
False
```

Therefore:

```python
continue
```

The task is skipped because it is **stale**.

---

## Why `is` and not `==`?

`==` compares values.

```python
Task(1,5,"Email") == Task(1,5,"Email")
```

may return `True` (especially with dataclasses).

But we don't care whether two tasks have the same values.

We care whether this heap entry is **the current active object**.

`is` compares identity:

```python
old_task is new_task
```

Always:

```python
False
```

---

## Think of it like a pointer

The dictionary always points to the **latest version**.

```
Before update

task_map
   |
   v
old_task

After update

task_map
   |
   v
new_task

old_task
^
|
still inside heap
```

When the scheduler pops `old_task`, it asks:

> "Is this the same object the dictionary currently points to?"

Answer:

```
No.
```

So it's stale.

---

## General Rule

A heap entry is considered **stale** if it is **not the current object associated with that task ID**.

That's exactly what this line checks:

```python
if self.task_map.get(task.task_id) is not task:
    continue
```

* **Same object (`is`)** → this is the latest version → execute it.
* **Different object** → a newer version has replaced it → skip it.

This pattern is used in production systems because it lets updates remain **O(log n)** without needing to search through and modify the heap.

Great question. **You *can* use reference identity in Java.** In fact, Java's `==` on objects compares references (identity), just like Python's `is`.

The real question is: **should you?**

Let's compare them.

---

# Reference Identity in Java

```java
Task oldTask = new Task(1, 5);

Task newTask = new Task(1, 20);

Map<Integer, Task> taskMap = new HashMap<>();
taskMap.put(1, newTask);

if (taskMap.get(1) != oldTask) {
    // stale
}
```

This works because

```java
!=
```

compares object references.

Memory-wise:

```
oldTask  --------> Task(id=1, priority=5)

newTask  --------> Task(id=1, priority=20)

taskMap[1] ------> newTask
```

When `oldTask` is popped from the heap:

```
taskMap.get(1) != oldTask
```

becomes

```
newTask != oldTask
```

which is `true`.

So yes—it works.

---

# So why do many Java engineers prefer versions?

Because **reference identity couples correctness to object lifetime**.

Imagine six months later another developer writes:

```java
Task t = taskMap.get(id);

t.setPriority(20);
```

Instead of creating a new object, they **mutate** the existing one.

Now:

```
Heap
----
Task(priority=5)  <-- same object

Dictionary
----------
same object
```

Except the object now says

```
priority = 20
```

The heap is now inconsistent because **changing a key inside a heap does not reorder the heap**.

Your identity check still passes because it's the same object, but the heap property has been broken.

With immutable tasks (never modifying a `Task` after inserting it), this problem disappears—but immutability is a discipline that has to be maintained.

---

# Version Numbers Are Explicit

Suppose every task has

```java
class Task {
    int id;
    int priority;
    int version;
}
```

Heap:

```
Task(id=1, version=1)
```

Update:

```
Task(id=1, version=2)
```

Dictionary:

```
1 -> version 2
```

When the heap pops version 1:

```
1 != 2
```

Skip it.

Nobody needs to know anything about references.

---

# Readability

Imagine you're reviewing code.

Reference approach:

```java
if (taskMap.get(task.id) != task)
```

Someone unfamiliar with the pattern may ask:

> "Why are we comparing references instead of IDs?"

Now compare:

```java
if (task.version != latestVersion.get(task.id))
```

Immediately understandable:

> "Old version? Skip it."

Version numbers communicate intent more clearly.

---

# Distributed Systems

Suppose your scheduler runs on multiple machines.

Machine A:

```
Task object
```

Machine B:

```
Same task reconstructed from JSON
```

The references are different.

```
oldTask == newTask
```

is meaningless across JVMs.

Versions survive serialization.

```
Version 4
```

still equals

```
Version 4
```

on another machine.

---

# Serialization

Imagine saving tasks to disk.

Reference identity:

```
0xABC123
```

After restarting the JVM:

```
0xABC123
```

no longer exists.

Version:

```
7
```

Still works.

---

# Equality Can Change

Suppose someone overrides

```java
equals()
hashCode()
```

for `Task`.

Reference identity ignores that.

Sometimes that's good.

Sometimes it confuses readers because

```
task1.equals(task2)
```

may be true while

```
task1 == task2
```

is false.

Version numbers avoid this distinction entirely.

---

# Performance

Practically identical.

Reference comparison:

```
pointer == pointer
```

Version comparison:

```
int == int
```

Both are constant-time (`O(1)`) operations with negligible cost.

---

# Summary

| Aspect                            | Reference Identity | Version Counter           |
| --------------------------------- | ------------------ | ------------------------- |
| Time complexity                   | O(1)               | O(1)                      |
| Extra memory                      | None               | One integer per task      |
| Simple to implement               | ✅                  | Slightly more bookkeeping |
| Easy to understand                | Less obvious       | More explicit             |
| Works after serialization         | ❌                  | ✅                         |
| Works across JVMs/services        | ❌                  | ✅                         |
| Depends on immutable task objects | Yes                | No                        |

### Which would I choose?

* **Single-process, in-memory scheduler with immutable `Task` objects:** Reference identity is perfectly valid and concise.
* **Production systems, distributed services, persisted queues, or codebases with many contributors:** I'd choose **version counters**. They make the notion of "latest task" explicit, don't rely on object identity, and remain correct across serialization, process boundaries, and language implementations.

So the difference isn't that Java *can't* use reference identity—it absolutely can. The trade-off is between a compact implementation that relies on object identity and immutability, versus a slightly more explicit implementation whose correctness is easier to reason about and that scales better to more complex systems.
