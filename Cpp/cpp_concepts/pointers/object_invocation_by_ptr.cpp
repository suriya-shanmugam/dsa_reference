#include <iostream>

class Shape {

	public :
		Shape(){}
		
		void whatshape(){
			std::cout << "I am shape" ;
		}
};



class Square : public Shape {
	
	private:
		int side;
	public :
		Square(int input_side): side(input_side){}
		
		void getArea(){
			std::cout << " Area " << (this->side * this->side) << std::endl;
		}
			
};


void call_getArea(Shape *instance){
	
	//std::cout << instance->whatshape() << std::endl;
	instance->whatshape();

}


void call_by_ref(Shape &ref){
	//std::cout << ref.whatshape() << std::endl;
	ref.whatshape();

}


int main(int argc, char *agrv[]){

	Shape *shape;
	
	shape = new Square(5);
	
	shape->whatshape();

	delete shape;
	
	


	//Square s(5);
	
	//s.whatshape();
	
	//call_getArea(&s);
	//call_by_ref(s);
	//std::cout << s.getArea() << std::endl;
	return 0;

}
