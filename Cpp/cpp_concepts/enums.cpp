#include<iostream>

enum  class Suit {
	clubs=2, diamonds, hearts, spades
};

int main(){

	Suit s = Suit::hearts;

	std::cout << "Suit" << static_cast<int>(s) << std::endl;
	
} 
