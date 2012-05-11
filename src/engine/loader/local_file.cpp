////////////////////////////////////////////////////////////////////////////////
//  Copyright (C) 2012 Robert Engeln (engeln@gmail.com)
//  See accompanying LICENSE file for full license information.
////////////////////////////////////////////////////////////////////////////////

#include "prefix.hpp"
#include "local_file.hpp"

using namespace spire;
using namespace loader;

LocalFile::LocalFile(const char* path)
{
}

LocalFile::~LocalFile()
{
}

size_t LocalFile::Size() const
{
}

boost::unique_future<std::vector<char>> LocalFile::Read(size_t offset, size_t count) const
{
}
