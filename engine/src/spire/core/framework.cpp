////////////////////////////////////////////////////////////////////////////////
//  Copyright (C) 2012 Robert Engeln (engeln@gmail.com) All rights reserved.
//  See accompanying LICENSE file for full license information.
////////////////////////////////////////////////////////////////////////////////

#include "prefix.hpp"
#include "spire/common/version.hpp"
#include "spire/core/framework.hpp"

using namespace spire;
using namespace core;

namespace spire
{
    namespace core
    {
        Framework& GetFrameworkInstance()
        {
            static Framework instance;
            return instance;
        }
    }
}

extern "C" __declspec(dllexport)
Framework* GetCoreFrameworkInstance(int cppVer, const char* spireVer)
{
    if (cppVer != _CPPLIB_VER ||
        strcmp(spireVer, SPIRE_VERSION_COMMIT) != 0)
    {
        return nullptr;
    }
    return &GetFrameworkInstance();
}

Framework::Framework()
{
}

Framework::~Framework()
{
}
