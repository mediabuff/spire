////////////////////////////////////////////////////////////////////////////////
//  Copyright (C) 2012 Robert Engeln (engeln@gmail.com) All rights reserved.
//  See accompanying LICENSE file for full license information.
////////////////////////////////////////////////////////////////////////////////

#include "prefix.hpp"
#include "spire/core/task.hpp"
#include "default_task_queue.hpp"

using namespace spire;
using namespace core;

DefaultTaskQueue::DefaultTaskQueue()
{
}

DefaultTaskQueue::~DefaultTaskQueue()
{
}

void DefaultTaskQueue::Push(std::unique_ptr<Task> task, int priority)
{
    boost::lock_guard<boost::mutex> lock(m_mutex);
    m_tasks.push_back(std::make_pair(priority, std::move(task)));
    std::push_heap(m_tasks.begin(), m_tasks.end(),
        [] (decltype(*m_tasks.begin())& a, decltype(*m_tasks.begin())& b)
        {
            return a.first < b.first;
        });
}

std::unique_ptr<Task> DefaultTaskQueue::Pop()
{
    boost::lock_guard<boost::mutex> lock(m_mutex);
    for (auto i = m_tasks.begin(); i != m_tasks.end(); ++i)
    {
        if (i->second->Ready())
        {
            std::unique_ptr<Task> ret = std::move(i->second);
            m_tasks.erase(i);
            std::make_heap(m_tasks.begin(), m_tasks.end(),
                [] (decltype(*m_tasks.begin())& a, decltype(*m_tasks.begin())& b)
                {
                    return a.first < b.first;
                });
            return std::move(ret);
        }
    }
    return std::unique_ptr<Task>();
}


