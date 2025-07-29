#include<iostream>
#include<vector>
#include<queue>
#include<functional>

using namespace std;

int MAX = 99999;

//compare operator
struct compare{
	bool operator()(pair<int,int>p1, pair<int,int>p2){
		return p1.second > p2.second;
	}
};

//Dijkstra
std::vector<int> get_shortest_distance(int V, vector<vector<int>> edges){
	
	// store min distance state - Initialize with infinifty for other than source vertex
 	vector<int> min_distance(V);
	for(int i=1 ; i < V; i++ ){
		min_distance[i] = MAX;
	}

	// Build adjacency list  // Can use map as well 
	vector<vector<pair<int,int>>> adj_list(V);
	for (const auto& edge : edges){
		int source = edge[0];
		int dest = edge[1];
		int weight = edge[2];
		adj_list[source].push_back({dest,weight});
		adj_list[dest].push_back({source,weight});

	}
	for (int index = 0 ; index < adj_list.size(); index++){
		cout << "Adjacency list of " << index << std::endl;
		cout << "Node\tWeight" << std::endl;
		/*
		for (int sub_index = 0 ; sub_index < adj_list[index].size(); sub_index++){
			cout << adj_list[index][sub_index].first << "\t" << adj_list[index][sub_index].second << std::endl; 	
		} */
		//Better way 
		for (const auto &edge : adj_list[index]){
			cout << edge.first << "\t" << edge.second << std::endl;
		}
	}
	
	// pq collection - 1st param is type of each element, Second is the container, Third is type of comparison function
	priority_queue <pair<int,int>, vector<pair<int,int>>, compare> pq;
	pq.push({0,min_distance[0]});

	while(pq.size() != 0 ){
		int node = pq.top().first;
		pq.pop();

		for( const auto &edge : adj_list[node]){
			int v = edge.first;
			int wt = edge.second;
			if(min_distance[v] > min_distance[node] + wt){
				min_distance[v] = min_distance[node] + wt;
				pq.push({v,min_distance[v]});
			}
		}

	}
	 
	
	return min_distance;

} 

int main(){
	
	
	std::vector<std::vector<int>> edges = {{0,1,4},{0,2,8},{1,2,1}}; // 1st - source, 2nd -target, 3rd - weight
	std::cout << "Source\tTarget\tDistance" << std::endl; 
	for (const auto &edge : edges ){
		for (const auto &element : edge){
			std::cout << element << "\t";
		}
		std::cout << std::endl;
	}
	vector<int> result = get_shortest_distance(3,edges);
	for (int index = 0 ; index < result.size(); index++)
		std::cout << "Distance of " << index << "from 0 is " << result[index] << std::endl;
	std::cout << std::endl;
	return 0;
}

// Doubts 
// What about unreachable nodes?
