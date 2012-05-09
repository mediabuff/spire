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

        ///
        /// Priority queue of Task objects.
        ///
        class TaskQueue
        {
        public:
            ///
            /// Destructor.
            ///
            virtual ~TaskQueue() = 0 { };

            ///
            /// Pushes a task onto the queue.
            ///
            /// @param task Task object. The TaskQueue will take
            ///             ownership.
            /// @param priority Task priority; a higher number is better.
            ///                 Tasks are always executed strictly in order
            ///                 of priority, assuming they are ready.
            ///
            virtual void Push(std::unique_ptr<Task> task,
                              int priority = 0) = 0;

            ///
            /// Pops the highest priority ready task from the queue.
            ///
            /// @return Highest priority ready task, or null if no task is ready.
            ///
            virtual std::unique_ptr<Task> Pop() = 0;
        };
    }   //  namespace core
}   //  namespace spire

#endif  //  SPIRE_CORE_TASK_QUEUE_HPP

