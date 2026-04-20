#include <mutex>
#include <condition_variable>

class binary_semaphore {
    std::mutex mtx;
    std::condition_variable cv;
    bool flag = false;

public:
    explicit binary_semaphore(bool init = false) : flag(init) {}

    void release() {
        std::lock_guard<std::mutex> lock(mtx);
        flag = true;
        cv.notify_one();
    }

    void acquire() {
        std::unique_lock<std::mutex> lock(mtx);
        cv.wait(lock, [&]{ return flag; });
        flag = false;
    }
};