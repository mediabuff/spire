////////////////////////////////////////////////////////////////////////////////
//  Copyright (C) 2012 Robert Engeln (engeln@gmail.com) All rights reserved.
//  See accompanying LICENSE file for full license information.
////////////////////////////////////////////////////////////////////////////////
///
/// @file spire/core/factory_service.hpp
/// Defines the FactoryServce interface.
/// @addtogroup core
/// @{

#ifndef SPIRE_CORE_FACTORY_SERVICE_HPP
#define SPIRE_CORE_FACTORY_SERVICE_HPP

namespace spire
{
    namespace core
    {
        class Factory;

        ///
        /// Manages the repository of Factory instances.
        ///
        class FactoryService
        {
        public:
            ///
            /// Destructor.
            ///
            virtual ~FactoryService() = 0 { };

            ///
            /// Registers a factory type.
            ///
            /// @param name Name of the factory type.
            /// @param generator Function which will instantiate factory objects.
            ///
            virtual void Register(std::string name,
                                  std::function<Factory*()> generator) = 0;

            ///
            /// Acquires a factory.
            ///
            /// @tparam Factory type (typically a specialization of BasicFactory.)
            /// @param name Name of the factory to acquire.
            ///
            template <typename T>
            T& Acquire(const std::string& name);

        protected:
            //
            //  Implementation for Acquire().
            //
            virtual Factory& Acquire(const std::string& type,
                                     const std::string& name) = 0;
        };
    }
}

#endif  //  SPIRE_CORE_FACTORY_SERVICE_HPP
