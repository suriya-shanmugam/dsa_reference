#include <iostream>
#include <thread>
#include <semaphore>

std::binary_semaphore ready(0);

void initialize_system(){
    std::cout << "Initializing\n";
    std::this_thread::sleep_for(std::chrono::seconds(2));
    std::cout << "Initialization complete\n";
    ready.release();
}

void worker(){
    std::cout << "Worker Waiting for the initialization\n";
    ready.acquire();
    std::cout << "Worker starts working\n";
}

int main(){
    std::thread t1(worker);
    std::thread i(initialize_system);

    i.join();
    t1.join();
    return 0;
}