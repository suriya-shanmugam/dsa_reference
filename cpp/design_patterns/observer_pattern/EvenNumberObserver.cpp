#include<EvenNumberObserver.hpp>
#include<iostream>

void EvenNumberObserver::update(int number){
		if (number % 2 == 0){
			std::cout << "Got one Even" << number << std::endl;
		}
}

