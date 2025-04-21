#include<iostream>

class Point{
	public :
		Point(int n1,int n2):x(n1),y(n2){
		}

		bool operator == (const Point& other)const {
			return (x == other.x && y == other.y);
		}

	private : 
		int x, y;
	
};



int main(){
	
	std::pair<int,int> p = {1,2}, p2 = {2,3};
	
	if ( p < p2 ){
		std::cout << "P is lesser " << std::endl;
	}

	std::cout << "First " << p.first << " second " << p.second << std::endl;


	std::pair<int,Point> customp = {1,{1,0}};
	std::pair<int,Point> customp1 = {2,{1,0}};

	if (customp == customp1){
		std::cout << "They are equal";
	}


	return 0;
}
