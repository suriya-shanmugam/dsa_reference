#include<iostream>
#include<vector>

class PriorityQueue {
	public :
		PriorityQueue(){
			nodes.push_back(-1);
		}
		
		// assumption hear is the index - 0 has the minimum value and will be neglected throughout the process 
		void push(int number){
			nodes.push_back(number);
			int current_index = nodes.size()-1;
			

			// Works fine my thought process was based on  iteration
			/*int parent_index = -1;
			
			  while (current_index > 0){i
				parent_index = current_index / 2 ;
				if (nodes[current_index] < nodes[parent_index]){
					int temp = nodes[parent_index];
					nodes[parent_index] = nodes[current_index];
					nodes[current_index] = temp;
					current_index = parent_index;
				}else{
					break;
				}
				
			}*/

			
			// Better approach iteration and based condition combined
			
			int parent_index = current_index / 2;
			
			while(nodes[parent_index] > nodes[current_index]){
				int temp = nodes[parent_index];
				nodes[parent_index] = nodes[current_index]; 
				nodes[current_index] = temp;
				current_index = parent_index;
				parent_index = current_index/2;
			}
		}

		void pop(){
			
			
			int return_value = nodes[1];

			int last_element = nodes[nodes.size()-1];
			
			
			
			// check the number is less than left or right if less than any child then swap and current_index is swapped index
				
			int current_idx = 1;
			
			int last_idx = nodes.size()-1;
			nodes[current_idx] = nodes[last_idx];
			nodes.erase(nodes.end()-1);

			last_idx -=1; 
			
			while (current_idx < last_idx){
				
				int left_idx = 2 * current_idx;
				int right_idx = 2 * current_idx + 1;
				
				if(right_idx < last_idx && nodes[left_idx] > nodes[right_idx] && nodes[current_idx] > nodes[right_idx] ){
					//swap current and right
					int temp = nodes[current_idx];
					nodes[current_idx] = nodes[right_idx];
					nodes[right_idx] = temp;
					current_idx = right_idx;
				
				}else if(left_idx < last_idx && nodes[current_idx] > nodes[left_idx]){
					
					int temp = nodes[current_idx];
					nodes[current_idx] = nodes[left_idx];
					nodes[left_idx] = temp;
					current_idx = left_idx;
	
				}else{
					break;
				}

			}
			
			// Wrong approach 
			
			/*
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

			}*/
			
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
	pq.push(0);
	pq.print();


	pq.pop();
	pq.pop();
	pq.print();

	return 0;
}
