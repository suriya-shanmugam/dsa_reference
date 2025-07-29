#include<iostream>
#include<vector>

struct Point {

	int x;
	std::vector<int> list; 
	int y;
};

int main(){

	Point p = {1};
	Point p2 = {1,{1,2},2};

	std::cout << "Point a " << p.x << " " << p.y << std::endl;

	for (const auto&num : p2.list){
		std::cout << num << std::endl;
	}

        std::cout << "Point b " << p2.x << " " << p2.y;
	for (const auto&num : p.list){
		std::cout << num << std::endl;
	}




}
