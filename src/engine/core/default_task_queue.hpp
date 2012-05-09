////////////////////////////////////////////////////////////////////////////////
//  Copyright (C) 2012 Robert Engeln (engeln@gmail.com) All rights reserved.
//  See accompanying LICENSE file for full license information.
////////////////////////////////////////////////////////////////////////////////
///
/// @file spire/core/default_task_queue.hpp
/// Defines the DefaultTaskQueue clas.
/// @addtogroup core
/// @{

#ifndef SPIRE_CORE_DEFAULT_TASK_QUEUE_HPP
#define SPIRE_CORE_DEFAULT_TASK_QUEUE_HPP

#include "spire/core/task_queue.hpp"

namespace spire
{
    namespace core
    {
        class Task;

        ///
        /// Default implementation of TaskQueue.
        ///
        class DefaultTaskQueue : public TaskQueue
        {
        public:
            ///
            /// Constructor.
            ///
            DefaultTaskQueue();

            ///
            /// Destructor.
            ///
            virtual ~DefaultTaskQueue();

            ///
            /// From TaskQueue.
            /// @{
            virtual void Push(std::unique_ptr<Task> task, int priority);
            virtual std::unique_ptr<Task> Pop();
            //! @}

        private:
            boost::mutex m_mutex;
            std::vector<std::pair<int, std::unique_ptr<Task>>> m_tasks;
        };
    }   //  namespace core
}   //  namespace spire

#endif  //  SPIRE_CORE_DEFAULT_TASK_QUEUE_HPP

