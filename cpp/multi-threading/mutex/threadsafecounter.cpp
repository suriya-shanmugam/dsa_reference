#include <iostream>
#include <thread>
#include <vector>

int counter = 0 ;
std::mutex counterLock;
// void incrementCounter(int times){
    
//     for (int i = 0; i < times ; i++){
//         counterLock.lock();
//         counter++;
//         counterLock.unlock();
//     }
    
// }

// RAII - Better Handling
void incrementCounter(int times){ 
    for (int i = 0; i < times ; i++){
        std::lock_guard<std::mutex> lock(counterLock);
        counter++;
    }
}

int main(){
    std::vector<std::thread> threads;
    
    int NUM_THREADS = 100;
    int COUNT = 20;
    
    for(int i = 0 ; i < NUM_THREADS; i++){
        threads.emplace_back(incrementCounter, COUNT);
    }

    for (int i = 0 ; i < NUM_THREADS; i++){
        threads[i].join();
    }
    std::cout << "The answer we got " << counter << "Expected Answer is " << NUM_THREADS * COUNT;
    return 0;
}