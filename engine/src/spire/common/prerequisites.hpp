////////////////////////////////////////////////////////////////////////////////
//  Copyright (C) 2012 Robert Engeln (engeln@gmail.com) All rights reserved.
//  See accompanying LICENSE file for full license information.
////////////////////////////////////////////////////////////////////////////////
///
/// @file spire/common/prerequisites.hpp
/// This header is included by all of the prefix.hpp headers and includes the
/// minimum requirements across all projects.
///

#ifndef SPIRE_COMMON_PREREQUISITES_HPP
#define SPIRE_COMMON_PREREQUISITES_HPP

#define WIN32_LEAN_AND_MEAN
#include <Windows.h>
#include <tchar.h>

#undef min
#undef max

#include <algorithm>
#include <array>
#include <cassert>
#include <cmath>
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <exception>
#include <list>
#include <map>
#include <utility>
#include <vector>

#include <boost/exception/all.hpp>
#include <boost/format.hpp>
#include <boost/type_traits.hpp>
#include <boost/utility.hpp>
#include <boost/variant.hpp>

#include <rapidxml.hpp>

#ifdef SPIRE_UNITTEST
#   include <gtest/gtest.h>
#   include <gmock/gmock.h>
//  Necessary to special case these libraries because the names are different
//  in debug and release builds, which .props files can't easily handle.
#   ifdef _DEBUG
#       pragma comment(lib, "gtestd.lib")
#       pragma comment(lib, "gtest_maind.lib")
#   else
#       pragma comment(lib, "gtest.lib")
#       pragma comment(lib, "gtest_main.lib")
#   endif
#endif

#include "spire/common/exception.hpp"
#include "spire/common/get_framework.hpp"

#endif  //  SPIRE_COMMON_PREREQUISITES_HPP
