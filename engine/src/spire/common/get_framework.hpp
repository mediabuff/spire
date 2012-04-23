////////////////////////////////////////////////////////////////////////////////
//  Copyright (C) 2012 Robert Engeln (engeln@gmail.com) All rights reserved.
//  See accompanying LICENSE file for full license information.
////////////////////////////////////////////////////////////////////////////////
/// @file spire/common/get_framework.hpp
/// Prototype for the GetFramework function.
/// @addtogroup common
/// @{

#ifndef SPIRE_COMMON_GET_FRAMEWORK_HPP
#define SPIRE_COMMON_GET_FRAMEWORK_HPP

namespace spire
{
    namespace core
    {
        class Framework;
    }
}

namespace spire
{
    namespace common
    {
        ///
        /// Returns the singleton Framework instance.
        ///
        /// The Framework instance lives in spire_core.dll. The first time it is called,
        /// this function will load the DLL (or acquire a handle to it if already in
        /// memory) and call its GetCoreFrameworkInstance function to acquire a pointer
        /// to the Framework instance, which it will then cache for future calls.
        ///
        spire::core::Framework& GetFramework();
    } 
    using common::GetFramework;
} 

#endif  //  SPIRE_COMMON_GET_FRAMEWORK_HPP
