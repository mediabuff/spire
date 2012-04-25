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
        /// Exception thrown when an attempt to acquire a factory fails
        /// because no factory matching the type and name was found.
        ///
        typedef Error<struct _FactoryNotFoundError, RuntimeError> FactoryNotFoundError;

        ///
        /// Manages the repository of Factory instances.
        ///
        class FactoryService : public Servce
        {
        public:
            ///
            /// Destructor.
            ///
            virtual ~FactoryService() = 0 { };

            ///
            /// Registers a factory prototype.
            ///
            /// @param name Name of the factory type.
            /// @param prototype Prototype factory instance.
            ///
            virtual void Register(std::string name,
                                  std::unique_ptr<Factory> prototype) = 0;

            ///
            /// Acquires a factory.
            ///
            /// @tparam Factory interface.
            /// @param name Name of the factory to acquire.
            ///
            template <typename T>
            T& Acquire(std::string name);

        protected:
            //
            //  Implementation for Acquire().
            //
            virtual Factory& Acquire(std::string type,
                                     std::string name) = 0;
        };
    }
}

#endif  //  SPIRE_CORE_FACTORY_SERVICE_HPP
