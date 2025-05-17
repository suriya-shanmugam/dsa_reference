/*
 * std::lock_guard is lightweight NO unlock/relock 
 * support all mutex type like std::mutex, std::shared_mutex etc
 *
 */

#include<iostream>
#include<thread>
#include<mutex>

std::mutex mutex;

int counter = 0;

void increment_counter(){
	
	for (int i =0 ; i < 1000 ; i++){
		
		std::lock_guard<std::mutex> lock(mutex);

		// mutex.lock();
		++counter;
		// mutex.unlock();

	
	}
}

int main(){
	
	
	std::thread t1(increment_counter);
	std::thread t2(increment_counter);
	std::thread t3(increment_counter);
	//increment_counter();
	
	t1.join();
	t2.join();
	t3.join();
	std::cout << "counter example" << counter << std::endl;
	return 0;
}
