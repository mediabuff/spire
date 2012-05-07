////////////////////////////////////////////////////////////////////////////////
//  Copyright (C) 2012 Robert Engeln (engeln@gmail.com) All rights reserved.
//  See accompanying LICENSE file for full license information.
////////////////////////////////////////////////////////////////////////////////
///
/// @file spire/core/service.hpp
/// Inline functions for Service and BasicService.
/// @addtogroup core
/// @{

#ifndef SPIRE_CORE_SERVICE_INL
#define SPIRE_CORE_SERVICE_INL

#include "spire/core/framework.hpp"

namespace spire
{
    namespace core
    {
        template <typename T>
        inline BasicService<T>::BasicService()
        {
            GetFramework().Register<T>(static_cast<T*>(this));
        }

        template <typename T>
        inline BasicService<T>::~BasicService()
        {
            GetFramework().Register<T>(static_cast<T*>(nullptr));
        }
    }
}

#endif  //  SPIRE_CORE_SERVICE_INL
