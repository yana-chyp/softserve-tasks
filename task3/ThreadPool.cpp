#ifndef THREADPOOL_CPP
#define THREADPOOL_CPP

#include "ThreadPool.h"
#include <iostream>

ThreadPool::ThreadPool(int num) {
    std::cout<<"number of threads in thread pool: "<<num<<"\n";
    for (int i = 0; i<num; ++i)
        thrds.push_back(std::thread(&ThreadPool::loop, this));
}

ThreadPool::~ThreadPool() {
    {
        std::unique_lock<std::mutex> lock(mtx);
        stop = true;
    }
    cv.notify_all();
    {
        std::unique_lock<std::mutex> lock(mtx);

        // std::cout<<"thrds.size() = "<<thrds.size()<<"\n"; 
    // if (thrds.size() == 0) return;
    // for (std::thread &thrd: thrds) {        
        // std::cout<<"thread id = "<<thrd.get_id()<<"\n";
        // if (thrd.joinable()) 
        // thrd.join();
    // }
        int n = thrds.size();
        for (int i = 0; i<n; ++i) {
            if (thrds[i].joinable()) 
                thrds[i].join();
        }

        thrds.clear();
    }
}

void ThreadPool::wait_queue_empty() {
    while(!stop) {
        {
            std::unique_lock<std::mutex> lock(mtx);
            cv.wait(lock, [this] {return tasks.empty() || stop;});
            if (tasks.empty()) return;
        }
    }
}

void ThreadPool::add_task(std::function<void()> task) {
    {
        std::unique_lock<std::mutex> lock(mtx);
        tasks.push(move(task));
    }
    cv.notify_one();
}

void ThreadPool::wait_and_join_all() {
    {
        std::unique_lock<std::mutex> lock(mtx);
        cv.wait(lock, [this] {return tasks.empty();});
        stop = true;
        
    }
    cv.notify_all();
    for (auto &thrd: thrds) {
        // std::cout<<"thread id = "<<thrd.get_id()<<"\n";s
        if (thrd.joinable()) 
            thrd.join();
    }
}

void ThreadPool::loop() {
    while(!stop) {
        std::function<void()> task;
        {
            std::unique_lock<std::mutex> lock(mtx);
            cv.wait(lock, [this] {return !tasks.empty() || stop;});
            if (tasks.empty()) continue;

            task = tasks.front();
            tasks.pop();
        }
        task();
        cv.notify_one();
    }
}


#endif
