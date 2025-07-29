#include<iostream>
#include<array>
#include "sample.hpp"

constexpr int square(int x){
	return x * x ;
}

int main(){
	
	constexpr int a = square(9);

	std::cout << "square of 9 is " << a << std::endl;

	for (std::array<Suit,4>::iterator it = suits.begin(); it != suits.end(); it++){
		std::cout <<  static_cast<int>(*it) << std::endl;
	} 

}
