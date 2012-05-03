////////////////////////////////////////////////////////////////////////////////
//  Copyright (C) 2012 Robert Engeln (engeln@gmail.com) All rights reserved.
//  See accompanying LICENSE file for full license information.
////////////////////////////////////////////////////////////////////////////////
///
/// @file spire/core/blueprint_service.hpp
/// Defines the BlueprintService interface.
/// @addtogroup core
/// @{

#ifndef SPIRE_CORE_BLUEPRINT_SERVICE_HPP
#define SPIRE_CORE_BLUEPRINT_SERVICE_HPP

#include "spire/core/factory.hpp"
#include "spire/core/service.hpp"

namespace spire
{
    namespace core
    {
        class Blueprint;
        template <typename T> class BlueprintInterface;

        ///
        /// Exception thrown when an attempt to acquire a blueprint fails
        /// because no blueprint matching the type and name was found.
        ///
        typedef Error<struct _BlueprintNotFoundError, RuntimeError> BlueprintNotFoundError;

        ///
        /// Exception thrown when an attempt to acquire a blueprint prototype
        /// fails because no prototype was registered for the given type.
        ///
        typedef Error<struct _BlueprintPrototypeNotFoundError, RuntimeError> BlueprintPrototypeNotFoundError;

        ///
        /// Exception thrown when XML parsing fails.
        ///
        typedef Error<struct _BlueprintParsingError, DataError> BlueprintParsingError;

        ///
        /// Manages the repository of Blueprint instances.
        ///
        class BlueprintService : public Service
        {
        public:
            ///
            /// Destructor.
            ///
            virtual ~BlueprintService() = 0 { };

            ///
            /// Registers a blueprint prototype.
            ///
            /// The BlueprintService will take ownership of the prototype
            /// object. If a prototype has already been registered under the
            /// provided name, it will be replaced.
            ///
            /// @param type Name of the blueprint type.
            /// @param prototype Prototype blueprint instance. If null, any
            ///                  existing prototype with the given type
            ///                  will be destroyed.
            ///
            virtual void Register(std::string type,
                                  std::unique_ptr<Blueprint> prototype) = 0;

            ///
            /// Returns the prototype for a blueprint type.
            ///
            /// @param name Name of the blueprint type.
            ///
            virtual const Blueprint& GetPrototype(const std::string& type) = 0;

            ///
            /// Acquires a blueprint.
            ///
            /// @tparam T Type constructed by the blueprint.
            /// @param name Name of the blueprint to acquire.
            ///
            template <typename T>
            const BlueprintInterface<T>& Acquire(const std::string& name);

            ///
            /// Parses XML blueprint definitions.
            ///
            /// @param src XML source.
            /// @throw BlueprintParsingError An error occured while parsing.
            ///
            virtual void Parse(std::vector<char> src) = 0;

        protected:
            //
            //  Implementation for Acquire().
            //
            virtual const Blueprint& AcquireBlueprint(const std::string& type,
                                                      const std::string& name) = 0;
        };

        ///
        /// Factory interface for constructing BlueprintService instances.
        ///
        typedef FactoryInterface<std::unique_ptr<BlueprintService>()> BlueprintServiceFactory;
    }   //  namespace core
    using core::BlueprintService;
    using core::BlueprintServiceFactory;
}   //  namespace spire

#include "spire/core/blueprint_service.inl"

#endif  //  SPIRE_CORE_BLUEPRINT_SERVICE_HPP
