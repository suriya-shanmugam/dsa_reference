#include<iostream>

namespace calculator {

	int add(const int a, const int b){
		return a+b;
	};

	
	class twonum{
		
		
		public :
		
		int num1;
		int num2;
				
		twonum(int num1, int num2){
			this->num1 = num1;
			this->num2 = num2;
		}		
	};

}

using namespace calculator;

int main(){
	
	
	twonum numset1(5,6);
	std::cout<< "calling add Result - " << calculator::add(numset1.num1, numset1.num2) << std::endl ;
	return 0 ;

}
