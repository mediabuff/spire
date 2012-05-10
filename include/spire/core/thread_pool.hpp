////////////////////////////////////////////////////////////////////////////////
//  Copyright (C) 2012 Robert Engeln (engeln@gmail.com) All rights reserved.
//  See accompanying LICENSE file for full license information.
////////////////////////////////////////////////////////////////////////////////
///
/// @file spire/core/thread_pool.hpp
/// Defines the ThreadPool class.
/// @addtogroup core
/// @{

#ifndef SPIRE_CORE_THREAD_POOL_HPP
#define SPIRE_CORE_THREAD_POOL_HPP

namespace spire
{
    namespace core
    {
        class TaskQueue;

        ///
        /// Thread pool for excuting tasks from a TaskQueue.
        ///
        class ThreadPool
        {
        public:
            ///
            /// Destructor.
            ///
            virtual ~ThreadPool() = 0 { };

            ///
            /// Returns the TaskQueue associated with the thread pool.
            ///
            virtual TaskQueue& GetTaskQueue() = 0;
        };
    }   //  namespace core
}   //  namespace spire

#endif  //  SPIRE_CORE_THREAD_POOL_HPP

