#include <iostream>
#include <thread>
#include <shared_mutex>
#include <vector>
#include <ctime>
#include <mutex>

int value = 1 ;

std::shared_mutex s_mutex;

void read(){
	
	std::shared_lock<std::shared_mutex> lock(s_mutex);
	std::srand(std::time(0));
	std::this_thread::sleep_for(std::chrono::seconds(1+ std::rand()%10));
	std::cout << value << std::endl;

}

void write(){
	
	std::unique_lock<std::shared_mutex> lock(s_mutex);
	//std::srand(std::time(0));
	//std::this_thread::sleep_for(std::chrono::seconds(1 + std::rand()%2));
	value++;
}


int main(){

	std::vector<std::thread> threads;

	for(int i =0 ; i < 10 ; i++){

		threads.emplace_back(write);
	}
	//threads.emplace_back(write);
	//threads.emplace_back(write);
	
	for(int i =0 ; i < 100 ; i++){
		threads.emplace_back(read);
	}
	

	for (auto &t : threads){
		t.join();
	}
	
	//thread.emplace_back(read);


	return 0;
}
