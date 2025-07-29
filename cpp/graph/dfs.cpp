#include<iostream>
#include<unordered_map>
#include<vector>

using namespace std;

void pre_order_dfs(int source, unordered_map<int, vector<int>> adj_by_node){
	cout << source << "\t" << endl;
	for (auto node : adj_by_node[source]){
		pre_order_dfs(node, adj_by_node);
	}
	
}

int main(){
	
	unordered_map<int, vector<int>> adj_list_by_node;
	adj_list_by_node[0] = {1,2};
	adj_list_by_node[1] = {2,3};
	adj_list_by_node[2] = {};

	/*
	for (auto adjL : adj_list_by_node){
		cout << "Current Node: " << adjL.first << std::endl;
		for (auto node : adjL.second){
			cout << node << "\t";
		}
		cout << std::endl;
	}*/
	pre_order_dfs(0,adj_list_by_node);
	return 0;
}
