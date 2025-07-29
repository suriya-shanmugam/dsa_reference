#include "NumberReporter.hpp"
#include "EvenNumberObserver.hpp"
#include <queue>

int main(){
	NumberReporter* subject = new NumberReporter;
	new EvenNumberObserver(subject);
	
	std::queue<int> numbers = subject->getNumbers();
	while (!numbers.empty()){
		int number = numbers.front();
		numbers.pop();
		subject->notify(number);
	}
	return 0;
}
