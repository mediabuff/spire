////////////////////////////////////////////////////////////////////////////////
//  Copyright (C) 2012 Robert Engeln (engeln@gmail.com) All rights reserved.
//  See accompanying LICENSE file for full license information.
////////////////////////////////////////////////////////////////////////////////

#include "prefix.hpp"
#include "spire/core/default_factory_service.hpp"

using namespace spire;
using namespace core;

DefaultFactoryService::DefaultFactoryService()
{
}

DefaultFactoryService::~DefaultFactoryService()
{
}

void DefaultFactoryService::Register(std::string name,
                                     std::unique_ptr<Factory> prototype)
{

}

Factory& DefaultFactoryService::Acquire(std::string type,
                                        std::string name)
{

}

