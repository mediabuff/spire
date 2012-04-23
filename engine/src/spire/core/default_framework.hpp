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
            virtual void RegisterUntyped(std::string type, Service* svc);
            virtual Service& AcquireUntyped(std::string type);
            //! @}

        private:
            std::vector<std::unique_ptr<Service>> m_servicePtrs;
            std::map<std::string, Service*> m_serviceMap;
        };
    }
}

#endif  //  SPIRE_CORE_DEFAULT_FRAMEWORK_HPP
