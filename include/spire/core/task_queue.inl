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

        inline bool operator<(const TaskQueue::TaskInfo& lhs,
                              const TaskQueue::TaskInfo& rhs)
        {
            return lhs.priority < rhs.priority;
        }

        inline TaskQueue::TaskInfo::TaskInfo()
        {
        }

        inline TaskQueue::TaskInfo::TaskInfo(TaskQueue::TaskInfo&& src)
        : task(std::move(src.task)), 
          priority(src.priority), 
          affinity(src.affinity)
        {
        }

        inline TaskQueue::TaskInfo& TaskQueue::TaskInfo::operator=(TaskQueue::TaskInfo&& rhs)
        {
            task = std::move(rhs.task);
            priority = rhs.priority;
            affinity = rhs.affinity;
            return *this;
        }

        inline void TaskQueue::Push(std::unique_ptr<Task> task,
                                    ThreadAffinity affinity,
                                    int priority)
        {
            boost::lock_guard<boost::mutex> lock(m_mutex);
            TaskInfo taskInfo;
            taskInfo.task = std::move(task);
            taskInfo.affinity = affinity;
            taskInfo.priority = priority;

            m_tasks.push_back(std::move(taskInfo));
            std::push_heap(m_tasks.begin(), m_tasks.end());
        }

        inline std::unique_ptr<Task> TaskQueue::Pop(int thread)
        {
            boost::lock_guard<boost::mutex> lock(m_mutex);
            for (auto i = m_tasks.begin(); i != m_tasks.end(); ++i)
            {
                if (i->task->Ready())
                {
                    std::unique_ptr<Task> ret = std::move(i->task);
                    if (i == m_tasks.begin())
                    {
                        std::pop_heap(m_tasks.begin(), m_tasks.end());
                        m_tasks.pop_back();
                    }
                    else
                    {
                        m_tasks.erase(i);
                        std::make_heap(m_tasks.begin(), m_tasks.end());
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


