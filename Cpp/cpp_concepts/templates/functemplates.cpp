#include<iostream>

template <typename T>
T compare(T a, T b){
	return a > b;
}


template <typename T>
class Point {
	public :
		Point(T n1, T n2) : x(n1), y(n2) {}
		void print(){
			std::cout << " X - value : " << x << " Y - value:  " << y << std::endl;
		}
	private :
		T x; 
		T y;
};


int main (){
	
	int a = 1;
	int b = 2;
	std::cout << "Interger compare "<< compare(a, b) << std::endl;
	float c = 10.22;
	float d = 11.22;
	std::cout << "Float compare" << compare(c,d) << std::endl;
	
	
	Point p1(1,2);
	p1.print();

	Point p2(3.4, 7.5);
	p2.print();

		

	return 0;
}
