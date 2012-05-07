////////////////////////////////////////////////////////////////////////////////
//  Copyright (C) 2012 Robert Engeln (engeln@gmail.com)
//  See accompanying LICENSE file for full license information.
////////////////////////////////////////////////////////////////////////////////
/// @file spire/common/enum_property.hpp 
/// Defines the EnumProperty class.
/// @addtogroup common
/// @{

#ifndef SPIRE_COMMON_ENUM_PROPERTY_HPP
#define SPIRE_COMMON_ENUM_PROPERTY_HPP

namespace spire
{
    namespace common
    {
        class Property;
        class EnumPropertyProxy;
        template <typename T, typename Enabler> class PropertyProxy;
        template <typename T, typename Enabler> class PropertyTraits;

        ///
        ///  Property object encapsulating an enum value.
        ///
        class EnumProperty
        {
        public:
            //
            //  Copy constructor.
            //
            EnumProperty(const EnumProperty&);

            //
            //  Construct from a proxy object.
            //
            EnumProperty(const EnumPropertyProxy&);

            //
            //  Destructor.
            //
            ~EnumProperty();

            //
            //  Gets the integral value.
            //
            int Get() const;

            //
            //  Gets the string value.
            //
            const char* GetString() const;

            //
            //  Sets the integral value.
            //
            EnumProperty& Set(int);

            //
            //  Sets the value as a string.
            //
            EnumProperty& Set(const char*);

        private:
            EnumPropertyProxy* m_proxy;
            char m_storage[16];
        };

        //
        //  Internal interface for an enum property proxy object.
        //
        class EnumPropertyProxy
        {
        public:
            virtual int Get() const = 0;
            virtual const char* GetString() const = 0;
            virtual void Set(int) = 0;
            virtual void Set(const char*) = 0;
            virtual EnumPropertyProxy* Clone(void* ptr, size_t len) const = 0;
        };
        
        //
        //  Proxy class for boolean properties.
        //
        template <typename T>
        class PropertyProxy<T, typename boost::enable_if<boost::is_same<typename PropertyTraits<T, void>::PropertyType, EnumProperty>>::type>
            : public EnumPropertyProxy
        {
        public:
            typedef typename boost::enable_if<boost::is_same<typename PropertyTraits<T, void>::PropertyType, EnumProperty>>::type Enabler;
            typedef PropertyProxy<T, Enabler> ThisType;
            typedef typename PropertyTraits<T, void>::ReferenceType ReferenceType;

            static EnumProperty ToProperty(ReferenceType ref);

            PropertyProxy(ReferenceType ref);
            PropertyProxy(const ThisType& cpy);
            virtual int Get() const;
            virtual const char* GetString() const;
            virtual void Set(int);
            virtual void Set(const char*);
            virtual EnumPropertyProxy* Clone(void* ptr, size_t len) const;

        private:
            ReferenceType m_ref;
        };
    }   //  namespace common
}   //  namespace spire

#endif  //  SPIRE_COMMON_ENUM_PROPERTY_HPP
