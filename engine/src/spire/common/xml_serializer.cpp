////////////////////////////////////////////////////////////////////////////////
//  Copyright (C) 2012 Robert Engeln (engeln@gmail.com)
//  See accompanying LICENSE file for full license information.
////////////////////////////////////////////////////////////////////////////////

#include "prefix.hpp"
#include "spire/common/xml_serializer.hpp"

using namespace spire;
using namespace spire::common;

XmlSerializer::XmlSerializer(Property p)
: m_prop(p)
{
}

std::ostream& spire::common::operator<<(std::ostream& os, XmlSerializer& xs)
{
    Property p = xs.m_prop;
    if (!p.Empty())
    {
    }
    return os;
}

rapidxml::xml_node<>& spire::common::operator<<(rapidxml::xml_node<>& node, XmlSerializer& xs)
{
    Property p = xs.m_prop;
    if (!p.Empty())
    {
    }
    return node;
}

std::istream& spire::common::operator>>(std::istream& is, XmlSerializer& xs)
{
    Property p = xs.m_prop;
    if (!p.Empty())
    {
    }
    return is;
}

const rapidxml::xml_node<>& spire::common::operator>>(const rapidxml::xml_node<>& node, XmlSerializer& xs)
{
    std::stringstream ss;
    Property p = xs.m_prop;
    if (!p.Empty())
    {
        switch (p.Type())
        {
        case PropertyTypes::Boolean: 
            {
                bool b;
                ss << node.value();
                ss >> b;
                p.AsBool().Set(b);
                ss.clear();
                break;
            }
        case PropertyTypes::Integer:
            {
                int64_t i;
                ss << node.value();
                ss >> i;
                p.AsInt().Set(i);
                ss.clear();
                break;
            }
        case PropertyTypes::Real:
            {
                double d;
                ss << node.value();
                ss >> d;
                p.AsReal().Set(d);
                ss.clear();
                break;
            }
        case PropertyTypes::String:
            {
                p.AsString().Set(node.value());
                break;
            }
        case PropertyTypes::Collection:
            {
                rapidxml::xml_node<>* itemNode = node.first_node();
                while (itemNode)
                {
                    assert(strcmp(itemNode->name(), "item") == 0);
                    Property itemProp = p.AsCollection().Grow();
                    *itemNode >> XmlSerializer(itemProp);
                    itemNode = itemNode->next_sibling();
                }
                break;
            }
        case PropertyTypes::Dictionary:
            {
                rapidxml::xml_node<>* itemNode = node.first_node();
                while (itemNode)
                {
                    assert(strcmp(itemNode->name(), "item") == 0);
                    rapidxml::xml_attribute<>* keyAttr = itemNode->first_attribute("key");
                    assert(keyAttr != nullptr);
                    Property itemProp = p.AsDictionary().Grow(std::string(keyAttr->value()));
                    *itemNode >> XmlSerializer(itemProp);
                    itemNode = itemNode->next_sibling();
                }
                break;
            }
        case PropertyTypes::Object:
            {
                rapidxml::xml_node<>* fieldNode = node.first_node();
                while (fieldNode)
                {
                    Property fieldProp = p.AsObject().Get(std::string(fieldNode->name()));
                    assert(!fieldProp.Empty());
                    *fieldNode >> XmlSerializer(fieldProp);
                    fieldNode = fieldNode->next_sibling();
                }
                break;
            }
        }
    }
    return node;
}

const std::string& spire::common::operator>>(const std::string& str, XmlSerializer& xs)
{
    std::vector<char> v;
    v.resize(str.size() + 1, 0);
    std::copy(str.begin(), str.end(), v.begin());

    rapidxml::xml_document<> doc;
    doc.parse<0>(v.data());
    *doc.first_node() >> xs;
    return str;
}
