# Python Dictionaries / Maps — Practical Notes

> Target: day-to-day, interview-ready, production-grade usage. Python ≥ 3.9

---

## 1) Core Concepts

- **Dictionary**: hash table mapping *hashable* keys → values.
- **Insertion order preserved** (since 3.7 CPython, guaranteed by language spec): iterate in the order keys were added.
- **Average-time ops**: O(1) for lookup/insert/update/delete; resizing happens occasionally.
- **Hashable keys**: immutable and implement stable `__hash__` and `__eq__` (e.g., `str`, `int`, `tuple` of hashables).

```python
# creation
user = {"id": 42, "name": "Ada"}
empty = {}
from_pairs = dict([("a", 1), ("b", 2)])
from_kwargs = dict(a=1, b=2)
comp = {k: k*k for k in range(5)}
```

---

## 2) Everyday Methods & Idioms

### Access with default
```python
# get with fallback
country = user.get("country", "US")

# setdefault: fetch-or-initialize in one go
index = {}
index.setdefault("python", []).append(101)
```

### Safe popping
```python
# pop with default (avoid KeyError)
val = user.pop("middle_name", None)

# popitem: LIFO remove (useful for stack-like drains)
key, value = user.popitem()
```

### Merging & updating (3.9+)
```python
base = {"host": "localhost", "port": 5432}
override = {"port": 6432}
merged = base | override           # new dict
base |= override                   # in-place update
```

### Iteration best practices
```python
for k, v in user.items():
    ...

# avoid recomputing lookups
for key in data:
    val = data[key]
    ...

# don’t mutate size during iteration – iterate on a snapshot
for k, v in list(cache.items()):
    if expired(v):
        cache.pop(k)
```

### Sorting views (without changing dict)
```python
for k in sorted(d):
    ...
for k, v in sorted(d.items(), key=lambda kv: kv[1], reverse=True):
    ...
```

### Inverting a map
```python
# works if values are unique & hashable
inv = {v: k for k, v in d.items()}

# when values repeat → map to sets/lists
from collections import defaultdict
groups = defaultdict(set)
for k, v in d.items():
    groups[v].add(k)
```

### Grouping / bucketing
```python
from collections import defaultdict
by_country = defaultdict(list)
for user in users:
    by_country[user.country].append(user)
```

### Frequency counts
```python
from collections import Counter
counts = Counter(words)
counts.most_common(10)
```

### Using dict as a dispatch table (switch-on-string)
```python
def handle_csv(): ...
def handle_json(): ...

dispatch = {
    "csv": handle_csv,
    "json": handle_json,
}

handler = dispatch.get(fmt, lambda: (_ for _ in ()).throw(ValueError("unsupported")))
handler()
```

---

## 3) `collections` Power Tools

### `defaultdict`
- Auto-creates a default value on missing key via a factory.
```python
from collections import defaultdict
index = defaultdict(list)
index["py"].append(101)
```

### `Counter`
- Bags/multisets with arithmetic.
```python
from collections import Counter
c1, c2 = Counter("banana"), Counter("bandana")
(c1 + c2), (c1 - c2), (c1 & c2), (c1 | c2)
```

### `OrderedDict`
- Mostly superseded by built-in `dict` preserving order.
- Still useful for `move_to_end` and LRU-style algorithms.
```python
from collections import OrderedDict
cache = OrderedDict()
cache["a"] = 1
cache.move_to_end("a", last=True)
```

### `ChainMap`
- Layer multiple dicts as a read-through mapping (e.g., env → defaults).
```python
from collections import ChainMap
settings = ChainMap(env_vars, user_cfg, default_cfg)
value = settings["timeout"]
```

---

## 4) Mapping Interfaces & Typing

- **Protocols / ABCs**: `collections.abc.Mapping`, `MutableMapping` define the mapping contract.
- **Typing**: prefer `Mapping[K, V]` for read-only views; `MutableMapping[K, V]` or `dict[K, V]` for mutable.
- **Read-only view of a dict**: `types.MappingProxyType` wraps a dict to prevent mutation.

```python
from collections.abc import Mapping, MutableMapping
from types import MappingProxyType
from typing import Mapping as TMapping

def f(cfg: TMapping[str, int]) -> None: ...

config = {"retries": 3}
ro = MappingProxyType(config)
# ro["retries"] = 5  # TypeError
```

---

## 5) Performance Notes

