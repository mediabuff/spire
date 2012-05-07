////////////////////////////////////////////////////////////////////////////////
//  Copyright (C) 2012 Robert Engeln (engeln@gmail.com) All rights reserved.
//  See accompanying LICENSE file for full license information.
////////////////////////////////////////////////////////////////////////////////

#include "prefix.hpp"
#include "spire/core/factory.hpp"
#include "spire/loader/file.hpp"
#include "spire/loader/file_provider.hpp"
#include "spire/loader/file_protocol.hpp"
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
    auto i = m_protocols.find(name);
    if (i != m_protocols.end())
    {
        throw ProtocolAlreadyRegisteredError(boost::format("Protocol \"%s\" was already registered")
                                             % protocol);
    }
    m_protocols.insert(std::make_pair(std::move(name), std::move(protocol)));
}

FileProvider& DefaultLoaderService::Mount(const char* uri,
                                          const char* mount)
{
    std::string uriStr = uri, mountStr = mount;
    auto protocol = uriStr.substr(0, uriStr.find_first_of(':')),
         path     = uriStr.substr(uriStr.find_first_of(':') + 1);
    if (!protocol.length() || path.length() < 3 || path[0] != '/' || path[1] != '/')
    {
        throw MalformedUriError(boost::format("\"%s\" is not a valid URI")
                                % uri);
    }
    path = path.substr(2);

    auto i = m_protocols.find(protocol);
    if (i == m_protocols.end())
    {
        throw MalformedUriError(boost::format("Unknown protocol \"%s\" in URI \"%s\"")
                                % protocol
                                % uri);
    }

    //  Canonicalize the path - should end with /, but not start with it
    if (mountStr.find_first_of('/') == 0)
    {
        mountStr.erase(0, 1);
    }
    if (mountStr.find_last_of('/') + 1 != mountStr.size())
    {
        mountStr.push_back('/');
    }
    
    auto provider = i->second->CreateProvider(path.c_str());
    m_providers.push_back(std::make_pair(std::move(mountStr), std::move(provider)));
}

void DefaultLoaderService::Unmount(FileProvider& provider)
{
    m_providers.erase(std::remove_if(m_providers.begin(),
                                     m_providers.end(),
                                     [&] (FileProvider& p) { return &p == &provider; }),
                      m_providers.end());
}

std::shared_ptr<File> DefaultLoaderService::Open(const char* path)
{
    std::string pathStr = path;

    //  Remove any prefix '/' from the path
    if (pathStr.find_first_of('/') == 0)
    {
        pathStr.erase(0, 1);
    }

    for (auto i = m_providers.rbegin(); i != m_providers.rend(); ++i)
    {
        if (pathStr.compare(0, i->first.size(), i->first, 0, i->first.size()) == 0)
        {
            auto filePtr = i->second->Open(pathStr.substr(i->first.size()).c_str());
            if (filePtr)
            {
                return std::shared_ptr<File>(filePtr.get());
            }
        }
    }
    throw FileNotFoundError(boost::format("File \"%s\" was not found")
                            % path);
}
