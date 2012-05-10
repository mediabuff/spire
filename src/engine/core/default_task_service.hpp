////////////////////////////////////////////////////////////////////////////////
//  Copyright (C) 2012 Robert Engeln (engeln@gmail.com) All rights reserved.
//  See accompanying LICENSE file for full license information.
////////////////////////////////////////////////////////////////////////////////
///
/// @file spire/core/default_task_service.hpp
/// Defines the DefaultTaskService class.
/// @addtogroup core
/// @{

#ifndef SPIRE_CORE_DEFAULT_TASK_SERVICE_HPP
#define SPIRE_CORE_DEFAULT_TASK_SERVICE_HPP

#include "spire/core/task_service.hpp"
#include "spire/core/task_queue.hpp"

namespace spire
{
    namespace core
    {
        class ThreadPool;

        class DefaultTaskService : public BasicService<TaskService>
        {
        public:
            ///
            /// Constructor.
            ///
            DefaultTaskService();

            ///
            /// Destructor.
            ///
            virtual ~DefaultTaskService();

            ///
            /// From TaskService.
            /// @{
            virtual TaskQueue& GetMainlineTaskQueue();
            virtual TaskQueue& GetAsyncTaskQueue();
            virtual void Update(size_t timeout);
            //! @}

        private:
            TaskQueue m_mainlineTaskQueue;
            std::unique_ptr<ThreadPool> m_threadPool;
        };
    }   //  namespace core
}   //  namespace spire

#endif  //  SPIRE_CORE_DEFAULT_TASK_SERVICE_HPP

