////////////////////////////////////////////////////////////////////////////////
//  Copyright (C) 2012 Robert Engeln (engeln@gmail.com) All rights reserved.
//  See accompanying LICENSE file for full license information.
////////////////////////////////////////////////////////////////////////////////

#include "prefix.hpp"
#include "spire/common/version.hpp"
#include "spire/core/factory.hpp"
#include "spire/core/service.hpp"
#include "default_framework.hpp"

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

void DefaultFramework::RegisterService(std::string type, Service* svc)
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

Service& DefaultFramework::AcquireService(const std::string& type)
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

void DefaultFramework::Register(std::unique_ptr<Factory> factory, std::string name)
{
    m_factoryMap[std::move(name)] = std::move(factory);
}

Factory& DefaultFramework::AcquireFactory(const std::string& name)
{
    auto i = m_factoryMap.find(name);
    if (i == m_factoryMap.end())
    {
        throw FactoryNotFoundError(boost::format("No factory named \"%s\" was registered")
                                   % name);
    }
    return *i->second;
}

void DefaultFramework::LoadModule(const char* name)
{
    // TODO: refactor this into a platform-independent interface
    // TODO: add verification that the module is a spire module before loading it
    char path[MAX_PATH] = {0};
    sprintf_s(path, "%s.dll", name);

    HMODULE hmod;
    WIN_CHECK(hmod = LoadLibraryExA(path, NULL, 0));

}
