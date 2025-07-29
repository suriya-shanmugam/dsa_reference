#include<iostream>
#include<queue>
#include<functional>
#include<vector>

/**

8 3 4 5
8
max_heap - 8
min_heap - 

3
maxh - 3
minh - 8

4 
maxh - 4,3
minh - 8

5 
maxh - 5,4,3
minh - 8 
//Balance 
maxh - 4,3
minh - 5,8

# add to the heap based on the peek element and balance it based on the size


**/


std::priority_queue<int, std::vector<int>, std::greater<int>> min_heap;
std::priority_queue<int, std::vector<int>> max_heap; 

void add(int number){
	
	if ( min_heap.empty() || (!min_heap.empty() && number > min_heap.top())){
		min_heap.push(number);	
	}else{
		max_heap.push(number);
	}
	
	// Important c++ pitfall unsigned types return by size()
	// size() will return unsigned type - so 0 - 1 will be interpreted as large number
	if ( min_heap.size() > max_heap.size() + 1){
		max_heap.push(min_heap.top());
		min_heap.pop();
	}else if( max_heap.size() > min_heap.size() + 1){
		min_heap.push(max_heap.top());
		max_heap.pop();
	} 

}

double get_median(){
	if (min_heap.size() > max_heap.size()){
		return min_heap.top();
	}else if (max_heap.size() > min_heap.size()){
		return max_heap.top();
	}else{
		if (max_heap.size() == 0 || min_heap.size() == 0){
			return -1; // Replace it with constant
		}
		return ( double(min_heap.top()) + max_heap.top())/2 ;
	}
} 

int main(){
	add(5);
	add(10);
	add(25);
	add(6);
	add(9);
        add(1);
	add(2);
	add(11);
	add(3);
	// 1 2 3 5 6 9 10 11 25	
	std::cout <<"Min heap and max_heap sizes are "<< min_heap.size() <<" "<< max_heap.size() << std::endl;
	std::cout << "Min max is " << min_heap.top() << "max_min is "  << max_heap.top() << std::endl;
	std::cout <<"Median is" << get_median() << std::endl;
	return 0;
}
