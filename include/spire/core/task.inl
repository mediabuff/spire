////////////////////////////////////////////////////////////////////////////////
//  Copyright (C) 2012 Robert Engeln (engeln@gmail.com) All rights reserved.
//  See accompanying LICENSE file for full license information.
////////////////////////////////////////////////////////////////////////////////
///
/// @file spire/core/task.inl
/// Inline functions for Task, IndependentTask and DependentTask.
/// @addtogroup core
/// @{

#ifndef SPIRE_CORE_TASK_INL
#define SPIRE_CORE_TASK_INL

namespace spire
{
    namespace core
    {
        template <typename T>
        inline IndependentTask<T>::IndependentTask(T&& fn)
        : m_fn(std::forward<T>(fn))
        {
        }

        template <typename T>
        inline IndependentTask<T>::~IndependentTask()
        {
        }

        template <typename T>
        inline bool IndependentTask<T>::Ready() const
        {
            return true;
        }

        template <typename T>
        inline void IndependentTask<T>::Run()
        {
            m_fn();
        }

        template <typename T, typename F>
        inline DependentTask<T, F>::DependentTask(T&& fn, F&& future)
        : m_fn(std::forward<T>(fn)), m_future(std::forward<F>(future))
        {
        }

        template <typename T, typename F>
        inline DependentTask<T, F>::~DependentTask()
        {
        }

        template <typename T, typename F>
        inline bool DependentTask<T, F>::Ready() const
        {
            return m_future.is_ready();
        }

        template <typename T, typename F>
        inline void DependentTask<T, F>::Run()
        {
            assert(Ready());
            m_fn();
        }
    }   //  namespace core
}   //  namespace spire

#endif  //  SPIRE_CORE_TASK_INL

