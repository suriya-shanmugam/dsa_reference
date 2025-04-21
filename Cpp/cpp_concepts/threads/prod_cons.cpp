#include<iostream>
#include<queue>
#include<thread>
#include<vector>
#include<chrono>


std::queue<int> pending_works;
int completed = 0;
//std::mutex mtx;


void producer(){
	
	for (int i = 0 ; i < 20 ; i++){
		std::this_thread::sleep_for(std::chrono::seconds(1));
		
		pending_works.push(i);
	}
	completed = 1;
}

void consumer(){
	
	while(!completed){
		
		if (pending_works.size() != 0){

			int work = pending_works.front();
			pending_works.pop();
			std::cout << work << std::endl;
		}	
	}
}


int main(){
	
	std::thread prod(producer);

	std::thread cons1(consumer);
	//std::thread cons2(consumer);

	prod.join();
	cons1.join();
	//cons2.join();
	
	return 0;

	
}
