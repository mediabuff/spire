////////////////////////////////////////////////////////////////////////////////
//  Copyright (C) 2012 Robert Engeln (engeln@gmail.com) All rights reserved.
//  See accompanying LICENSE file for full license information.
////////////////////////////////////////////////////////////////////////////////

#include "prefix.hpp"
#include "spire/common/version.hpp"
#include "spire/core/default_framework.hpp"
#include "spire/core/service.hpp"

using namespace spire;
using namespace core;

extern "C" __declspec(dllexport)
Framework* GetCoreFrameworkInstance(int cppVer, const char* spireVer)
{
    if (cppVer != _CPPLIB_VER ||
        strcmp(spireVer, SPIRE_VERSION_COMMIT) != 0)
    {
        return nullptr;
    }
    static DefaultFramework instance;
    return static_cast<Framework*>(&instance);
}

DefaultFramework::DefaultFramework()
{
}

DefaultFramework::~DefaultFramework()
{
    //  Destroy all attached services so they will unregister now instead
    //  of after the Framework has been invalidated
    m_servicePtrs.clear();
}

void DefaultFramework::RegisterUntyped(std::string type, Service* svc)
{
    auto i = m_serviceMap.find(type);
    if (svc)
    {
        if (i != m_serviceMap.end())
        {
            throw ServiceAlreadyRegisteredError(boost::format("A service was already registered for \"%s\"")
                                                % type);
        }
        m_serviceMap[type] = svc;
    }
    else
    {
        if (i != m_serviceMap.end())
        {
            m_serviceMap.erase(i);
        }
    }
}

Service& DefaultFramework::AcquireUntyped(std::string type)
{
    auto i = m_serviceMap.find(type);
    if (i == m_serviceMap.end())
    {
        throw ServiceNotFoundError(boost::format("No service was found for \"%s\"")
                                                 % type);
    }
    return *i->second;
}            

void DefaultFramework::Attach(std::unique_ptr<Service> svc)
{
    m_servicePtrs.push_back(std::move(svc));
}
