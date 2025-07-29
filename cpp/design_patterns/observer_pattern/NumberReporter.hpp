#pragma once
#include<Subject.h>
#include<queue>

class NumberReporter : public Subject{	

public:
	NumberReporter(){
		numbers.push(1);
		numbers.push(2);
	}
	std::queue<int> getNumbers(){
		return numbers;
	}

private:
	std::queue<int> numbers;
	
};
