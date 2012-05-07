////////////////////////////////////////////////////////////////////////////////
//  Copyright (C) 2012 Robert Engeln (engeln@gmail.com)
//  See accompanying LICENSE file for full license information.
////////////////////////////////////////////////////////////////////////////////
/// @file spire/common/object_property.hpp 
/// Defines the ObjectProperty class.
/// @addtogroup common
/// @{

#ifndef SPIRE_COMMON_OBJECT_PROPERTY_HPP
#define SPIRE_COMMON_OBJECT_PROPERTY_HPP

namespace spire
{
    namespace common
    {
        class Property;
        class ObjectPropertyProxy;
        template <typename T, typename Enabler> class PropertyProxy;
        template <typename T, typename Enabler> class PropertyTraits;

        ///
        /// Encapsulates a key-value store corresponding to a class or struct.
        ///
        class ObjectProperty
        {
        public:
            //
            //  Copy constructor.
            //
            ObjectProperty(const ObjectProperty&);

            //
            //  Construct from a proxy object.
            //
            ObjectProperty(const ObjectPropertyProxy&);

            //
            //  Destructor.
            //
            ~ObjectProperty();

            //
            //  Gets a field.
            //
            Property Get(const std::string& key);

            //
            //  Enumerates through the class's fields.
            //
            template <typename T>
            void Enumerate(T visitor);

        private:
            ObjectPropertyProxy* m_proxy;
            char m_storage[16];
        };

        //
        //  Functor for enumerating through an object property.
        //
        class ObjectPropertyEnumerator
        {
        public:
            virtual bool operator()(const std::string& key, Property p) = 0;
        };

        //
        //  Interface for Object property proxy objects.
        //
        class ObjectPropertyProxy
        {
        public:
            virtual Property Get(const std::string& key) = 0;
            virtual void Enumerate(ObjectPropertyEnumerator& visitor) = 0;
            virtual ObjectPropertyProxy* Clone(void* ptr, size_t len) const = 0;
        };

        template <typename T>
        class PropertyProxy<T, typename boost::enable_if<boost::is_same<typename PropertyTraits<T, void>::PropertyType, ObjectProperty>>::type> 
            : public ObjectPropertyProxy
        {
        public:
            typedef typename boost::enable_if<boost::is_same<typename PropertyTraits<T, void>::PropertyType, ObjectProperty>>::type Enabler;
            typedef PropertyProxy<T, Enabler> ThisType;
            typedef typename PropertyTraits<T, void>::ReferenceType ReferenceType;

            static ObjectProperty ToProperty(ReferenceType ref);

            PropertyProxy(ReferenceType ref);
            PropertyProxy(const ThisType& cpy);
            virtual Property Get(const std::string& key);
            virtual void Enumerate(ObjectPropertyEnumerator& visitor);
            virtual ObjectPropertyProxy* Clone(void* ptr, size_t len) const;

        private:
            ReferenceType m_ref;
        };

    }   //  namespace common
}   //  namespace spire

#endif  //  SPIRE_COMMON_OBJECT_PROPERTY_HPP
