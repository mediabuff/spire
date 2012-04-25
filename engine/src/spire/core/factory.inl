////////////////////////////////////////////////////////////////////////////////
//  Copyright (C) 2012 Robert Engeln (engeln@gmail.com) All rights reserved.
//  See accompanying LICENSE file for full license information.
////////////////////////////////////////////////////////////////////////////////
///
/// @file spire/core/factory.inl
/// Inline functions for the BasicFactory class.
/// @addtogroup core
/// @{

#ifndef SPIRE_CORE_FACTORY_INL
#define SPIRE_CORE_FACTORY_INL

#include "spire/core/factory_service.hpp"

namespace spire
{
    namespace core
    {
        template <typename T, typename I>
        std::unique_ptr<I> BasicFactory<T, I>::Clone() const
        {
            return new T(static_cast<const T*>(this));
        }

        template <typename T, typename I>
        const char* BasicFactory<T, I>::GetInterfaceType() const
        {
            return typeid(I).name();
        }
    }   //  namespace core
}   //  namespace core

#endif  //  SPIRE_CORE_FACTORY_INL

