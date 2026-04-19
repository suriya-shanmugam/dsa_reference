#include<iostream>
#include <thread>

bool ready = false;
std::mutex ready_mutex;
std::condition_variable cv;
void consumer(){
    std::unique_lock<std::mutex> lock(ready_mutex);
    cv.wait(lock, []{ return ready; });
    std::cout << "Cosumer got the data";
}

int main(){
    std::thread t(consumer);
    {
        std::lock_guard<std::mutex> lock(ready_mutex);
        ready = true;
    }
    cv.notify_one();
    t.join();
    return 0;
}