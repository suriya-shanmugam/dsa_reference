## Khan's algorithm [Directed Acyclic Graph]
- [1,0] -> if 1 depends on 0 then build 0 -> 1 graph
```
# topological sort
for u,v in edges :
    graph[u].append(v)
    indegree[v] += 1
```
- in course schedule, consider all courses to add to queue don't just consider edges [There are disconnected nodes]


## Cycle dectection in undirected graph

- track visited and parent


## Djikstra

- Works for both directed and undirected graph
- graph should have weight along with u,v  
```
{'u' : [('v', 5)]}
```
- dist state stores cumulative cost from source node
```
dist = {v: float('inf') for v in graph}
```
- algorithm is 
if current parent's cumulative cost + parents edge cost < node's cumaltive cost then update and add to queue
