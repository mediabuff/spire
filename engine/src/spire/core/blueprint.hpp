////////////////////////////////////////////////////////////////////////////////
//  Copyright (C) 2012 Robert Engeln (engeln@gmail.com) All rights reserved.
//  See accompanying LICENSE file for full license information.
////////////////////////////////////////////////////////////////////////////////
///
/// @file spire/core/blueprint.hpp
/// Defines the Blueprint and BlueprintInterface classes.
/// @addtogroup core
/// @{

#ifndef SPIRE_CORE_BLUEPRINT_HPP
#define SPIRE_CORE_BLUEPRINT_HPP

#include "spire/common/property.hpp"

namespace spire
{
    namespace core
    {
        ///
        /// Base class for Blueprint classes.
        ///
        class Blueprint : public PropertyHost
        {
        public:
            ///
            /// Destructor.
            ///
            virtual ~Blueprint() = 0 { };

            ///
            /// Returns the name of the type the blueprint is for.
            ///
            virtual const char* GetType() const = 0;

            ///
            /// Clones the blueprint.
            ///
            virtual std::unique_ptr<Blueprint> Clone() const = 0;
        };

        ///
        /// Interface for Blueprint implementations.
        ///
        template <typename T>
        class BlueprintInterface : public Blueprint
        {
        public:
            ///
            /// Constructs an object from the blueprint.
            ///
            virtual std::unique_ptr<T> Construct() const = 0;
        };

        ///
        /// Mixin for implementing Blueprint classes.
        ///
        /// @tparam C Inheriting type.
        /// @tparam T Concrete type constructed by this blueprint.
        ///
        template <typename C, typename T>
        class BasicBlueprint : public BlueprintInterface<T>
        {
        public:
            ///
            /// From Blueprint.
            ///
            /// @{
            virtual const char* GetType() const;
            virtual std::unique_ptr<Blueprint> Clone() const;
            //! @}
        };
    }   //  namespace spire
    using core::Blueprint;
    using core::BasicBlueprint;
}   //  namespace spire

#include "blueprint.inl"

#endif  //  SPIRE_CORE_BLUEPRINT_HPP

