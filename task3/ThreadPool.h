#ifndef THREADPOOL_H
#define THREADPOOL_H
#include <thread>
#include <vector>
#include <queue>
#include <functional>
#include <condition_variable>

class ThreadPool {
    private:
        std::vector<std::thread> thrds;
        std::queue<std::function<void()>> tasks;
        std::condition_variable cv;
        std::mutex mtx;
        bool stop = false;
        void loop();
    public:
        // void stop();
        ThreadPool(int num = std::thread::hardware_concurrency());
        ~ThreadPool();
        void add_task(std::function<void()> task);
        void wait_and_join_all();
        void wait_queue_empty();

};

#endif