#include<iostream>
#include<iomanip>
#include<vector>

class Point {

public :
	Point(int a, int b):x(a),y(b){
		std::cout << "Constructor" << std::endl;
	}
	Point (const Point& other){
		std::cout << "Copy Constructor";
		x = other.x;
		y = other.y;
	}

	Point& operator = (const Point& other){
		std::cout << "Assignment operator called" << std::endl;
		x = other.x;
		y = other.y;
		return *this;

	}

	~Point(){
		std::cout << "Destructor point!!" << std::endl;
	
	}
	int x;
	int y;
};

int main(){
	
	Point p(1,2);
	
	Point p2(0,0);
	
	{
		std::vector<Point> points;
		points.push_back(p);
	}

	{
	
		p2 = p;
	}

	std::cout << "X is " << p2.x << "Y is " << p2.y << std::endl;

	return 0;
}
