////////////////////////////////////////////////////////////////////////////////
//  Copyright (C) 2012 Robert Engeln (engeln@gmail.com) All rights reserved.
//  See accompanying LICENSE file for full license information.
////////////////////////////////////////////////////////////////////////////////

#include "prefix.hpp"
#include "spire/core/task.hpp"
#include "default_task_service.hpp"

using namespace spire;
using namespace core;

DefaultTaskService::DefaultTaskService()
{
}

DefaultTaskService::~DefaultTaskService()
{
}

TaskQueue& DefaultTaskService::GetMainlineTaskQueue()
{
    return m_mainlineTaskQueue;
}

void DefaultTaskService::Update(size_t timeout)
{
    std::unique_ptr<Task> task;
    while (task = m_mainlineTaskQueue.Pop())
    {
        task->Run();
    }
}
