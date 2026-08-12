```python
class Node:
    def __init__(self, key, value):
        self.key = key
        self.value = value
        self.freq = 1
        self.prev = None
        self.next = None


class DoublyLinkedList:
    def __init__(self):
        self.head = Node(-1, -1)
        self.tail = Node(-1, -1)
        self.head.next = self.tail
        self.tail.prev = self.head
        self.size = 0

    def add_front(self, node):
        node.next = self.head.next
        node.prev = self.head
        self.head.next.prev = node
        self.head.next = node
        self.size += 1

    def remove(self, node):
        node.prev.next = node.next
        node.next.prev = node.prev
        self.size -= 1

    def remove_lru(self):
        if self.size == 0:
            return None
        node = self.tail.prev
        self.remove(node)
        return node


class LFUCache:
    def __init__(self, capacity):
        self.capacity = capacity
        self.size = 0
        self.min_freq = 0

        self.key_map = {}     # key -> Node
        self.freq_map = {}    # freq -> DoublyLinkedList

    def _update(self, node):
        freq = node.freq
        dll = self.freq_map[freq]
        dll.remove(node)

        if dll.size == 0:
            del self.freq_map[freq]
            if self.min_freq == freq:
                self.min_freq += 1

        node.freq += 1

        if node.freq not in self.freq_map:
            self.freq_map[node.freq] = DoublyLinkedList()

        self.freq_map[node.freq].add_front(node)

    def get(self, key):
        if key not in self.key_map:
            return -1

        node = self.key_map[key]
        self._update(node)
        return node.value

    def put(self, key, value):
        if self.capacity == 0:
            return

        if key in self.key_map:
            node = self.key_map[key]
            node.value = value
            self._update(node)
            return

        if self.size == self.capacity:
            lru = self.freq_map[self.min_freq].remove_lru()
            del self.key_map[lru.key]

            if self.freq_map[self.min_freq].size == 0:
                del self.freq_map[self.min_freq]

            self.size -= 1

        node = Node(key, value)
        self.key_map[key] = node

        if 1 not in self.freq_map:
            self.freq_map[1] = DoublyLinkedList()

        self.freq_map[1].add_front(node)

        self.min_freq = 1
        self.size += 1
```

### Properties

* **`get`**: O(1) average
* **`put`**: O(1) average
* **Space**: O(capacity)
* **Tie-breaking**: LRU within the same frequency (the least recently used node is always removed from the tail of the corresponding frequency list).
