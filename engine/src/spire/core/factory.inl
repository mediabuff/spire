////////////////////////////////////////////////////////////////////////////////
//  Copyright (C) 2012 Robert Engeln (engeln@gmail.com) All rights reserved.
//  See accompanying LICENSE file for full license information.
////////////////////////////////////////////////////////////////////////////////
///
/// @file spire/core/factory.inl
/// Inline functions for AutoRegisterFactory.
/// @addtogroup core
/// @{

#ifndef SPIRE_CORE_FACTORY_INL
#define SPIRE_CORE_FACTORY_INL

#include "spire/core/framework.hpp"

namespace spire
{
    namespace core
    {
        template <typename T>
        inline AutoRegisterFactory<T>::AutoRegisterFactory(const char* name)
        {
            assert(name);
            GetFramework().Register(std::unique_ptr<T>(new T()), name);
        }
    }   //  namespace core
}   //  namespace spire

#endif  //  SPIRE_CORE_FACTORY_INL


