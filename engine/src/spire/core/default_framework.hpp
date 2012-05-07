////////////////////////////////////////////////////////////////////////////////
//  Copyright (C) 2012 Robert Engeln (engeln@gmail.com) All rights reserved.
//  See accompanying LICENSE file for full license information.
////////////////////////////////////////////////////////////////////////////////
///
/// @file spire/core/default_framework.hpp
/// Defines the DefaultFramework class.
/// @addtogroup core
/// @{

#ifndef SPIRE_CORE_DEFAULT_FRAMEWORK_HPP
#define SPIRE_CORE_DEFAULT_FRAMEWORK_HPP

#include "spire/core/framework.hpp"

namespace spire
{
    namespace core
    {
        ///
        /// Default Framework implementation.
        ///
        class DefaultFramework : public Framework
        {
        public:
            ///
            /// Constructor.
            ///
            DefaultFramework();
            
            ///
            /// Destructor.
            ///
            virtual ~DefaultFramework();

            ///
            /// Inherited from Framework.
            /// @{
            virtual void Attach(std::unique_ptr<Service> svc);
            virtual void RegisterService(std::string type, Service* svc);
            virtual Service& AcquireService(const std::string& type);
            virtual Factory& AcquireFactory(const std::string& name);
            virtual void Register(std::unique_ptr<Factory> factory, std::string name);
            virtual void LoadModule(const char* name);
            //! @}

        private:
            std::vector<std::unique_ptr<Service>> m_servicePtrs;
            std::map<std::string, Service*> m_serviceMap;
            std::map<std::string, std::unique_ptr<Factory>> m_factoryMap;
        };
    }
}

#endif  //  SPIRE_CORE_DEFAULT_FRAMEWORK_HPP
