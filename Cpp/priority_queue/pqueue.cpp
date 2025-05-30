#include<iostream>
#include<vector>

class PriorityQueue {
	public :
		PriorityQueue(){
			nodes.push_back(-1);
		}
		
		void push(int number){
			nodes.push_back(number);
			int current_index = nodes.size()-1;
			int parent_index = -1;
			while (current_index > 0){
				parent_index = current_index / 2 ;
				if (nodes[current_index] < nodes[parent_index]){
					int temp = nodes[parent_index];
					nodes[parent_index] = nodes[current_index];
					nodes[current_index] = temp;
				}else{
					break;
				}
				current_index--;
			}
		}

		void pop(){
			
			int current_index = 1;
			int value = nodes[current_index];
			
			nodes[current_index] = nodes[nodes.size()-1];
			nodes.erase(nodes.end()-1);
			
			while (current_index > nodes.size()){
				
				int left = 2 * current_index ;
				int right = 2 * current_index + 1;
				
				if(nodes[current_index] > nodes[left]){
					int temp = nodes[current_index];
					nodes[current_index] = nodes[left];
					nodes[left] = temp;
					current_index = left;
				}else if(nodes[current_index] > nodes[right]){
					int temp = nodes[current_index];
					nodes[current_index] = nodes[right];
					nodes[right] = temp;
					current_index = right;
				}else{
					break;
				}

			}
			
		}

		void print(){
			for (const int& num : nodes){
				std::cout << num << " ";
			}
			std::cout << std::endl;
		}
			
	
	private:
		std::vector<int> nodes;
		
};

int main(){
	
	PriorityQueue pq;
	pq.push(2);
	pq.push(3);
	pq.push(4);
	pq.push(5);
	pq.push(1);
	
	pq.print();

	pq.pop();
	pq.print();

	return 0;
}
