////////////////////////////////////////////////////////////////////////////////
//  Copyright (C) 2012 Robert Engeln (engeln@gmail.com) All rights reserved.
//  See accompanying LICENSE file for full license information.
////////////////////////////////////////////////////////////////////////////////
///
/// @file spire/core/defaultfactory_service.hpp
/// Defines the DefaultFactoryService class.
/// @addtogroup core
/// @{

#ifndef SPIRE_CORE_DEFAULT_FACTORY_SERVICE_HPP
#define SPIRE_CORE_DEFAULT_FACTORY_SERVICE_HPP

#include "spire/core/factory_service.hpp"

namespace spire
{
    namespace core
    {
        ///
        /// Default implementation for FactoryService.
        ///
        class DefaultFactoryService : public FactoryService
        {
        public:
            ///
            /// Constructor.
            ///
            DefaultFactoryService();

            ///
            /// Destructor.
            ///
            virtual ~DefaultFactoryService();

            ///
            /// From FactoryService.
            /// @{

        };
    }
}

#endif  //  SPIRE_CORE_DEFAULT_FACTORY_SERVICE_HPP
