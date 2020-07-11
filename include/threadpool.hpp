#pragma once
#include <iostream>
#include <deque>
#include <functional>
#include <thread>
#include <condition_variable>
#include <mutex>
#include <random>
#include <atomic>

//thread pool
class ThreadPool
{
public:
    ThreadPool(unsigned int n = std::thread::hardware_concurrency());

    template<class F> void enqueue(F&& f);
    void enqueue(std::function<void ()>&f);
    void waitFinished();
    ~ThreadPool();

    unsigned int getProcessed() const { return processed; }

private:
    std::vector< std::thread > workers;
    std::deque< std::function<void()> > tasks;
    std::mutex queue_mutex;
    std::condition_variable cv_task;
    std::condition_variable cv_finished;
    std::atomic_uint processed;
    unsigned int busy;
    bool stop;

    void thread_proc();
};
