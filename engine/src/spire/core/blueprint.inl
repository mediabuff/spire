////////////////////////////////////////////////////////////////////////////////
//  Copyright (C) 2012 Robert Engeln (engeln@gmail.com) All rights reserved.
//  See accompanying LICENSE file for full license information.
////////////////////////////////////////////////////////////////////////////////
///
/// @file spire/core/blueprint.inl
/// Inline functions for the BasicBlueprint class.
/// @addtogroup core
/// @{

#ifndef SPIRE_CORE_BLUEPRINT_INL
#define SPIRE_CORE_BLUEPRINT_INL

namespace spire
{
    namespace core
    {
        template <typename T, typename I>
        std::unique_ptr<I> BasicBlueprint<T, I>::Clone() const
        {
            return new T(static_cast<const T*>(this));
        }

        template <typename T, typename I>
        const char* BasicBlueprint<T, I>::GetInterfaceType() const
        {
            return typeid(I).name();
        }
    }   //  namespace core
}   //  namespace core

#include "spire/core/blueprint.inl"

#endif  //  SPIRE_CORE_BLUEPRINT_INL

