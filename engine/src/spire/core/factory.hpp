////////////////////////////////////////////////////////////////////////////////
//  Copyright (C) 2012 Robert Engeln (engeln@gmail.com) All rights reserved.
//  See accompanying LICENSE file for full license information.
////////////////////////////////////////////////////////////////////////////////
///
/// @file spire/core/factory.hpp
/// Defines the Factory and BasicFactory classes.
/// @addtogroup core
/// @{

#ifndef SPIRE_CORE_FACTORY_HPP
#define SPIRE_CORE_FACTORY_HPP

#include "spire/common/property.hpp"

namespace spire
{
    namespace core
    {
        ///
        /// Base class for all factories.
        ///
        class Factory : public PropertyHost,
                        public boost::noncopyable
        {
        public:
            ///
            /// Destructor.
            ///
            virtual ~Factory() = 0 { };
        };

        //
        //  Helper class for implementing BasicFactory with a zero parameter
        //  function signature.
        //
        template <typename F, size_t Arity>
        class BasicFactoryHelper
        {
            static_assert(Arity >= 4, "Factory signatures with more than 4 parameters are not supported.");
        };

        template <typename F>
        class BasicFactoryHelper<F, 0> : public Factory
        {
        public:
            typedef typename boost::function_types::result_type<F>::type ResultType;

            virtual ResultType operator()() const = 0;
        };

        template <typename F>
        class BasicFactoryHelper<F, 1> : public Factory
        {
        public:
            typedef typename boost::function_types::result_type<F>::type ResultType;
            typedef typename boost::mpl::at_c<typename boost::function_types::parameter_types<F>, 0>::type Arg1Type;

            virtual ResultType operator()(Arg1Type) const = 0;
        };

        template <typename F>
        class BasicFactoryHelper<F, 2> : public Factory
        {
        public:
            typedef typename boost::function_types::result_type<F>::type ResultType;
            typedef typename boost::mpl::at_c<typename boost::function_types::parameter_types<F>, 0>::type Arg1Type;
            typedef typename boost::mpl::at_c<typename boost::function_types::parameter_types<F>, 1>::type Arg2Type;

            virtual ResultType operator()(Arg1Type, Arg2Type) const = 0;
        };

        template <typename F>
        class BasicFactoryHelper<F, 3> : public Factory
        {
        public:
            typedef typename boost::function_types::result_type<F>::type ResultType;
            typedef typename boost::mpl::at_c<typename boost::function_types::parameter_types<F>, 0>::type Arg1Type;
            typedef typename boost::mpl::at_c<typename boost::function_types::parameter_types<F>, 1>::type Arg2Type;
            typedef typename boost::mpl::at_c<typename boost::function_types::parameter_types<F>, 2>::type Arg3Type;

            virtual ResultType operator()(Arg1Type, Arg2Type, Arg3Type) const = 0;
        };

        template <typename F>
        class BasicFactoryHelper<F, 4> : public Factory
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
        /// Interface for a Factory which produces objects of a given type.
        ///
        /// @tparam F Function signature for the Construct method.
        ///
        template <typename F>
        class BasicFactory : public BasicFactoryHelper<F, boost::function_types::function_arity<F>::value>
        {
        };
    }
}

#endif  //  SPIRE_CORE_FACTORY_HPP

