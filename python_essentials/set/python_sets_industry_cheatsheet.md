# Python Sets — the essentials

## What they are
- **Unordered**, **unique** collection of **hashable** items (backed by a hash table).
- Average **O(1)** membership tests and updates.
- Two flavors:
  - `set` — mutable.
  - `frozenset` — immutable & hashable (can be dict keys or elements of other sets).

```python
s = {1, 2, 3}          # literal
s = set([1, 2, 3])     # from iterable
fs = frozenset({1, 2}) # immutable
```

## Core operations (and operator twins)
```python
a | b        # union               a.union(b, c, ...)
a & b        # intersection        a.intersection(b, ...)
a - b        # difference          a.difference(b, ...)
a ^ b        # symmetric diff      a.symmetric_difference(b)

a |= b       # in-place union      a.update(b)
a &= b       # in-place intersect  a.intersection_update(b)
a -= b       # in-place diff       a.difference_update(b)
a ^= b       # in-place symdiff    a.symmetric_difference_update(b)

a < b        # proper subset       a.issubset(b) and a != b
a <= b       # subset              a.issubset(b)
a > b        # proper superset     a.issuperset(b) and a != b
a >= b        # superset           a.issuperset(b)
a.isdisjoint(b)
```

## Handy methods you’ll reach for
```python
s.add(x)         # add one item
s.update(iter)   # add many
s.remove(x)      # KeyError if missing
s.discard(x)     # safe remove (no error)
s.pop()          # remove & return an arbitrary element
s.clear()
s.copy()
```

## Comprehensions & typing
```python
squares = {n*n for n in range(10) if n % 2 == 0}

# Type hints (PEP 585 — prefer builtins)
def f(ids: set[int]) -> frozenset[str]:
    ...
```

## Common industry scenarios

1. **Fast membership / “is in the catalog?”**
```python
allowed_ext = {".jpg", ".png", ".gif"}
if ext in allowed_ext: ...
```

2. **De‑duplication (large streams)**
```python
seen = set()
for row in rows:
    if row.id in seen: continue
    seen.add(row.id); process(row)
```

3. **Dedup while preserving original order**
```python
def dedup_keep_order(xs):
    seen, out = set(), []
    for x in xs:
        if x not in seen:
            seen.add(x); out.append(x)
    return out
```

4. **Set algebra as “mini SQL”**
```python
active_users = set(api_active_ids())
paying_users = set(db_paying_ids())
churn_risk = active_users - paying_users
cross_sell = paying_users & set(new_feature_beta_ids)
```

5. **Permissions / feature flags**
```python
user_perms = roles["analyst"] | roles["viewer"]
if {"export", "share"}.issubset(user_perms): ...
```

6. **Text processing**
```python
stop = {"the", "a", "of", "and"}
tokens = [t for t in tokenize(text) if t not in stop]
```

7. **Graph/relationships (unique neighbors)**
```python
adj: dict[int, set[int]] = defaultdict(set)
adj[u].add(v); adj[v].add(u)
```

8. **Uniqueness checks**
```python
def all_unique(xs) -> bool:
    return len(xs) == len(set(xs))
```

9. **Config diffs / audits**
```python
expected = set(load_expected_keys())
actual   = set(cfg.keys())
missing  = expected - actual
extra    = actual - expected
```

10. **Immutability needed (nested sets / dict keys)**
```python
edges = {frozenset({u, v}) for (u, v) in undirected_edge_list}
cache = {frozenset(params.items()): result}
```

## Performance notes that matter
- Membership & insert/delete: **amortized O(1)**; intersection/union roughly linear in the smaller operand.
- Prefer set literals for small, constant membership tests (faster than lists/tuples).
- Iteration order is **arbitrary** (don’t rely on it). Use `for x in sorted(s):` if you need determinism.
- Sets have **nontrivial memory overhead**. For very compact boolean presence, consider bit arrays/`array`/`numpy`/`pyroaring` (domain‑specific).

## Pitfalls & pro tips
- **Unhashable elements:** lists/dicts aren’t allowed. Use tuples/frozensets instead.
  ```python
  s = {("x", 1), ("y", 2)}               # ok
  s = {frozenset({"read", "write"})}     # ok
  ```
- **Custom objects:** implement `__hash__` and `__eq__` consistently or membership will be wrong.
- **Don’t mutate while iterating.** Iterate over a snapshot: `for x in s.copy(): ...`
- **`remove` vs `discard`:** prefer `discard` when absence is normal.
- **`default` args:** never use `set()` as a default parameter (mutables!). Use `None` + init.
  ```python
  def f(opts=None):
      opts = set() if opts is None else set(opts)
  ```
- **JSON serialization:** sets aren’t JSON‑serializable; convert to list (optionally `sorted`) before dumping.
- **NaN weirdness:** `float('nan') != float('nan')`, so multiple NaNs can coexist in a set; be cautious in data cleaning.

## Micro‑recipes

- **Fast intersection of many sets (smallest first)**
```python
from functools import reduce
def intersect_all(*sets):
    sets = sorted(sets, key=len)
    return reduce(set.intersection, sets) if sets else set()
```

- **Top‑k unique in stream**
```python
def first_k_unique(iterable, k):
    out, seen = [], set()
    for x in iterable:
        if x not in seen:
            seen.add(x); out.append(x)
            if len(out) == k: break
    return out
```

- **Compute duplicates (values that occur >1)**
```python
def duplicates(xs):
    seen, dup = set(), set()
    for x in xs:
        (dup if x in seen else seen).add(x)
    return dup
```

- **Symmetric diff for “changed keys”**
```python
changed = old_keys ^ new_keys
```

- **Disjoint check for constraint validation**
```python
if not required.isdisjoint(forbidden): raise ValueError("Conflicting options")
```

## Testing & debugging tips
- Compare sets directly in tests (order‑insensitive):
  ```python
  assert set(func(ids)) == {"a", "b", "c"}
  ```
- When failures are hard to read, render deterministically:
  ```python
  assert sorted(actual_set) == ["a", "b", "c"]
  ```
