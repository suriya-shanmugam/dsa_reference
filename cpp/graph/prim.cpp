#include<iostream>
#include<vector>
#include<queue>
#include<unordered_set>

class Edge{
public:	
	int source;
	int destination;
	int weight;
};

class GT{
public :
	bool operator()(Edge e1, Edge e2){
		return e1.weight > e2.weight;
	}
};

int main(){
	int num_nodes = 3;
	std::vector<Edge> edges = {{0,1,5},{1,2,10},{0,2,12}};
	std::vector<std::vector<Edge>> adj_list(num_nodes);
	
	// Building adjacency list 
	for (Edge e : edges ){
		//std::cout << "Source: "<< e.source << "\tDestination: " << e.destination << "\tWeight: " << e.weight << std::endl;
		adj_list[e.source].push_back(e);
		adj_list[e.destination].push_back(e);

	}

	// Testing to correctness of the adj_list
	/**
	int index = 0;
	for (auto list : adj_list){
		std::cout << "Node " << index << " adj_list " << std::endl;
		for (auto e : list){
			std::cout << "Source: "<< e.source << "\tDestination: " << e.destination << "\tWeight: " << e.weight << std::endl;
		}
		index++;
	}
	**/
	
	std::priority_queue <Edge, std::vector<Edge>, GT> pq;
	std::unordered_set<int> visited;
	std::vector<Edge> mst;

	for (Edge e : adj_list[0]){
		pq.push(e);
	}
	
	visited.insert(0);
	
	while( pq.size() != 0 ){
		
		auto edge = pq.top();
		pq.pop();
		
		if (visited.find(edge.destination) != visited.end()){
			continue;
		}
		
		visited.insert(edge.destination);
		mst.push_back(edge);
		
		for (const auto e : adj_list[edge.destination]){
			pq.push(e);	
		}
	}

	for (const auto e : mst){
		std::cout << "Source: "<< e.source << "\tDestination: " << e.destination << "\tWeight: " << e.weight << std::endl;

	}
	return 0;
}
