////////////////////////////////////////////////////////////////////////////////
//  Copyright (C) 2012 Robert Engeln (engeln@gmail.com)
//  See accompanying LICENSE file for full license information.
////////////////////////////////////////////////////////////////////////////////
/// @file spire/common/property_traits.hpp 
/// Defines the PropertyTraits class.
/// @addtogroup common
/// @{

#ifndef SPIRE_COMMON_PROPERTY_TRAITS_HPP
#define SPIRE_COMMON_PROPERTY_TRAITS_HPP

namespace spire
{
    namespace common
    {
        ///
        /// Defines how a type can be wrapped by a Property.
        ///
        template <typename T, typename Enabler = void>
        class PropertyTraits
        {
        };
    }   //  namespace common
}   //  namespace spire

#endif  //  SPIRE_COMMON_PROPERTY_TRAITS_HPP
