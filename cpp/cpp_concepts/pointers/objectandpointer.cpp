#include<iostream>
#include<cstring>


class Widget {

	public :

		Widget(char *&n1,int s):id(s){
			std::strcpy(name,n1);
		}

		void print(){
			std::cout << "name - " << name << " Id - " << id << " size - " << size << std::endl;
		}

		int size;
	
	private :

		char name[200];
		int id;
		

};


int main(){

	char *a = "tooltip";
	
	Widget w(a,1);
	w.size = 30;
	w.print();
	
	char *b = "Button";
	
	Widget *w2[10]; 
	w2[0] = new Widget(b, 2);
	w2[0]->size = 2;
	w2[0]->print();
	
	Widget *w3 = new Widget[2]{{b,3},{b,3}};
	
	w3->print();
	w3++;
	w3->print();
	
	// beyond allocated
	w3++;
	w3->print();

	return 0;
}
