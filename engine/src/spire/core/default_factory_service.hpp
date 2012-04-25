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
        class DefaultFactoryService : public BasicService<FactoryService>
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
            virtual void Register(std::string name,
                                  std::unique_ptr<Factory> prototype);
            virtual Factory& Acquire(std::string type,
                                     std::string name);
            //! @}
        
        private:
            std::map<std::string, std::unique_ptr<Factory>> m_factoryPrototypeMap;
            std::map<std::string, 
                     std::map<std::string, 
                              std::unique_ptr<Factory>>> m_factoryMap;
        };
    }
}

#endif  //  SPIRE_CORE_DEFAULT_FACTORY_SERVICE_HPP
