////////////////////////////////////////////////////////////////////////////////
//  Copyright (C) 2012 Robert Engeln (engeln@gmail.com)
//  See accompanying LICENSE file for full license information.
////////////////////////////////////////////////////////////////////////////////
/// @file spire/common/real_property.hpp 
/// Defines the RealProperty class.
/// @addtogroup common
/// @{

#ifndef SPIRE_COMMON_REAL_PROPERTY_HPP
#define SPIRE_COMMON_REAL_PROPERTY_HPP

namespace spire
{
    namespace common
    {
        class Property;
        class RealPropertyProxy;
        template <typename T, typename Enabler> class PropertyProxy;
        template <typename T, typename Enabler> class PropertyTraits;

        ///
        /// Encapsulates a float or double as a Property.
        ///
        class RealProperty
        {
        public:
            //
            //  Copy constructor.
            //
            RealProperty(const RealProperty&);

            //
            //  Construct from a proxy object.
            //
            RealProperty(const RealPropertyProxy&);

            //
            //  Destructor.
            //
            ~RealProperty();

            //
            //  Gets the value.
            //
            double Get() const;

            //
            //  Sets the value.
            //
            RealProperty& Set(double);

        private:
            RealPropertyProxy* m_proxy;
            char m_storage[16];
        };
        
        //
        //  Internal interface for a real property proxy object.
        //
        class RealPropertyProxy
        {
        public:
            virtual double Get() const = 0;
            virtual void Set(double) = 0;
            virtual RealPropertyProxy* Clone(void* ptr, size_t len) const = 0;
        };

        //
        //  Specialization of PropertyProxy for boolean properties.
        //
        template <typename T>
        class PropertyProxy<T, typename boost::enable_if<boost::is_same<typename PropertyTraits<T, void>::PropertyType, RealProperty>>::type>
            : public RealPropertyProxy
        {
        public:
            typedef typename boost::enable_if<boost::is_same<typename PropertyTraits<T, void>::PropertyType, RealProperty>>::type Enabler;
            typedef PropertyProxy<T, Enabler> ThisType;
            typedef typename PropertyTraits<T, void>::ReferenceType ReferenceType;

            static RealProperty ToProperty(ReferenceType ref);

            PropertyProxy(ReferenceType ref);
            PropertyProxy(const ThisType& cpy);
            virtual double Get() const;
            virtual void Set(double);
            virtual RealPropertyProxy* Clone(void* ptr, size_t len) const;

        private:
            ReferenceType m_ref;
        };
    }   //  namespace common
}   //  namespace spire

#endif  //  SPIRE_COMMON_REAL_PROPERTY_HPP
