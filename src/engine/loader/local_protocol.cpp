////////////////////////////////////////////////////////////////////////////////
//  Copyright (C) 2012 Robert Engeln (engeln@gmail.com)
//  See accompanying LICENSE file for full license information.
////////////////////////////////////////////////////////////////////////////////

#include "prefix.hpp"
#include "local_protocol.hpp"

using namespace spire;
using namespace loader;

LocalProtocol::LocalProtocol()
{
}

LocalProtocol::~LocalProtocol()
{
}

std::unique_ptr<FileProvider> LocalProtocol::CreateProvider(const char* path)
{
}
