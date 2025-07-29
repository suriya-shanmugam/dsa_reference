#pragma once
#include "Observer.h"
#include <vector>

class Subject{

	public :
	void attach(Observer* observer){
		observers.push_back(observer);
	}
	
	void notify(int num){
		for (auto obs : observers){
			obs->update(num);
		}
	}


private :
	std::vector<Observer*> observers;
};
