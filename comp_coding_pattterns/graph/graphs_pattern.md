# Graph Problem Decision Tree

```text
Graph Problem
│
├── Traverse all nodes?
│   ├── DFS
│   └── BFS
│
├── Need shortest path?
│   ├── Unweighted → BFS
│   ├── Weighted positive → Dijkstra
│   ├── DAG → Topological + DP
│   └── Negative weights → Bellman-Ford
│
├── Detect cycle?
│   ├── Undirected → DFS / Union Find
│   └── Directed → DFS Colors / Topological
│
├── Dependency ordering?
│   └── Topological Sort
│
├── Connected components?
│   └── DFS / BFS / Union Find
│
├── Minimum Cost Connection?
│   ├── Kruskal
│   └── Prim
│
├── Bipartite?
│   └── BFS Coloring
│
├── All paths?
│   └── Backtracking DFS
│
├── State + Graph?
│   └── BFS with State
│
└── Grid?
    ├── Islands
    ├── Multi-source BFS
    └── Flood Fill
```

---

# 1. DFS Traversal

### Pattern

* Visit all reachable nodes
* Count components
* Explore paths

Time: **O(V+E)**

```python
def dfs(graph, start):
    visited = set()

    def visit(node):
        visited.add(node)

        for nei in graph[node]:
            if nei not in visited:
                visit(nei)

    visit(start)
```

---

# 2. BFS Traversal

### Pattern

* Minimum steps
* Level order
* Unweighted shortest path

```python
from collections import deque

def bfs(graph, start):
    q = deque([start])
    visited = {start}

    while q:
        node = q.popleft()

        for nei in graph[node]:
            if nei not in visited:
                visited.add(nei)
                q.append(nei)
```

---

# 3. Connected Components

Pattern:

> "How many disconnected groups?"

```python
def count_components(graph):
    visited = set()
    count = 0

    def dfs(node):
        visited.add(node)
        for nei in graph[node]:
            if nei not in visited:
                dfs(nei)

    for node in graph:
        if node not in visited:
            dfs(node)
            count += 1

    return count
```

---

# 4. Cycle Detection (Undirected)

```python
def has_cycle(graph):
    visited = set()

    def dfs(node, parent):
        visited.add(node)

        for nei in graph[node]:
            if nei == parent:
                continue

            if nei in visited:
                return True

            if dfs(nei, node):
                return True

        return False

    for node in graph:
        if node not in visited:
            if dfs(node, -1):
                return True

    return False
```

---

# 5. Cycle Detection (Directed)

Use colors.

```python
WHITE = 0
GRAY = 1
BLACK = 2

def has_cycle(graph):
    color = {v: WHITE for v in graph}

    def dfs(node):
        color[node] = GRAY

        for nei in graph[node]:
            if color[nei] == GRAY:
                return True

            if color[nei] == WHITE:
                if dfs(nei):
                    return True

        color[node] = BLACK
        return False

    return any(
        color[node] == WHITE and dfs(node)
        for node in graph
    )
```

---

# 6. Topological Sort

Pattern:

* Course Schedule
* Build Order
* Dependency graph

```python
from collections import deque

def topo_sort(graph):
    indegree = {u: 0 for u in graph}

    for u in graph:
        for v in graph[u]:
            indegree[v] += 1

    q = deque([u for u in graph if indegree[u] == 0])

    order = []

    while q:
        node = q.popleft()
        order.append(node)

        for nei in graph[node]:
            indegree[nei] -= 1
            if indegree[nei] == 0:
                q.append(nei)

    return order
```

---

# 7. Dijkstra

Pattern:

Shortest weighted path.

```python
import heapq

def dijkstra(graph, start):
    dist = {v: float('inf') for v in graph}
    dist[start] = 0

    heap = [(0, start)]

    while heap:
        d, node = heapq.heappop(heap)

        if d > dist[node]:
            continue

        for nei, w in graph[node]:
            nd = d + w

            if nd < dist[nei]:
                dist[nei] = nd
                heapq.heappush(heap, (nd, nei))

    return dist
```

---

# 8. Union Find

Pattern:

* Components
* Cycle detection
* Dynamic connectivity

```python
class UnionFind:

    def __init__(self, n):
        self.parent = list(range(n))
        self.rank = [0]*n

    def find(self, x):
        if self.parent[x] != x:
            self.parent[x] = self.find(self.parent[x])

        return self.parent[x]

    def union(self, x, y):
        px = self.find(x)
        py = self.find(y)

        if px == py:
            return False

        if self.rank[px] < self.rank[py]:
            px, py = py, px

        self.parent[py] = px

        if self.rank[px] == self.rank[py]:
            self.rank[px] += 1

        return True
```

---

# 9. Kruskal MST

