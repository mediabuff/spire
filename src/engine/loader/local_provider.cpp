////////////////////////////////////////////////////////////////////////////////
//  Copyright (C) 2012 Robert Engeln (engeln@gmail.com)
//  See accompanying LICENSE file for full license information.
////////////////////////////////////////////////////////////////////////////////

#include "prefix.hpp"
#include "local_provider.hpp"

using namespace spire;
using namespace loader;

LocalProvider::LocalProvider(const char* path)
{
}

LocalProvider::~LocalProvider()
{
}

std::unique_ptr<File> LocalProvider::Open(const char* path)
{
}
