////////////////////////////////////////////////////////////////////////////////
//  Copyright (C) 2012 Robert Engeln (engeln@gmail.com) All rights reserved.
//  See accompanying LICENSE file for full license information.
////////////////////////////////////////////////////////////////////////////////
///
/// @file spire/core/task.hpp
/// Defines the Task, IndepdenentTask, and DependentTask classes.
/// @addtogroup core
/// @{

#ifndef SPIRE_CORE_TASK_HPP
#define SPIRE_CORE_TASK_HPP

namespace spire
{
	namespace core
	{
		///
		///	Encapsulates an asynchronous work unit.
		///
		class Task
		{
		public:
			///
			///	Destructor.
			///
			virtual ~Task() = 0 { };

			///
			///	Checks if the task is ready to execute.
			///
			virtual bool Ready() const = 0;

			///
			///	Executes the task.
			///
			virtual void Run() = 0;
		};

        ///
        /// Simple task ready to run immediately.
        ///
        template <typename T>
        class IndependentTask : public Task
        {
        public:
            ///
            /// Constructor.
            ///
            /// @param fn Code to execute.
            ///
            IndependentTask(T&& fn);

            ///
            /// Destructor.
            ///
            virtual ~IndependentTask();

            ///
            /// From Task.
            /// @{
            virtual bool Ready() const;
            virtual void Run();
            //! @}

        private:
            T m_fn;
        };

		///
		///	Simple task dependent on a future to run.
		///
		///	@tparam T Callable type.
        /// @tparam F Future type.
		///
		template <typename T, typename F>
		class DependentTask : public Task
		{
		public:
			///
			///	Constructor.
			///
			///	@param fn Code to execute.
			///	@param future (Optional) Future to wait on. If empty, the
			///				  task will be ready to run immediately. Otherwise,
			///               it will be ready once the future is ready.
			///
			DependentTask(T&& fn, F&& future);

            ///
            /// Destructor.
            ///
            virtual ~DependentTask();

            ///
            /// From Task.
            /// @{
            virtual bool Ready() const;
            virtual void Run();
            //! @}

        private:
            T m_fn;
            F m_future;
		};

        ///
        /// Generates a Task object.
        /// @{
        template <typename T>
        std::unique_ptr<Task> MakeTask(T&& fn);

        template <typename T, typename F>
        std::unique_ptr<Task> MakeTask(F&& future, T&& fn);
        //! @}

	}	//	namespace core
}	//	namespace spire

#endif	//	SPIRE_CORE_TASK_HPP
