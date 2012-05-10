////////////////////////////////////////////////////////////////////////////////
//  Copyright (C) 2012 Robert Engeln (engeln@gmail.com) All rights reserved.
//  See accompanying LICENSE file for full license information.
////////////////////////////////////////////////////////////////////////////////
///
/// @file spire/core/task_queue.hpp
/// Defines the TaskQueue class.
/// @addtogroup core
/// @{

#ifndef SPIRE_CORE_TASK_QUEUE_HPP
#define SPIRE_CORE_TASK_QUEUE_HPP

namespace spire
{
    namespace core
    {
        class Task;

        struct ThreadAffinities
        {
            ///
            /// Flags indicating which threads a task can run on.
            ///
            /// Subsystems are free to use bits 2+ to mask specific
            /// threads, but there is no generic meaning for those bits.
            ///
            enum ThreadAffinity
            {
                Main = 1,
                Async = 0xFFFFFFFF ^ 1,
                Any = 0xFFFFFFFF
            };

        private:
            ThreadAffinities();
        };
        typedef ThreadAffinities::ThreadAffinity ThreadAffinity;

        ///
        /// Priority queue of Task objects.
        ///
        class TaskQueue : public boost::noncopyable
        {
        public:
            ///
            /// Constructor.
            ///
            TaskQueue();

            ///
            /// Destructor.
            ///
            ~TaskQueue();

            ///
            /// Pushes a task onto the queue.
            ///
            /// @param task Task object. The TaskQueue will take
            ///             ownership.
            /// @param affinity Thread affinity. 
            /// @param priority Task priority; a higher number is better.
            ///                 Tasks are always executed strictly in order
            ///                 of priority, assuming they are ready.
            ///
            void Push(std::unique_ptr<Task> task,
                      ThreadAffinity affinity = ThreadAffinities::Any,
                      int priority = 0);

            ///
            /// Pops the highest priority ready task from the queue.
            ///
            /// @param thread Thread bit; will be compared against the affinity
            ///               mask provided by the thread. A task whose affinity
            ///               does not match the thread will not be returned.
            /// @return Highest priority ready task, or null if no task is ready.
            ///
            std::unique_ptr<Task> Pop(int thread);

            ///
            /// Checks if the queue is completely empty.
            ///
            bool Empty() const;

        private:
            struct TaskInfo
            {
                ThreadAffinity affinity;
                int priority;
                std::unique_ptr<Task> task;

                TaskInfo();
                TaskInfo(TaskInfo&& rhs);
                TaskInfo& operator=(TaskInfo&& rhs);
            };
            friend bool operator<(const TaskInfo&, const TaskInfo&);

            mutable boost::mutex m_mutex;
            std::vector<TaskInfo> m_tasks;
        };
    }   //  namespace core
    using core::TaskQueue;
    using core::ThreadAffinity;
    using core::ThreadAffinities;
}   //  namespace spire

#include "spire/core/task_queue.inl"

#endif  //  SPIRE_CORE_TASK_QUEUE_HPP

