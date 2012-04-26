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
            /// Returns the prototype interface type name.
            ///
            /// This is equivalent to typeid(T).name(), where T is the
            /// specialization of BlueprintInterface.
            ///
            virtual const char* GetInterfaceType() const = 0;

            ///
            /// Clones the prototype.
            ///
            virtual std::unique_ptr<Blueprint> Clone() const = 0;
        };

        //
        //  Helper class for implementing BlueprintInterface with a zero parameter
        //  function signature.
        //
        template <typename F, size_t Arity>
        class BlueprintInterfaceHelper
        {
            static_assert(Arity >= 4, "Signatures with more than 4 parameters are not supported.");
        };

        template <typename F>
        class BlueprintInterfaceHelper<F, 0> : public Blueprint
        {
        public:
            typedef typename boost::function_types::result_type<F>::type ResultType;

            virtual ResultType operator()() const = 0;
        };

        template <typename F>
        class BlueprintInterfaceHelper<F, 1> : public Blueprint
        {
        public:
            typedef typename boost::function_types::result_type<F>::type ResultType;
            typedef typename boost::mpl::at_c<typename boost::function_types::parameter_types<F>, 0>::type Arg1Type;

            virtual ResultType operator()(Arg1Type) const = 0;
        };

        template <typename F>
        class BlueprintInterfaceHelper<F, 2> : public Blueprint
        {
        public:
            typedef typename boost::function_types::result_type<F>::type ResultType;
            typedef typename boost::mpl::at_c<typename boost::function_types::parameter_types<F>, 0>::type Arg1Type;
            typedef typename boost::mpl::at_c<typename boost::function_types::parameter_types<F>, 1>::type Arg2Type;

            virtual ResultType operator()(Arg1Type, Arg2Type) const = 0;
        };

        template <typename F>
        class BlueprintInterfaceHelper<F, 3> : public Blueprint
        {
        public:
            typedef typename boost::function_types::result_type<F>::type ResultType;
            typedef typename boost::mpl::at_c<typename boost::function_types::parameter_types<F>, 0>::type Arg1Type;
            typedef typename boost::mpl::at_c<typename boost::function_types::parameter_types<F>, 1>::type Arg2Type;
            typedef typename boost::mpl::at_c<typename boost::function_types::parameter_types<F>, 2>::type Arg3Type;

            virtual ResultType operator()(Arg1Type, Arg2Type, Arg3Type) const = 0;
        };

        template <typename F>
        class BlueprintInterfaceHelper<F, 4> : public Blueprint
        {
        public:
            typedef typename boost::function_types::result_type<F>::type ResultType;
            typedef typename boost::mpl::at_c<typename boost::function_types::parameter_types<F>,0>::type Arg1Type;
            typedef typename boost::mpl::at_c<typename boost::function_types::parameter_types<F>,1>::type Arg2Type;
            typedef typename boost::mpl::at_c<typename boost::function_types::parameter_types<F>,2>::type Arg3Type;
            typedef typename boost::mpl::at_c<typename boost::function_types::parameter_types<F>,3>::type Arg4Type;

            virtual ResultType operator()(Arg1Type, Arg2Type, Arg3Type, Arg4Type) const = 0;
        };

        ///
        /// Interface for a Blueprint which produces objects of a given type.
        ///
        /// @tparam F Function signature for the Construct method.
        ///
        template <typename F>
        class BlueprintInterface : public BlueprintInterfaceHelper<F, boost::function_types::function_arity<F>::value>
        {
        };

        ///
        /// Mixin for implementing Blueprint classes.
        ///
        /// @tparam T Inheriting type.
        /// @tparam I BlueprintInterface specialization to inherit from.
        ///
        template <typename T, typename I>
        class BasicBlueprint : public I
        {
        public:
            ///
            /// From Blueprint.
            ///
            virtual const char* GetInterfaceType() const;
            virtual std::unique_ptr<Blueprint> Clone() const;
        };
    }   //  namespace spire
    using core::Blueprint;
    using core::BlueprintInterface;
    using core::BasicBlueprint;
}   //  namespace spire

#endif  //  SPIRE_CORE_BLUEPRINT_HPP

