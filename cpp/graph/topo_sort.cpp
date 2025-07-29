#include<iostream>
#include<unordered_set>
#include<vector>

using namespace std;

void post_order_dfs(int source, vector<vector<int>> &adj_by_node, unordered_set<int> &visited, vector<int> &topo){
	
	if (visited.find(source) != visited.end()){
		return;
	}
	visited.insert(source);
	for (int adj_node : adj_by_node[source]){
		post_order_dfs(adj_node, adj_by_node, visited, topo);
	}
	topo.push_back(source);
}

int main(){
	// adj_list
	int TOTAL_NODES = 6;
	std::vector<std::vector<int>> adj_list_of_nodes(6);
	
	adj_list_of_nodes[0].insert(adj_list_of_nodes[0].end(),{1,2});
	adj_list_of_nodes[1].push_back(3);
	adj_list_of_nodes[2].push_back(4);
	adj_list_of_nodes[3].push_back(5);
	adj_list_of_nodes[4].push_back(5);
	//adj_list_of_nodes[5] is empty
	
	//Printing
	for (int node_idx = 0 ; node_idx < TOTAL_NODES ; node_idx++ ){

		cout << "Node of "<< node_idx << std::endl; 
		for (const auto &node_id : adj_list_of_nodes[node_idx]){
			cout << node_id << "\t";
		}
		cout << endl;
	}

	// pre_order_dfs, visited_set, topology	
	
	std::unordered_set<int> visited_set;
	std::vector<int> results;
	
	post_order_dfs(0, adj_list_of_nodes, visited_set, results);

	cout << "Reversing the post_order_dfs_result to get topological sorted order " << std::endl;
	for (int node_id = results.size()-1; node_id > -1 ; node_id--){
		std::cout << results[node_id] << "\t";
	}
	std::cout << std::endl;

	return 0;
}