- **O(1)** average ops; collisions degrade but are rare in practice.
- **Pre-size when possible**: if you know N, a dict comp/comprehension is efficient.
- **Avoid repeated hashing**: store lookups (`val = d[key]`) if the key is reused in hot loops.
- **Use tuples for compound keys**: `cache[(user_id, date)] = ...`.
- **Prefer `defaultdict` over `setdefault` in tight loops**: fewer Python bytecodes.
- **Memory**: dicts are memory-heavy; consider arrays or `dataclasses` for dense data.

Micro-optimizations should be measured with `timeit` before committing.

---

## 6) Mutability, Hashability, and Equality

- Keys must be **immutable** and **hashable**.
- Custom classes used as keys must define consistent `__hash__` and `__eq__`.
- Changing a key object’s fields that participate in the hash after insertion **breaks** the table.

```python
@dataclass(frozen=True)  # frozen dataclass is hashable by default (if fields are)
class Point:
    x: int
    y: int

hits = {Point(1, 2): 3}
```

---

## 7) Copying & (De)serialization

```python
# shallow copy
c1 = d.copy()
from_copy = dict(d)

# deep copy
import copy
c2 = copy.deepcopy(d)
```

- **JSON**: keys must be strings; convert non-string keys or map to objects.
```python
import json
json.dumps({"a": 1})           # OK
json.dumps({1: "a"})           # OK in Python (int → JSON string), but consumers may expect strings
json.dumps({(1,2): 3})         # TypeError: keys must be str, int, float, bool, None
```

---

## 8) Common Patterns (Industry Scenarios)

### a) Join-like lookup (index one side)
```python
by_id = {u.id: u for u in users}
rows = [{"user": by_id[row.user_id], **row} for row in rows]
```

### b) LRU cache (tiny, custom)
```python
from collections import OrderedDict

class LRU:
    def __init__(self, cap=128):
        self.cap = cap
        self.d = OrderedDict()
    def get(self, k):
        if k not in self.d: return None
        self.d.move_to_end(k)
        return self.d[k]
    def put(self, k, v):
        if k in self.d:
            self.d.move_to_end(k)
        self.d[k] = v
        if len(self.d) > self.cap:
            self.d.popitem(last=False)
```

### c) Multi-index (compound key)
```python
# (region, sku) → price
price = { (r.id, sku.id): sku.price for r in regions for sku in r.skus }
```

### d) Deduping while preserving order
```python
seen = set()
unique = []
for x in items:
    if x in seen: continue
    seen.add(x)
    unique.append(x)
```

### e) Two-way map (with validation)
```python
left_to_right = {"red": 1, "green": 2}
right_to_left = {v: k for k, v in left_to_right.items()}
assert len(left_to_right) == len(right_to_left)  # ensure bijection
```

### f) Counting / histogram and top-K
```python
from collections import Counter
counts = Counter(events)
for event, n in counts.most_common(5):
    print(event, n)
```

### g) Safe config overlay
```python
from collections import ChainMap
final = ChainMap(cli_args, env, file_cfg, defaults)
```

---

## 9) Gotchas

- Mutating a dict while iterating over it changes size → `RuntimeError`.
- Non-hashable keys (e.g., lists, dicts) are invalid.
- `setdefault` creates the default even if you don’t end up using it; don’t pass heavy constructors directly.
```python
# better
index = defaultdict(list)  # vs. d.setdefault(k, expensive())
```
- Watch out for **mutable default values** shared across keys.
```python
# bad
d = {k: [] for k in range(3)}  # ok; each is distinct
# but
bucket = []
d = dict.fromkeys(range(3), bucket)  # all keys share the same list!
```

---

## 10) Testing & Debugging Tips

```python
assert key in d                               # membership
assert set(d.keys()) == {"a", "b"}
assert d == {**expected}                      # structural equality

# Pretty printing nested dicts
import pprint as pp
pp.pprint(d)
```

---

## 11) Quick Reference

- Create: `{}`, `dict()`, comprehension
- Read: `d[k]`, `d.get(k, default)`
- Write: `d[k] = v`, `update`, `|`, `|=`
- Delete: `del d[k]`, `pop(k[, default])`, `clear()`
- Iterate: `keys()`, `values()`, `items()`
- Group: `defaultdict(list/set)`
- Count: `Counter`
- Merge layers: `ChainMap`
- Read-only: `MappingProxyType`
- Sort views: `sorted(d)`, `sorted(d.items(), key=...)`
```

---
