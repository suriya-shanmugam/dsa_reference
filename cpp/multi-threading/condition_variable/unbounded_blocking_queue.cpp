#include <iostream>
#include <thread>
#include <queue>
#include <mutex>
#include <condition_variable>
#include <chrono>

template<typename T>
class BlockingQueue {
public:
    void push(const T& value) {
        {
            std::lock_guard<std::mutex> lock(_mutex);
            if (_closed) return; // optional safety: ignore pushes after close
            _queue.push(value);
        }
        _cv.notify_one();
    }

    // Returns false when queue is closed AND empty
    bool pop(T& value) {
        std::unique_lock<std::mutex> lock(_mutex);

        _cv.wait(lock, [this] {
            return _closed || !_queue.empty();
        });

        if (_queue.empty()) {
            return false; // closed and no more data
        }

        value = _queue.front();
        _queue.pop();
        return true;
    }

    void close() {
        {
            std::lock_guard<std::mutex> lock(_mutex);
            _closed = true;
        }
        _cv.notify_all();
    }

private:
    std::queue<T> _queue;
    std::mutex _mutex;
    std::condition_variable _cv;
    bool _closed = false;
};

BlockingQueue<int> q;
std::mutex logger_mutex;

void producer() {
    for (int i = 0; i < 5; ++i) {
        {
            std::lock_guard<std::mutex> lock(logger_mutex);
            std::cout << "Producing: " << i << std::endl;
        }

        q.push(i);
        std::this_thread::sleep_for(std::chrono::milliseconds(500));
    }
    q.close();
}

void consumer(int id) {
    int value;
    while (q.pop(value)) {
        {
            std::lock_guard<std::mutex> lock(logger_mutex);
            std::cout << "Consumer " << id << " processed " << value << std::endl;
        }
    }

    {
        std::lock_guard<std::mutex> lock(logger_mutex);
        std::cout << "Consumer " << id << " exiting\n";
    }
}

int main() {
    std::thread t1(producer);
    std::thread t2(consumer, 1);
    std::thread t3(consumer, 2);

    t1.join();
    t2.join();
    t3.join();

    return 0;
}