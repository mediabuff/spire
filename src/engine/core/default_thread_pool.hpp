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

namespace spire
{
    namespace core
    {
        ///
        /// Default implementation of ThreadPool.
        ///
        class DefaultThreadPool : public ThreadPool
        {
        public:
            ///
            /// Constructor.
            ///
            DefaultThreadPool();

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
            std::unique_ptr<TaskQueue> m_taskQueue;
        };
    }
}

#endif  //  SPIRE_CORE_DEFAULT_THREAD_POOL

