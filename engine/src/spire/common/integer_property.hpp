////////////////////////////////////////////////////////////////////////////////
//  Copyright (C) 2012 Robert Engeln (engeln@gmail.com)
//  See accompanying LICENSE file for full license information.
////////////////////////////////////////////////////////////////////////////////
/// @file spire/common/integer_property.hpp 
/// Defines the IntegerProperty class.
/// @addtogroup common
/// @{

#ifndef SPIRE_COMMON_INTEGER_PROPERTY_HPP
#define SPIRE_COMMON_INTEGER_PROPERTY_HPP

namespace spire
{
    namespace common
    {
        class Property;
        class IntegerPropertyProxy;
        template <typename T, typename Enabler> class PropertyProxy;
        template <typename T, typename Enabler> class PropertyTraits;

        ///
        /// Encapsulates an integral value.
        ///
        class IntegerProperty
        {
        public:
            //
            //  Copy constructor.
            //
            IntegerProperty(const IntegerProperty&);

            //
            //  Construct from a proxy object.
            //
            IntegerProperty(const IntegerPropertyProxy&);

            //
            //  Destructor.
            //
            ~IntegerProperty();

            //
            //  Gets the value.
            //
            int64_t Get() const;

            //
            //  Sets the value.
            //
            IntegerProperty& Set(int64_t);

        private:
            IntegerPropertyProxy* m_proxy;
            char m_storage[16];
        };

        //
        //  Internal interface for an integer property proxy object.
        //
        class IntegerPropertyProxy
        {
        public:
            virtual int64_t Get() const = 0;
            virtual void Set(int64_t) = 0;
            virtual IntegerPropertyProxy* Clone(void* ptr, size_t len) const = 0;
        };

        //
        //  Specialization of PropertyProxy for integer properties.
        //
        template <typename T>
        class PropertyProxy<T, typename boost::enable_if<boost::is_same<typename PropertyTraits<T, void>::PropertyType, IntegerProperty>>::type>
            : public IntegerPropertyProxy
        {
        public:
            typedef typename boost::enable_if<boost::is_same<typename PropertyTraits<T, void>::PropertyType, IntegerProperty>>::type Enabler;
            typedef PropertyProxy<T, Enabler> ThisType;
            typedef typename PropertyTraits<T, void>::ReferenceType ReferenceType;

            static IntegerProperty ToProperty(ReferenceType ref);

            PropertyProxy(ReferenceType ref);
            PropertyProxy(const ThisType& cpy);
            virtual int64_t Get() const;
            virtual void Set(int64_t);
            virtual IntegerPropertyProxy* Clone(void* ptr, size_t len) const;

        private:
            ReferenceType m_ref;
        };
    }
}

#endif  //  SPIRE_COMMON_INTEGER_PROPERTY_HPP
