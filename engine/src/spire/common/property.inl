////////////////////////////////////////////////////////////////////////////////
//  Copyright (C) 2012 Robert Engeln (engeln@gmail.com)
//  See accompanying LICENSE file for full license information.
////////////////////////////////////////////////////////////////////////////////

#ifndef SPIRE_COMMON_PROPERTY_INL
#define SPIRE_COMMON_PROPERTY_INL

namespace spire
{
    namespace common
    {
        template <typename T, typename Enabler = void>
        class PropertyProxy;

        inline Property::Property()
        {
        }

        inline Property::Property(Property& cpy)
        : m_variant(cpy.m_variant)
        {
        }

        inline Property::Property(Property&& cpy)
        : m_variant(std::move(cpy.m_variant))
        {
        }

        template <typename T>
        inline Property::Property(T& ref)
        {
            //  NOTE: An error here most likely indicates that PropertyTraits have
            //  not been specialized for the given type, and so it cannot be
            //  encapsulated in a Property object.
            m_variant = PropertyProxy<T>::ToProperty(ref);
        }

        inline BooleanProperty& Property::AsBool()
        {
            auto ptr = boost::get<BooleanProperty>(&m_variant);
            if (!ptr)
            {
                throw PropertyTypeError("Not a BooleanProperty");
            }
            return *ptr;
        }

        inline const BooleanProperty& Property::AsBool() const
        {
            auto ptr = boost::get<BooleanProperty>(&m_variant);
            if (!ptr)
            {
                throw PropertyTypeError("Not a BooleanProperty");
            }
            return *ptr;
        }

        inline IntegerProperty& Property::AsInt()
        {
            auto ptr = boost::get<IntegerProperty>(&m_variant);
            if (!ptr)
            {
                throw PropertyTypeError("Not an IntegerProperty");
            }
            return *ptr;
        }

        inline const IntegerProperty& Property::AsInt() const
        {
            auto ptr = boost::get<IntegerProperty>(&m_variant);
            if (!ptr)
            {
                throw PropertyTypeError("Not an IntegerProperty");
            }
            return *ptr;
        }

        inline RealProperty& Property::AsReal()
        {
            auto ptr = boost::get<RealProperty>(&m_variant);
            if (!ptr)
            {
                throw PropertyTypeError("Not a RealProperty");
            }
            return *ptr;
        }

        inline const RealProperty& Property::AsReal() const
        {
            auto ptr = boost::get<RealProperty>(&m_variant);
            if (!ptr)
            {
                throw PropertyTypeError("Not a RealProperty");
            }
            return *ptr;
        }

        inline StringProperty& Property::AsString()
        {
            auto ptr = boost::get<StringProperty>(&m_variant);
            if (!ptr)
            {
                throw PropertyTypeError("Not a StringProperty");
            }
            return *ptr;
        }

        inline const StringProperty& Property::AsString() const
        {
            auto ptr = boost::get<StringProperty>(&m_variant);
            if (!ptr)
            {
                throw PropertyTypeError("Not a StringProperty");
            }
            return *ptr;
        }

        inline CollectionProperty& Property::AsCollection()
        {
            auto ptr = boost::get<CollectionProperty>(&m_variant);
            if (!ptr)
            {
                throw PropertyTypeError("Not a CollectionProperty");
            }
            return *ptr;
        }

        inline const CollectionProperty& Property::AsCollection() const
        {
            auto ptr = boost::get<CollectionProperty>(&m_variant);
            if (!ptr)
            {
                throw PropertyTypeError("Not a CollectionProperty");
            }
            return *ptr;
        }

        inline DictionaryProperty& Property::AsDictionary()
        {
            auto ptr = boost::get<DictionaryProperty>(&m_variant);
            if (!ptr)
            {
                throw PropertyTypeError("Not a DictionaryProperty");
            }
            return *ptr;
        }

        inline const DictionaryProperty& Property::AsDictionary() const
        {
            auto ptr = boost::get<DictionaryProperty>(&m_variant);
            if (!ptr)
            {
                throw PropertyTypeError("Not a DictionaryProperty");
            }
            return *ptr;
        }

        inline ObjectProperty& Property::AsObject()
        {
            auto ptr = boost::get<ObjectProperty>(&m_variant);
            if (!ptr)
            {
                throw PropertyTypeError("Not an ObjectProperty");
            }
            return *ptr;
        }

        inline const ObjectProperty& Property::AsObject() const
        {
            auto ptr = boost::get<ObjectProperty>(&m_variant);
            if (!ptr)
            {
                throw PropertyTypeError("Not an ObjectProperty");
            }
            return *ptr;
        }

        inline PropertyType Property::Type() const
        {
            return static_cast<PropertyType>(m_variant.which());
        }

        inline bool Property::Empty() const
        {
            return m_variant.which() == 0;
        }
    }   //  namespace common
}   //  namespace spire

#endif  //  SPIRE_COMMON_PROPERTY_INL
