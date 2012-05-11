////////////////////////////////////////////////////////////////////////////////
//  Copyright (C) 2012 Robert Engeln (engeln@gmail.com) All rights reserved.
//  See accompanying LICENSE file for full license information.
////////////////////////////////////////////////////////////////////////////////

#include "prefix.hpp"
#include "spire/core/task.hpp"
#include "spire/core/task_queue.hpp"

using namespace spire;

TEST(TaskQueueTests, TasksQueueIsOrderedByPriority)
{
    std::unique_ptr<Task> task1 = MakeTask([] {});
    std::unique_ptr<Task> task2 = MakeTask([] {});
    std::unique_ptr<Task> task3 = MakeTask([] {});

    Task* task1Ptr = task1.get();
    Task* task2Ptr = task2.get();
    Task* task3Ptr = task3.get();

    TaskQueue queue;
    queue.Push(std::move(task1), 1);
    queue.Push(std::move(task2), 0);
    queue.Push(std::move(task3), 2);

    auto task = queue.Pop();
    ASSERT_EQ(task.get(), task2Ptr);
    task = queue.Pop();
    ASSERT_EQ(task.get(), task1Ptr);
    task = queue.Pop();
    ASSERT_EQ(task.get(), task3Ptr);
}

TEST(TaskQueueTests, DependentTasksAreNotReadyUntilFutureHasValue)
{
    boost::promise<int> promise;
    std::unique_ptr<Task> task1 = MakeTask(promise.get_future(), [] {});

    TaskQueue queue;
    queue.Push(std::move(task1), 0);

    ASSERT_FALSE(queue.Empty());
    auto task = queue.Pop();
    ASSERT_EQ(task.get(), nullptr);

    promise.set_value(0);
    task = queue.Pop();
    ASSERT_TRUE(queue.Empty());
}
