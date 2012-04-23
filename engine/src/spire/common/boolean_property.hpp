////////////////////////////////////////////////////////////////////////////////
//  Copyright (C) 2012 Robert Engeln (engeln@gmail.com)
//  See accompanying LICENSE file for full license information.
////////////////////////////////////////////////////////////////////////////////
/// @file spire/common/boolean_property.hpp 
/// Defines the BooleanProperty class.
/// @addtogroup common
/// @{

#ifndef SPIRE_COMMON_BOOLEAN_PROPERTY_HPP
#define SPIRE_COMMON_BOOLEAN_PROPERTY_HPP

namespace spire
{
    namespace common
    {
        class Property;
        class BooleanPropertyProxy;
        template <typename T, typename Enabler> class PropertyProxy;
        template <typename T, typename Enabler> class PropertyTraits;

        ///
        ///  Property object encapsulating a boolean value.
        ///
        class BooleanProperty
        {
        public:
            //
            //  Copy constructor.
            //
            BooleanProperty(const BooleanProperty&);

            //
            //  Construct from a proxy object.
            //
            BooleanProperty(const BooleanPropertyProxy&);

            //
            //  Destructor.
            //
            ~BooleanProperty();

            //
            //  Gets the value.
            //
            bool Get() const;

            //
            //  Sets the value.
            //
            BooleanProperty& Set(bool);

        private:
            BooleanPropertyProxy* m_proxy;
            char m_storage[16];
        };

        //
        //  Internal interface for a boolean property proxy object.
        //
        class BooleanPropertyProxy
        {
        public:
            virtual bool Get() const = 0;
            virtual void Set(bool) = 0;
            virtual BooleanPropertyProxy* Clone(void* ptr, size_t len) const = 0;
        };
        
        //
        //  Proxy class for boolean properties.
        //
        template <typename T>
        class PropertyProxy<T, typename boost::enable_if<boost::is_same<typename PropertyTraits<T, void>::PropertyType, BooleanProperty>>::type>
            : public BooleanPropertyProxy
        {
        public:
            typedef typename boost::enable_if<boost::is_same<typename PropertyTraits<T, void>::PropertyType, BooleanProperty>>::type Enabler;
            typedef PropertyProxy<T, Enabler> ThisType;
            typedef typename PropertyTraits<T, void>::ReferenceType ReferenceType;

            static BooleanProperty ToProperty(ReferenceType ref);

            PropertyProxy(ReferenceType ref);
            PropertyProxy(const ThisType& cpy);
            virtual bool Get() const;
            virtual void Set(bool);
            virtual BooleanPropertyProxy* Clone(void* ptr, size_t len) const;

        private:
            ReferenceType m_ref;
        };
    }   //  namespace common
}   //  namespace spire

#endif  //  SPIRE_COMMON_BOOLEAN_PROPERTY_HPP
