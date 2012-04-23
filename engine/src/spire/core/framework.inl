////////////////////////////////////////////////////////////////////////////////
//  Copyright (C) 2012 Robert Engeln (engeln@gmail.com) All rights reserved.
//  See accompanying LICENSE file for full license information.
////////////////////////////////////////////////////////////////////////////////
///
/// @file spire/core/framework.inl
/// Inline functions for the Framework class.
/// @addtogroup core
/// @{

#ifndef SPIRE_CORE_FRAMEWORK_INL
#define SPIRE_CORE_FRAMEWORK_INL

namespace spire
{
    namespace core
    {
        template <typename T>
        inline void Framework::Register(T* svcPtr)
        {
            RegisterUntyped(typeid(T).name(), svcPtr);
        }

        template <typename T>
        inline T& Framework::Acquire()
        {
            Service& typedSvc = AcquireUntyped(typeid(T).name());
            return dynamic_cast<T&>(typedSvc);
        }
    }
}

#endif  //  SPIRE_CORE_FRAMEWORK_INL

