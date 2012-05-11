////////////////////////////////////////////////////////////////////////////////
//  Copyright (C) 2012 Robert Engeln (engeln@gmail.com) All rights reserved.
//  See accompanying LICENSE file for full license information.
////////////////////////////////////////////////////////////////////////////////

#include "prefix.hpp"
#include "spire/core/task.hpp"
#include "spire/core/task_queue.hpp"
#include "default_thread_pool.hpp"

using namespace spire;
using namespace core;

DefaultThreadPool::DefaultThreadPool(int threadCount)
{
    assert(threadCount > 0);
    m_threads.resize(threadCount);
    for (size_t i = 0; i < m_threads.size(); ++i)
    {
        m_threads[i] = boost::thread(Worker, boost::ref(*this));
    }
}

DefaultThreadPool::~DefaultThreadPool()
{
    m_exit = true;
    for (size_t i = 0; i < m_threads.size(); ++i)
    {
        m_threads[i].join();
    }
}

TaskQueue& DefaultThreadPool::GetTaskQueue()
{
    return m_taskQueue;
}

void DefaultThreadPool::Worker(DefaultThreadPool& threadPool)
{
    std::unique_ptr<Task> task;
    while (!threadPool.m_exit)
    {
        while (task = std::move(threadPool.m_taskQueue.Pop()))
        {
            task->Run();
        }
        boost::this_thread::yield();
    }
}
