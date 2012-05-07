////////////////////////////////////////////////////////////////////////////////
//  Copyright (C) 2012 Robert Engeln (engeln@gmail.com) All rights reserved.
//  See accompanying LICENSE file for full license information.
////////////////////////////////////////////////////////////////////////////////

#include "prefix.hpp"
#include "spire/common/get_framework.hpp"
#include "spire/common/version.hpp"
#include "spire/core/framework.hpp"

using namespace spire;
using namespace common;

namespace
{
    Framework* g_frameworkPtr = nullptr;    
}

namespace spire
{
    namespace common
    {
        Framework& GetFramework()
        {
            if (!g_frameworkPtr)
            {
                HMODULE coreDll = LoadLibraryA("spire_core.dll");
                WIN_CHECK(coreDll != nullptr);

                //  The parameters are C++ runtime version and Spire version, respectively
                typedef Framework* (*GetCoreFrameworkInstanceProc)(int, const char*);
                GetCoreFrameworkInstanceProc getCoreFrameworkInstance = reinterpret_cast<GetCoreFrameworkInstanceProc>
                    (GetProcAddress(coreDll, "GetCoreFrameworkInstance"));
                WIN_CHECK(getCoreFrameworkInstance != nullptr);
        
                g_frameworkPtr = getCoreFrameworkInstance(_CPPLIB_VER, SPIRE_VERSION_COMMIT);
                CHECK(RuntimeError, g_frameworkPtr != nullptr);
            }
            return *g_frameworkPtr;
        }
    }  
}
