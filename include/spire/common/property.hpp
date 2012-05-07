////////////////////////////////////////////////////////////////////////////////
//  Copyright (C) 2012 Robert Engeln (engeln@gmail.com)
//  See accompanying LICENSE file for full license information.
////////////////////////////////////////////////////////////////////////////////
/// @file spire/common/property.hpp 
/// Defines the Property class.
/// @addtogroup common
/// @{

#ifndef SPIRE_COMMON_PROPERTY_HPP
#define SPIRE_COMMON_PROPERTY_HPP

#include "spire/common/boolean_property.hpp"
#include "spire/common/integer_property.hpp"
#include "spire/common/real_property.hpp"
#include "spire/common/string_property.hpp"
#include "spire/common/enum_property.hpp"
#include "spire/common/collection_property.hpp"
#include "spire/common/dictionary_property.hpp"
#include "spire/common/object_property.hpp"
#include "spire/common/property_host.hpp"
#include "spire/common/property_wrapper.hpp"
#include "spire/common/property_traits.hpp"

namespace spire
{
    namespace common
    {
        struct PropertyTypes
        {
            ///
            /// Property types.
            ///
            enum PropertyType
            {
                Empty,                  //!< Property is empty.
                Boolean,                //!< Contains a BooleanProperty.
                Integer,                //!< Contains an IntegerProperty.
                Real,                   //!< Contains a RealProperty.
                String,                 //!< Contains a StringProperty.
                Enum,                   //!< Contains an EnumProperty.
                Collection,             //!< Contains a CollectionProperty.
                Dictionary,             //!< Contains a DictionaryProperty.
                Object,                 //!< Contains an ObjectProperty.
                Max
            };
        };
        typedef PropertyTypes::PropertyType PropertyType;

        ///
        /// Error thrown when an attempt is made to cast a Property to a different
        /// type than the inner object it contains.
        ///
        typedef Error<struct _PropertyTypeError, RuntimeError> PropertyTypeError;

        ///
        /// Encapsulates an object via an interface which enables reflection.
        ///
        class Property
        {
        public:
            ///
            /// Constructs an empty property.
            ///
            Property();

            ///
            /// Copy constructor.
            ///
            Property(Property&);
            
            ///
            /// Move constructor.
            ///
            Property(Property&&);
            
            ///
            ///  Construct a wrapper over an arbitrary object.
            ///
            template <typename T>
            Property(T& ref);

            ///
            /// Returns the property type.
            ///
            PropertyType Type() const;

            ///
            /// Returns true if the property object is empty.
            ///
            bool Empty() const;
                       
            ///
            /// Returns the inner BooleanProperty object.
            ///
            /// @throw PropertyTypeError The Property did not contain a BooleanProperty.
            /// @{
            BooleanProperty& AsBool();
            const BooleanProperty& AsBool() const;
            //! @}

            ///
            /// Returns the inner IntegerProperty object.
            ///
            /// @throw PropertyTypeError The Property did not contain an IntegerProperty.
            /// @{
            IntegerProperty& AsInt();
            const IntegerProperty& AsInt() const;
            //! @}

            ///
            /// Returns the inner RealProperty object.
            ///
            /// @throw PropertyTypeError The Property did not contain a RealProperty.
            /// @{
            RealProperty& AsReal();
            const RealProperty& AsReal() const;
            //! @}

            ///
            /// Returns the inner StringProperty object.
            ///
            /// @throw PropertyTypeError The Property did not contain a StringProperty.
            /// @{
            StringProperty& AsString();
            const StringProperty& AsString() const;
            //! @}

            ///
            /// Returns the inner EnumProperty object.
            ///
            /// @throw PropertyTypeError The Property did not contain an EnumProperty.
            /// @{
            EnumProperty& AsEnum();
            const EnumProperty& AsEnum() const;
            //! @}

            ///
            /// Returns the inner ObjectProperty object.
            ///
            /// @throw PropertyTypeError The Property did not contain an ObjectProperty.
            /// @{
            ObjectProperty& AsObject();
            const ObjectProperty& AsObject() const;
            //! @}

            ///
            /// Returns the inner CollectionProperty object.
            ///
            /// @throw PropertyTypeError The Property did not contain a CollectionProperty.
            /// @{
            CollectionProperty& AsCollection();
            const CollectionProperty& AsCollection() const;
            //! @}

            ///
            /// Returns the inner DictionaryProperty object.
            ///
            /// @throw PropertyTypeError The Property did not contain a DictionaryProperty.
            /// @{
            DictionaryProperty& AsDictionary();
            const DictionaryProperty& AsDictionary() const;
            //! @}

        private:
            struct EmptyProperty 
            {
                // failing to explicitly declare a constructor results in a
                // compiler warning on Visual C++
                EmptyProperty() { };
            };
            typedef boost::variant<EmptyProperty,
                                   BooleanProperty,
                                   IntegerProperty,
                                   RealProperty,
                                   StringProperty,
                                   EnumProperty,
                                   CollectionProperty,
                                   DictionaryProperty,
                                   ObjectProperty> PropertyVariant;
            PropertyVariant m_variant;
        };
    }   //  namespace common
    using common::Property;
    using common::PropertyType;
    using common::PropertyTypes;
    using common::BooleanProperty;
    using common::IntegerProperty;
    using common::RealProperty;
    using common::StringProperty;
    using common::EnumProperty;
    using common::CollectionProperty;
    using common::DictionaryProperty;
    using common::ObjectProperty;
    using common::PropertyHost;
    using common::PropertyTraits;
}   //  namespace spire

#include "spire/common/property.inl"
#include "spire/common/boolean_property.inl"
#include "spire/common/integer_property.inl"
#include "spire/common/real_property.inl"
#include "spire/common/string_property.inl"
#include "spire/common/enum_property.inl"
#include "spire/common/collection_property.inl"
#include "spire/common/dictionary_property.inl"
#include "spire/common/object_property.inl"
#include "spire/common/property_wrapper.inl"
#include "spire/common/property_traits.inl"

#endif  //  SPIRE_COMMON_PROPERTY_HPP
