#include<iostream>
#include<queue>

struct greater_than{
	
	bool operator() (const int& num1, const int&num2){
		if (num1 > num2){
			return true;
		}
		return false;
	}
};

int main(){
	
	std::priority_queue<int> pq;
	pq.push(25);
	pq.push(5);
	pq.push(10);
	pq.push(30);
	pq.push(2);
	pq.push(3);

	while (pq.size() != 0){
		std::cout << pq.top() << std::endl;
		pq.pop();
	}
	
	
	// Writing own functor to make to mimic min_heap behaviour
	std::priority_queue<int, std::vector<int>, greater_than> min_pq;
	
	// In this case - first param to std::greater will be the element iterator pointed by moving ptr 

	//std::priority_queue<int, std::vector<int>, std::greater<int>> min_pq;
	min_pq.push(25);
	min_pq.push(5);
	min_pq.push(10);
	
	while (min_pq.size() != 0){
		std::cout << min_pq.top() << std::endl;
		min_pq.pop();
	}
	
	// return boolean true if first number is greater than second
	std::greater<int> greater_than;
	std::cout << "Testing the functor : Greater is " <<  greater_than(5,4) << std::endl;
	
	return 0;
}
