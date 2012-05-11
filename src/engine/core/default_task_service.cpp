////////////////////////////////////////////////////////////////////////////////
//  Copyright (C) 2012 Robert Engeln (engeln@gmail.com) All rights reserved.
//  See accompanying LICENSE file for full license information.
////////////////////////////////////////////////////////////////////////////////

#include "prefix.hpp"
#include "spire/core/task.hpp"
#include "spire/core/thread_pool.hpp"
#include "default_task_service.hpp"
#include "default_thread_pool.hpp"

using namespace spire;
using namespace core;

namespace
{
    AutoRegisterFactory<BasicFactory<DefaultTaskService, TaskServiceFactory>>
        registerDefaultTaskServiceFactory("DefaultTaskService");
}

DefaultTaskService::DefaultTaskService()
{
    // FIXME do not hard code the number of threads!
    m_threadPool.reset(new DefaultThreadPool(1));
}

DefaultTaskService::~DefaultTaskService()
{
}

TaskQueue& DefaultTaskService::GetMainlineTaskQueue()
{
    return m_mainlineTaskQueue;
}

TaskQueue& DefaultTaskService::GetAsyncTaskQueue()
{
    assert(m_threadPool);
    return m_threadPool->GetTaskQueue();
}

void DefaultTaskService::Update(size_t timeout)
{
    std::unique_ptr<Task> task;
    while (task = m_mainlineTaskQueue.Pop())
    {
        task->Run();
    }
}
