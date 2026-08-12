A hash map + min-heap with **lazy expiration** is a clean design that gives **O(log n)** writes and amortized efficient cleanup.

### Design

* **HashMap**: `key -> (value, expire_time)`
* **Min Heap**: `(expire_time, key)`

  * Always keeps the earliest expiration at the top.
* **Lazy expiration**

  * We don't remove expired items immediately.
  * Before every `get()` or `put()`, clean the heap:

    * Pop while the top is expired.
    * Ignore stale heap entries (old expiration timestamps).

### Complexity

| Operation | Time                       |
| --------- | -------------------------- |
| put       | O(log n)                   |
| get       | O(log n) amortized         |
| cleanup   | O(log n) per removed entry |
| space     | O(n)                       |

---

## Implementation

```python
import heapq
import time


class TTLCache:
    def __init__(self):
        self.cache = {}          # key -> (value, expire_time)
        self.heap = []           # (expire_time, key)

    def _cleanup(self):
        now = time.time()

        while self.heap and self.heap[0][0] <= now:
            expire_time, key = heapq.heappop(self.heap)

            # Skip stale heap entries
            if key not in self.cache:
                continue

            value, current_expire = self.cache[key]

            # Expiration changed since this heap entry
            if current_expire != expire_time:
                continue

            del self.cache[key]

    def put(self, key, value, ttl):
        self._cleanup()

        expire_time = time.time() + ttl

        self.cache[key] = (value, expire_time)
        heapq.heappush(self.heap, (expire_time, key))

    def get(self, key):
        self._cleanup()

        if key not in self.cache:
            return None

        return self.cache[key][0]

    def __contains__(self, key):
        self._cleanup()
        return key in self.cache

    def __len__(self):
        self._cleanup()
        return len(self.cache)
```

---

## Example

```python
cache = TTLCache()

cache.put("a", 100, ttl=2)
cache.put("b", 200, ttl=5)

print(cache.get("a"))   # 100

time.sleep(3)

print(cache.get("a"))   # None
print(cache.get("b"))   # 200
```

---

## Why Lazy Expiration?

Suppose:

```
put("x", ttl=10)
put("x", ttl=20)
```

The heap now contains

```
(10, x)
(20, x)
```

The hash map contains only

```
x -> expire=20
```

When `(10, x)` reaches the top:

```
heap expiry = 10
map expiry  = 20
```

Since they don't match, it's an **outdated heap entry**, so we discard it without deleting the cache entry.

Later, when `(20, x)` reaches the top:

```
heap expiry = 20
map expiry  = 20
```

Now it is the current expiration, so we remove it from the cache.

This technique avoids the need to delete arbitrary elements from the heap (which would be O(n)) while keeping all operations at **O(log n)** amortized time.
