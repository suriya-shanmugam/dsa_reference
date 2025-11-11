
def pre_order_dfs(node_index, adj_list, visited, result) -> None :

    # to cover all the nodes use visted list
    if node_index in visited :
        return
    visited.add(node_index)

    # core logic
    for idx in adj_list[node_index]:
        pre_order_dfs(idx,adj_list,visited,result)
    
    result.append(node_index)

    


adjList = [[] for _ in range(8)]

# conventional way
# adjList = []
# for _ in range(3) :
#     adjList.append([])

adjList[0] = [1]
adjList[1] = [2,4]
adjList[2] = [3]
adjList[4] = [5,6]

visited = set()
result = []

for idx in range(8):
    pre_order_dfs(idx, adjList, visited, result)

result.reverse()
print(result)
