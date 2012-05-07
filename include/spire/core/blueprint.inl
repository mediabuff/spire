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
        template <typename C, typename T, typename I>
        std::unique_ptr<Blueprint> BasicBlueprint<C, T, I>::Clone() const
        {
            return std::unique_ptr<Blueprint>(new C(*static_cast<const C*>(this)));
        }

        template <typename C, typename T, typename I>
        const char* BasicBlueprint<C, T, typename I>::GetType() const
        {
            return typeid(T).name();
        }
    }   //  namespace core
}   //  namespace core

#include "spire/core/blueprint.inl"

#endif  //  SPIRE_CORE_BLUEPRINT_INL

