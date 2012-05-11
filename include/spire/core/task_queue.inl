////////////////////////////////////////////////////////////////////////////////
//  Copyright (C) 2012 Robert Engeln (engeln@gmail.com) All rights reserved.
//  See accompanying LICENSE file for full license information.
////////////////////////////////////////////////////////////////////////////////
///
/// @file spire/core/task_queue.inl
/// Inline functions for the TaskQueue class.
/// @addtogroup core
/// @{

#ifndef SPIRE_CORE_TASK_QUEUE_INL
#define SPIRE_CORE_TASK_QUEUE_INL

namespace spire
{
    namespace core
    {
        inline TaskQueue::TaskQueue()
        {
        }

        inline TaskQueue::~TaskQueue()
        {
        }

        inline void TaskQueue::Push(std::unique_ptr<Task> task,
                                    int priority)
        {
            boost::lock_guard<boost::mutex> lock(m_mutex);
            m_tasks.push_back(std::make_pair(priority, std::move(task)));
            std::push_heap(m_tasks.begin(), m_tasks.end(),
                [] (const decltype(*m_tasks.begin())& a,
                    const decltype(*m_tasks.begin())& b)
                {
                    return a.first > b.first;
                });
        }

        inline std::unique_ptr<Task> TaskQueue::Pop()
        {
            boost::lock_guard<boost::mutex> lock(m_mutex);
            for (auto i = m_tasks.begin(); i != m_tasks.end(); ++i)
            {
                if (i->second->Ready())
                {
                    std::unique_ptr<Task> ret = std::move(i->second);
                    if (i == m_tasks.begin())
                    {
                        std::pop_heap(m_tasks.begin(), m_tasks.end(),
                            [] (const decltype(*m_tasks.begin())& a,
                                const decltype(*m_tasks.begin())& b)
                            {
                                return a.first > b.first;
                            });
                        m_tasks.pop_back();
                    }
                    else
                    {
                        m_tasks.erase(i);
                        std::make_heap(m_tasks.begin(), m_tasks.end(),
                            [] (const decltype(*m_tasks.begin())& a,
                                const decltype(*m_tasks.begin())& b)
                            {
                                return a.first > b.first;
                            });
                    }
                    return std::move(ret);
                }
            }
            return std::unique_ptr<Task>();
        }

        inline bool TaskQueue::Empty() const
        {
            boost::lock_guard<boost::mutex> lock(m_mutex);
            return m_tasks.empty();
        }
    }   //  namespace core
}   //  namespace spire

#endif  //  SPIRE_CORE_TASK_QUEUE_INL


