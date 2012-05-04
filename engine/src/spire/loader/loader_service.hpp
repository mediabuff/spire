////////////////////////////////////////////////////////////////////////////////
//  Copyright (C) 2012 Robert Engeln (engeln@gmail.com)
//  See accompanying LICENSE file for full license information.
////////////////////////////////////////////////////////////////////////////////
///
/// @file spire/loader/loader_service.hpp
/// Defines the LoaderService class.
/// @addtogroup loader
/// @{

#ifndef SPIRE_LOADER_LOADER_SERVICE_HPP
#define SPIRE_LOADER_LOADER_SERVICE_HPP

#include "spire/core/service.hpp"

namespace spire
{
    namespace loader
    {
        ///
        /// Manages the virtual filesystem.
        ///
        class LoaderService : public Service
        {
        public:
            ///
            /// Destructor.
            ///
            virtual ~LoaderService() = 0;
        };
    }   //  namespace loader
    using loader::LoaderService;
}   //  namespace spire

#endif  //  SPIRE_LOADER_LOADER_SERVICE_HPP
