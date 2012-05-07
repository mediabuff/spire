////////////////////////////////////////////////////////////////////////////////
//  Copyright (C) 2012 Robert Engeln (engeln@gmail.com) All rights reserved.
//  See accompanying LICENSE file for full license information.
////////////////////////////////////////////////////////////////////////////////
///
/// @file spire/core/default_blueprint_service.hpp
/// Defines the DefaultBlueprintService class.
/// @addtogroup core
/// @{

#ifndef SPIRE_CORE_DEFAULT_BLUEPRINT_SERVICE_HPP
#define SPIRE_CORE_DEFAULT_BLUEPRINT_SERVICE_HPP

#include "spire/core/blueprint_service.hpp"

namespace spire
{
    namespace core
    {
        ///
        /// Default implementation for FactoryService.
        ///
        class DefaultBlueprintService : public BasicService<BlueprintService>
        {
        public:
            ///
            /// Constructor.
            ///
            DefaultBlueprintService();

            ///
            /// Destructor.
            ///
            virtual ~DefaultBlueprintService();

            ///
            /// From BlueprintService.
            /// @{
            virtual void Register(std::string name,
                                  std::unique_ptr<Blueprint> prototype);
            virtual const Blueprint& AcquireBlueprint(const std::string& type,
                                                      const std::string& name);
            virtual void Parse(std::vector<char> src);
            virtual const Blueprint& GetPrototype(const std::string& type);
            //! @}
        
        private:
            std::map<std::string, std::unique_ptr<Blueprint>> m_prototypeMap;
            std::map<std::string, 
                     std::map<std::string, 
                              std::unique_ptr<Blueprint>>> m_blueprintMap;
        };
    }
}

#endif  //  SPIRE_CORE_DEFAULT_BLUEPRINT_SERVICE_HPP
