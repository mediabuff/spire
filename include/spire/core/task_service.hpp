////////////////////////////////////////////////////////////////////////////////
//  Copyright (C) 2012 Robert Engeln (engeln@gmail.com) All rights reserved.
//  See accompanying LICENSE file for full license information.
////////////////////////////////////////////////////////////////////////////////
///
/// @file spire/core/task_service.hpp
/// Defines the TaskService interface.
/// @addtogroup core
/// @{

#ifndef SPIRE_CORE_TASK_SERVICE_HPP
#define SPIRE_CORE_TASK_SERVICE_HPP

#include "spire/core/service.hpp"

namespace spire
{
	namespace core
	{
        class TaskQueue;

		///
		///	Global task scheduler.
		//
		class TaskService : public Service
		{
		public:
            ///
            /// Destructor.
            /// 
            virtual ~TaskService() = 0 { };

            ///
            /// Returns the mainline task queue.
            ///
            /// Tasks in the mainline queue are executed on the main
            /// thread whenever Update() is called.
            ///
            virtual TaskQueue& GetMainlineTaskQueue() = 0;

            ///
            /// Runs tasks in the mainline queue.
            ///
            /// @param timeout Maximum amount of time to spend, in ms.
            ///                A task will not be interrupted if the timeout
            ///                is exceeded, but after it completes no new tasks
            ///                will run. If zero, will run until all tasks
            ///                are completed.
            ///
            virtual void Update(size_t timeout) = 0;
		};
	}	//	namespace core
}	//	namespace spire

#endif	//	SPIRE_CORE_TASK_SERVICE_HPP
