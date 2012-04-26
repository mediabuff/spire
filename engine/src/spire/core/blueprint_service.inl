////////////////////////////////////////////////////////////////////////////////
//  Copyright (C) 2012 Robert Engeln (engeln@gmail.com) All rights reserved.
//  See accompanying LICENSE file for full license information.
////////////////////////////////////////////////////////////////////////////////
///
/// @file spire/core/blueprint_service.inl
/// Inline functions for BlueprintService.
/// @addtogroup core
/// @{

#ifndef SPIRE_CORE_BLUEPRINT_SERVICE_INL
#define SPIRE_CORE_BLUEPRINT_SERVICE_INL

namespace spire
{
    namespace core
    {
        template <typename T>
        inline T& BlueprintService::Acquire(std::string name)
        {
            return dynamic_cast<T&>(Acquire(typeid(T).name(), name));
        }
    }
}

#endif  //  SPIRE_CORE_BLUEPRINT_SERVICE_INL
