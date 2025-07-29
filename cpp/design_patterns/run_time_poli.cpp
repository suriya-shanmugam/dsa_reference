#include<iostream>
#include<cstring>

class Element {

	public :
		Element(const char* n, int x, int y) : x_pos(x), y_pos(y){
			std::strcpy(name,n);
	        }	
		
		void print(){
			std::cout << "Name is " << name << "\n"
				<< "X_pos is " << x_pos << "\n"
				<< "Y pos is " << y_pos << std::endl;
		}

	private:
		char name[10];
		int x_pos;
		int y_pos;
};

class ButtonElement : public Element {
	
	public :
		ButtonElement(): Element("Button",1,2){}
};


int main(){
	
	ButtonElement button;
	
	// Runtime polymorphism with reference 
	// References can't be changed once assigned
	Element& ele = button;
	ele.print();
	
	Element* ele_ptr = &button;
	ele_ptr->print();

	return 0;
}
