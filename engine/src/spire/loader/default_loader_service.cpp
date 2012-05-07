////////////////////////////////////////////////////////////////////////////////
//  Copyright (C) 2012 Robert Engeln (engeln@gmail.com) All rights reserved.
//  See accompanying LICENSE file for full license information.
////////////////////////////////////////////////////////////////////////////////

#include "prefix.hpp"
#include "spire/core/factory.hpp"
#include "default_loader_service.hpp"

using namespace spire;
using namespace loader;

namespace
{
    AutoRegisterFactory<BasicFactory<DefaultLoaderService, LoaderServiceFactory>>
        registerDefaultLoaderServiceFactory("DefaultLoaderService");
}

DefaultLoaderService::DefaultLoaderService()
{
}

DefaultLoaderService::~DefaultLoaderService()
{
}

void DefaultLoaderService::RegisterProtocol(std::unique_ptr<FileProtocol> protocol,
                                            const char* name)
{
}

void DefaultLoaderService::Mount(const char* uri,
                                 const char* mount)
{
}

std::shared_ptr<File> DefaultLoaderService::Open(const char* path)
{
    return std::shared_ptr<File>(nullptr);
}