```python
def kruskal(n, edges):
    edges.sort(key=lambda x: x[2])

    uf = UnionFind(n)
    cost = 0

    for u, v, w in edges:
        if uf.union(u, v):
            cost += w

    return cost
```

---

# 10. Bipartite Graph

Pattern:

Can graph be colored using two colors?

```python
from collections import deque

def bipartite(graph):
    color = {}

    for start in graph:
        if start in color:
            continue

        color[start] = 0
        q = deque([start])

        while q:
            node = q.popleft()

            for nei in graph[node]:
                if nei not in color:
                    color[nei] = 1 - color[node]
                    q.append(nei)

                elif color[nei] == color[node]:
                    return False

    return True
```

---

# 11. Grid DFS

Pattern:

* Islands
* Flood fill

```python
ROWS = len(grid)
COLS = len(grid[0])

dirs = [(1,0),(-1,0),(0,1),(0,-1)]

def dfs(r,c):

    if r<0 or c<0 or r>=ROWS or c>=COLS:
        return

    if grid[r][c]=='0':
        return

    grid[r][c]='0'

    for dr,dc in dirs:
        dfs(r+dr,c+dc)
```

---

# 12. Multi-source BFS

Pattern:

* Rotten Oranges
* Walls and Gates
* Fire Spread

```python
from collections import deque

q = deque()

for r in range(ROWS):
    for c in range(COLS):
        if grid[r][c] == 2:
            q.append((r,c))

while q:
    r,c = q.popleft()

    for dr,dc in dirs:
        nr,nc = r+dr,c+dc

        if 0<=nr<ROWS and 0<=nc<COLS:
            if grid[nr][nc]==1:
                grid[nr][nc]=2
                q.append((nr,nc))
```

---

# 13. BFS with State

Pattern:

* Shortest path with keys
* Word Ladder
* Sliding Puzzle

```python
from collections import deque

q = deque([(start, initial_state)])
visited = {(start, initial_state)}

while q:
    node, state = q.popleft()

    for nxt, new_state in transitions(node, state):
        if (nxt, new_state) not in visited:
            visited.add((nxt, new_state))
            q.append((nxt, new_state))
```

---

# 14. All Paths (Backtracking)

```python
def all_paths(graph, start, end):

    path = []

    def dfs(node):

        path.append(node)

        if node == end:
            print(path[:])

        else:
            for nei in graph[node]:
                dfs(nei)

        path.pop()

    dfs(start)
```

---

# 15. Bellman-Ford

Pattern:

Negative weights.

```python
def bellman_ford(n, edges, start):
    dist = [float('inf')] * n
    dist[start] = 0

    for _ in range(n - 1):
        for u, v, w in edges:
            if dist[u] != float('inf') and dist[u] + w < dist[v]:
                dist[v] = dist[u] + w

    return dist
```

---

# Pattern Recognition Cheat Sheet

| If the problem says...                         | Use                           |
| ---------------------------------------------- | ----------------------------- |
| Visit everything                               | DFS                           |
| Minimum moves/steps                            | BFS                           |
| Shortest path (unweighted)                     | BFS                           |
| Shortest path (weighted, positive)             | Dijkstra                      |
| Shortest path (negative weights)               | Bellman-Ford                  |
| Dependency order                               | Topological Sort              |
| Detect cycle (undirected)                      | DFS / Union-Find              |
| Detect cycle (directed)                        | DFS Colors / Topological Sort |
| Number of groups                               | DFS / BFS / Union-Find        |
| Merge sets dynamically                         | Union-Find                    |
| Minimum spanning tree                          | Kruskal / Prim                |
| Two-color assignment                           | Bipartite Check               |
| Enumerate all possible paths                   | DFS + Backtracking            |
| Grid regions (e.g., islands)                   | Grid DFS/BFS                  |
| Multiple simultaneous sources                  | Multi-source BFS              |
| Node plus extra conditions (keys, masks, etc.) | BFS with State                |

## Common Interview Problems by Pattern

* **DFS/BFS:** Number of Islands, Clone Graph, Flood Fill
* **Connected Components:** Number of Provinces, Connected Components in an Undirected Graph
* **Cycle Detection:** Graph Valid Tree, Redundant Connection, Course Schedule
* **Topological Sort:** Course Schedule II, Alien Dictionary
* **Dijkstra:** Network Delay Time, Path with Minimum Effort
* **Union-Find:** Accounts Merge, Number of Islands II
* **Minimum Spanning Tree:** Min Cost to Connect All Points, Connecting Cities With Minimum Cost
* **Bipartite:** Is Graph Bipartite?, Possible Bipartition
* **Backtracking on Graphs:** All Paths From Source to Target
* **Grid BFS/DFS:** Surrounded Regions, Pacific Atlantic Water Flow, Rotting Oranges
* **BFS with State:** Word Ladder, Open the Lock, Shortest Path to Get All Keys

