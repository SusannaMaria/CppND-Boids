/**
 * @file threadpool.cpp
 * @author https://stackoverflow.com/users/1322972/whozcraig and Susanna Hepp
 * @brief https://stackoverflow.com/questions/23896421/efficiently-waiting-for-all-tasks-in-a-threadpool-to-finish
 * Fill functioncalls in thread pool and wait until pool is empty again
 * @version 0.1
 * @date 2020-07-12
 * 
 * @copyright Copyright (c) 2020
 * 
 */


#pragma once
#include <iostream>
#include <deque>
#include <functional>
#include <thread>
#include <condition_variable>
#include <mutex>
#include <random>
#include <atomic>

/**
 * @brief Fill threadpool with functioncalls and wait until they are finished
 * 
 */
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
