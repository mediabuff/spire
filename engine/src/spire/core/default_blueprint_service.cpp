////////////////////////////////////////////////////////////////////////////////
//  Copyright (C) 2012 Robert Engeln (engeln@gmail.com) All rights reserved.
//  See accompanying LICENSE file for full license information.
////////////////////////////////////////////////////////////////////////////////

#include "prefix.hpp"
#include "spire/core/blueprint.hpp"
#include "spire/core/default_blueprint_service.hpp"

using namespace spire;
using namespace core;

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

Blueprint& DefaultBlueprintService::Acquire(std::string type,
                                            std::string name)
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
    throw BlueprintNotFoundError(boost::format("No factory was found for \"%s\" (\"%s\")")
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
        }
    }
}
