////////////////////////////////////////////////////////////////////////////////
//  Copyright (C) 2012 Robert Engeln (engeln@gmail.com)
//  See accompanying LICENSE file for full license information.
////////////////////////////////////////////////////////////////////////////////
/// @file spire/common/xml_serializer.hpp 
/// Defines the XmlSerializer class.
/// @addtogroup common
/// @{

#ifndef SPIRE_COMMON_XML_SERIALIZER_HPP
#define SPIRE_COMMON_XML_SERIALIZER_HPP

#include "spire/common/property.hpp"

namespace spire
{
    namespace common
    {
        ///
        /// Thrown when a parse error occurs during serialization.
        ///
        typedef Error<struct _XmlParseError, DataError> XmlParseError;

        ///
        /// Serializes properties to and from XML.
        ///
        class XmlSerializer
        {
        public:
            XmlSerializer(Property);

            //
            //  Serializes an object to an ostream.
            //
            friend std::ostream& operator<<(std::ostream&, XmlSerializer&);

            //
            //  Serializes an object to an XML node.
            //
            friend rapidxml::xml_node<>& operator<<(rapidxml::xml_node<>&, XmlSerializer&);

            //
            //  Serializes an object to a string.
            //
            friend std::string& operator<<(std::string&, XmlSerializer&);

            //
            //  Deserializes an object from a istream containing XML data.
            //
            friend std::istream& operator>>(std::istream&, XmlSerializer&);

            //
            //  Deserializes an object from an XML node.
            //
            friend const rapidxml::xml_node<>& operator>>(const rapidxml::xml_node<>&, XmlSerializer&);

            //
            //  Deserializes an object from a string containing XML data.
            //
            friend const std::string& operator>>(const std::string&, XmlSerializer&);

        private:
            Property m_prop;
        };
    }   //  namespace common
    using common::XmlSerializer;
}   //  namespace spire

#endif  //  SPIRE_COMMON_XML_SERIALIZER_HPP
