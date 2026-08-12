# Step 1: What information should each cache entry store?

A cache entry needs more than just a key and value.

Each entry should know:

* key
* value
* frequency
* previous node
* next node

```java
class Node {
    int key;
    int value;
    int freq;

    Node prev;
    Node next;

    Node(int key, int value) {
        this.key = key;
        this.value = value;
        this.freq = 1;          // new node starts with frequency 1
    }
}
```

Why do we store `prev` and `next`?

Because nodes will move frequently between frequency lists. A doubly linked list lets us remove a node in **O(1)** when we already have a reference to it.

---

# Step 2: One Doubly Linked List per Frequency

For every frequency, we'll maintain a list of nodes having that frequency.

Example:

```
Frequency 1

HEAD <-> A <-> B <-> C <-> TAIL
```

```
Frequency 2

HEAD <-> D <-> E <-> TAIL
```

The front contains the least recently used node.

The back contains the most recently used node.

We'll use dummy head and tail nodes to simplify insertion and deletion.

```java
class DoublyLinkedList {

    Node head;
    Node tail;

    int size;

    DoublyLinkedList() {

        head = new Node(0, 0);
        tail = new Node(0, 0);

        head.next = tail;
        tail.prev = head;
    }
}
```

Current structure:

```
head <-------> tail
```

Initially there are no real nodes.

---

# Step 3: Insert at the End

Whenever a node is accessed, it becomes the most recently used within its frequency.

So we insert before `tail`.

```java
void addLast(Node node) {

    Node prev = tail.prev;

    prev.next = node;
    node.prev = prev;

    node.next = tail;
    tail.prev = node;

    size++;
}
```

Example

Before

```
HEAD <-> A <-> B <-> TAIL
```

Insert C

```
HEAD <-> A <-> B <-> C <-> TAIL
```

Constant time.

---

# Step 4: Remove Any Node

Because every node has `prev` and `next`.

```java
void remove(Node node) {

    node.prev.next = node.next;
    node.next.prev = node.prev;

    size--;
}
```

Example

Before

```
HEAD <-> A <-> B <-> C <-> TAIL
```

Remove B

```
HEAD <-> A <-> C <-> TAIL
```

Still O(1).

---

# Step 5: Remove Least Recently Used

The oldest node is always immediately after `head`.

```
HEAD <-> A <-> B <-> C <-> TAIL
```

Remove first

```java
Node removeFirst() {

    if (size == 0)
        return null;

    Node first = head.next;

    remove(first);

    return first;
}
```

Result

```
HEAD <-> B <-> C <-> TAIL
```

Again O(1).

---

# Step 6: Our Main Data Structures

Now we combine everything.

```java
class LFUCache {

    int capacity;

    int minFreq;

    Map<Integer, Node> cache;

    Map<Integer, DoublyLinkedList> freqMap;

    ...
}
```

What does each one store?

### `cache`

```
key
↓

1 -> Node
2 -> Node
5 -> Node
```

Allows

```
get(key)
```

in O(1).

---

### `freqMap`

Maps a frequency to its list.

```
1
↓

HEAD <-> A <-> B <-> TAIL
```

```
2
↓

HEAD <-> C <-> D <-> TAIL
```

```
5
↓

HEAD <-> E <-> TAIL
```

---

### `minFreq`

This is extremely important.

Suppose

```
Freq 1

A
```

```
Freq 2

B C
```

```
Freq 5

D
```

Then

```
minFreq = 1
```

When the cache is full,

we **don't search** for the minimum frequency.

We simply do

```java
freqMap.get(minFreq)
```

That's the trick that avoids an O(n) scan.

---

# Constructor

```java
public LFUCache(int capacity) {

    this.capacity = capacity;

    this.minFreq = 0;

    cache = new HashMap<>();

    freqMap = new HashMap<>();
}
```

At this point we have built all the supporting infrastructure:

* ✅ Node
* ✅ Doubly linked list
* ✅ Hash map from key → node
* ✅ Hash map from frequency → linked list
* ✅ `minFreq` tracker

The only missing pieces are the cache operations:

1. `get(key)` — find the node and increase its frequency.
2. `put(key, value)` — insert/update a key and evict the least frequently used item if the cache is full.
3. A helper method like `updateFrequency(node)` to move a node from one frequency list to the next while keeping `minFreq` correct.

Those three methods complete the LFU cache with **O(1)** `get()` and `put()` operations.
