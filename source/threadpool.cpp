/**
 * @file threadpool.cpp
 * @author https://stackoverflow.com/users/1322972/whozcraig and Susanna Hepp
 * @brief https://stackoverflow.com/questions/23896421/efficiently-waiting-for-all-tasks-in-a-threadpool-to-finish
 * @version 0.1
 * @date 2020-07-12
 * 
 * @copyright Copyright (c) 2020
 * 
 */

#include <iostream>
#include <deque>
#include <functional>
#include <thread>
#include <condition_variable>
#include <mutex>
#include <random>
#include <atomic>

#include "threadpool.hpp"

/**
 * @brief Construct a new ThreadPool object
 * 
 * @param n Amount of threads
 */
ThreadPool::ThreadPool(unsigned int n)
    : busy(), processed(), stop()
{
    for (unsigned int i = 0; i < n; ++i)
        workers.emplace_back(std::bind(&ThreadPool::thread_proc, this));
}

/**
 * @brief Destroy the ThreadPool object
 * 
 */
ThreadPool::~ThreadPool()
{
    // set stop-condition
    std::unique_lock<std::mutex> latch(queue_mutex);
    stop = true;
    cv_task.notify_all();
    latch.unlock();

    // all threads terminate, then we're done.
    for (auto &t : workers)
        t.join();
}

/**
 * @brief Thread processing
 * 
 */
void ThreadPool::thread_proc()
{
    while (true)
    {
        std::unique_lock<std::mutex> latch(queue_mutex);
        cv_task.wait(latch, [this]() { return stop || !tasks.empty(); });
        if (!tasks.empty())
        {
            // got work. set busy.
            ++busy;

            // pull from queue
            auto fn = tasks.front();
            tasks.pop_front();

            // release lock. run async
            latch.unlock();

            // run function outside context
            fn();
            ++processed;

            latch.lock();
            --busy;
            cv_finished.notify_one();
        }
        else if (stop)
        {
            break;
        }
    }
}
/**
 * @brief Push Function into task queu
 * 
 * @param f 
 */
void ThreadPool::enqueue(std::function<void()> &f)
{
    std::unique_lock<std::mutex> lock(queue_mutex);
    tasks.emplace_back(f);
    cv_task.notify_one();
}

/**
 * @brief Waits until the queue is empty.
 * 
 */
void ThreadPool::waitFinished()
{
    std::unique_lock<std::mutex> lock(queue_mutex);
    cv_finished.wait(lock, [this]() { return tasks.empty() && (busy == 0); });
}