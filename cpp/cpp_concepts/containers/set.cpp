#include<iostream>
#include<set>


class Point{
	
	public :
		Point (int n1, int n2):x(n1),y(n2){}
		
		/* To check uniqueness need to implement this */

		bool operator < (const Point &other) const{
			return x < other.x && y < other.y ;
		}

		/* methods has to be const  since objects are added as const in set*/
		void print() const {
			std::cout << "X is " << x << " Y is " << y << std::endl;
		}
	
	private:
		int x, y;
};


int main(){
	
	std::set<int> num_set;

	num_set.insert(1);
	num_set.insert(2);
	num_set.insert(2);

	for (const auto &num : num_set){
		std::cout << num << std::endl;
	}


	if (num_set.find(1) != num_set.end()){
		std::cout << "Value found" << std::endl;
	}
	
	num_set.erase(1);
	
	if (num_set.find(1) == num_set.end()){
		std::cout << "Value Not found" << std::endl;
	}


	std::set<Point> points_set;
	const Point p1(1,2);
	const Point p2(1,2);

	points_set.insert(p1);
	points_set.insert(p2);
	points_set.insert({2,3});
	points_set.insert({3,4});
	
	for (const auto &p : points_set){
		p.print();	
	}

	return 0;

}
