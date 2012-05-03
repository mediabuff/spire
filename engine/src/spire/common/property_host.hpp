////////////////////////////////////////////////////////////////////////////////
//  Copyright (C) 2012 Robert Engeln (engeln@gmail.com)
//  See accompanying LICENSE file for full license information.
////////////////////////////////////////////////////////////////////////////////
/// @file spire/common/property_host.hpp 
/// Defines the PropertyHost interface.
/// @addtogroup common
/// @{

#ifndef SPIRE_COMMON_PROPERTY_HOST_HPP
#define SPIRE_COMMON_PROPERTY_HOST_HPP

namespace spire
{
    namespace common
    {
        ///
        /// Interface for types which can be polymorphically encapsulated
        /// by an ObjectProperty.
        ///
        class PropertyHost
        {
        protected:
            template <typename T, typename Enabler> friend class spire::common::PropertyTraits;
            virtual void EnumerateProperties(ObjectPropertyEnumerator& e) = 0;
        };

        //  Workaround for a bug in VS2010 where decltype(*this) causes an ICE
        template <typename T>
        T& PtrToRef(T*);

#define BEGIN_HOST_PROPERTY_MAP(...) \
        template <typename T, typename Enabler> friend class spire::common::InheritProperties;            \
        void EnumeratePropertiesNonVirtual(spire::common::ObjectPropertyEnumerator& e)    \
        {                                                                               \
            typedef decltype(spire::common::PtrToRef(this)) _Self;               \
            _Self obj = *this; 
#define END_HOST_PROPERTY_MAP(...) \
        }                                                                               \
        virtual void EnumerateProperties(spire::common::ObjectPropertyEnumerator& e) \
        {                                                                           \
            EnumeratePropertiesNonVirtual(e);                                       \
        }
    }   //  namespace common
}   //  namespace spire

#endif  //  SPIRE_COMMON_PROPERTY_HOST_HPP
