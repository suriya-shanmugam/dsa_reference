#include<iostream>

using namespace std;

class Prob {
public :
	int value;
	Prob(int num):value(num){}
};

class Llm : public Prob {
public:	
	Llm(int num):Prob(num){} 
};

void print(int* value){
	cout << *value << endl;
}


int main(){
	
	int a = 90;
	print(&a);
	
	// Static pointer - compile time / upcasting
	char a_char = static_cast<char> (a); 
	cout << a_char << endl;
	
	//Llm* llm1 = new Llm(20000);
	//Prob* p1 = static_cast<Prob*> (llm1);
	
	Llm llm1(20000);
	Prob* p1 = static_cast<Prob*> (&llm1);
	
	cout << p1->value << endl;

	
	// any type - reinterpret bit pattern - platform specific
	int num = 65;
	char* c_num = reinterpret_cast<char*> (&num);
	
	cout << c_num << endl;

	return 0;
}
