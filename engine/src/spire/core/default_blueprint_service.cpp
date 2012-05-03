////////////////////////////////////////////////////////////////////////////////
//  Copyright (C) 2012 Robert Engeln (engeln@gmail.com) All rights reserved.
//  See accompanying LICENSE file for full license information.
////////////////////////////////////////////////////////////////////////////////

#include "prefix.hpp"
#include "spire/common/property.hpp"
#include "spire/common/xml_serializer.hpp"
#include "spire/core/blueprint.hpp"
#include "spire/core/default_blueprint_service.hpp"

using namespace spire;
using namespace core;

namespace
{
    struct AutoRegisterFactories
    {
        AutoRegisterFactories()
        {
            GetFramework().Register(std::unique_ptr<Factory>(new BasicFactory<DefaultBlueprintService, BlueprintServiceFactory>()),
                                    "DefaultBlueprintService");
        }
    };
}
AutoRegisterFactories autoreg;

DefaultBlueprintService::DefaultBlueprintService()
{
}

DefaultBlueprintService::~DefaultBlueprintService()
{
}

void DefaultBlueprintService::Register(std::string name,
                                       std::unique_ptr<Blueprint> prototype)
{
    m_prototypeMap.insert(std::make_pair(std::move(name),
                                         std::move(prototype)));
}

const Blueprint& DefaultBlueprintService::AcquireBlueprint(const std::string& type,
                                                           const std::string& name)
{
    auto i = m_blueprintMap.find(type);
    if (i != m_blueprintMap.end())
    {
        auto j = i->second.find(name);
        if (j != i->second.end())
        {
            return *j->second;
        }
    }
    throw BlueprintNotFoundError(boost::format("No blueprint was found for \"%s\" (\"%s\")")
                                 % name
                                 % type);
}

void DefaultBlueprintService::Parse(std::vector<char> src)
{
    rapidxml::xml_document<> doc;
    doc.parse<0>(src.data());
    auto root = doc.first_node();
    if (!root)
    {
        throw BlueprintParsingError("No root element");
    }
    else
    {
        for (auto node = root->first_node();
             node != nullptr; 
             node = node->next_sibling())
        {
            auto nameAttr = node->first_attribute("name", 0, false);
            if (!nameAttr || !nameAttr->value_size())
            {
                throw BlueprintParsingError("Missing \"name\" attribute");
            }
            auto clone = GetPrototype(node->name()).Clone();
            *node >> XmlSerializer(*clone);
            m_blueprintMap[clone->GetType()][nameAttr->value()] = std::move(clone);
        }
    }
}

const Blueprint& DefaultBlueprintService::GetPrototype(const std::string& type)
{
    auto i = m_prototypeMap.find(type);
    if (i == m_prototypeMap.end())
    {
        throw BlueprintPrototypeNotFoundError(boost::format("No prototype was registered for \"%s\"")
                                              % type);
    }
    return *i->second;
}