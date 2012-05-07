////////////////////////////////////////////////////////////////////////////////
//  Copyright (C) 2012 Robert Engeln (engeln@gmail.com)
//  See accompanying LICENSE file for full license information.
////////////////////////////////////////////////////////////////////////////////
/// @file spire/common/string_property.hpp 
/// Defines the StringProperty class.
/// @addtogroup common
/// @{

#ifndef SPIRE_COMMON_STRING_PROPERTY_HPP
#define SPIRE_COMMON_STRING_PROPERTY_HPP

namespace spire
{
    namespace common
    {
        class Property;
        class StringPropertyProxy;
        template <typename T, typename Enabler> class PropertyProxy;
        template <typename T, typename Enabler> class PropertyTraits;

        ///
        /// Encapsulates a C or STL string as a property.
        ///
        class StringProperty
        {
        public:
            //
            //  Copy constructor.
            //
            StringProperty(const StringProperty&);

            //
            //  Construct from a proxy object.
            //
            StringProperty(const StringPropertyProxy&);

            //
            //  Destructor.
            //
            ~StringProperty();

            //
            //  Gets the value as a c-style char array.
            //
            const char* Get() const;

            //
            //  Sets the value.
            //
            StringProperty& Set(const char*);
            StringProperty& Set(const std::string&);

        private:
            StringPropertyProxy* m_proxy;
            char m_storage[16];
        };

        //
        //  Internal interface for a string property proxy object.
        //
        class StringPropertyProxy
        {
        public:
            virtual const char* Get() const = 0;
            virtual void Set(const char*) = 0;
            virtual StringPropertyProxy* Clone(void* ptr, size_t len) const = 0;
        };

        //
        //  Specialization of PropertyProxy for string properties.
        //
        template <typename T>
        class PropertyProxy<T, typename boost::enable_if<boost::is_same<typename PropertyTraits<T, void>::PropertyType, StringProperty>>::type>
            : public StringPropertyProxy
        {
        public:
            typedef typename boost::enable_if<boost::is_same<typename PropertyTraits<T, void>::PropertyType, StringProperty>>::type Enabler;
            typedef PropertyProxy<T, Enabler> ThisType;
            typedef typename PropertyTraits<T, void>::ReferenceType ReferenceType;

            static StringProperty ToProperty(ReferenceType ref);

            PropertyProxy(ReferenceType);
            PropertyProxy(const ThisType&);
            virtual const char* Get() const;
            virtual void Set(const char*);
            virtual StringPropertyProxy* Clone(void* ptr, size_t len) const;

        private:
            ReferenceType m_ref;
        };
    }   //  namespace common
}   //  namespace spire

#endif  //  SPIRE_COMMON_STRING_PROPERTY_HPP
