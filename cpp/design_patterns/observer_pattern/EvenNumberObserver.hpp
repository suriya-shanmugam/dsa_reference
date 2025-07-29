#pragma once
#include "Observer.h"
#include "NumberReporter.hpp"

class EvenNumberObserver : public Observer{
public:
	EvenNumberObserver(NumberReporter* number_reporter){
		number_reporter->attach(this);
	}
	void update(int number) override;
}; 
