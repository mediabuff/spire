////////////////////////////////////////////////////////////////////////////////
//  Copyright (C) 2012 Robert Engeln (engeln@gmail.com) All rights reserved.
//  See accompanying LICENSE file for full license information.
////////////////////////////////////////////////////////////////////////////////
///
/// @file spire/core/default_thread_pool.hpp
/// Defines the DefaultThreadPool class.
/// @addtogroup core
/// @{

#ifndef SPIRE_CORE_DEFAULT_THREAD_POOL
#define SPIRE_CORE_DEFAULT_THREAD_POOL

#include "spire/core/thread_pool.hpp"
#include "spire/core/task_queue.hpp"

namespace spire
{
    namespace core
    {
        ///
        /// Default implementation of ThreadPool.
        ///
        class DefaultThreadPool : public ThreadPool,
                                  public boost::noncopyable
        {
        public:
            ///
            /// Constructor.
            ///
            /// @param threadCount Maximum number of threads to spawn.
            ///
            DefaultThreadPool(int threadCount);

            ///
            /// Destructor.
            ///
            virtual ~DefaultThreadPool();

            ///
            /// From ThreadPool.
            /// @{
            virtual TaskQueue& GetTaskQueue();
            //! @}

        private:
            static void Worker(DefaultThreadPool& threadPool);

            TaskQueue m_taskQueue;
            std::vector<boost::thread> m_threads;
            bool m_exit;
        };
    }
}

#endif  //  SPIRE_CORE_DEFAULT_THREAD_POOL

