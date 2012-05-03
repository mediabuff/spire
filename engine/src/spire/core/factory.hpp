////////////////////////////////////////////////////////////////////////////////
//  Copyright (C) 2012 Robert Engeln (engeln@gmail.com) All rights reserved.
//  See accompanying LICENSE file for full license information.
////////////////////////////////////////////////////////////////////////////////
///
/// @file spire/core/factory.hpp
/// Defines the Factory, FactoryInterface, and BasicFactory classes.
/// @addtogroup core
/// @{

#ifndef SPIRE_CORE_FACTORY_HPP
#define SPIRE_CORE_FACTORY_HPP

namespace spire
{
    namespace core
    {
        ///
        /// Base class for Factory classes.
        ///
        class Factory
        {
        public:
            ///
            /// Destructor.
            ///
            virtual ~Factory() = 0 { };
        };

        //
        //  Helper class for implementing FactoryInterface with a zero parameter
        //  function signature.
        //
        template <typename F, size_t Arity>
        class FactoryInterfaceHelper
        {
            static_assert(Arity >= 4, "Signatures with more than 4 parameters are not supported.");
        };

        template <typename F>
        class FactoryInterfaceHelper<F, 0> : public Factory
        {
        public:
            typedef typename boost::function_types::result_type<F>::type ResultType;

            virtual ResultType Construct() const = 0;
        };

        template <typename F>
        class FactoryInterfaceHelper<F, 1> : public Factory
        {
        public:
            typedef typename boost::function_types::result_type<F>::type ResultType;
            typedef typename boost::mpl::at_c<typename boost::function_types::parameter_types<F>, 0>::type Arg1Type;

            virtual ResultType Construct(Arg1Type) const = 0;
        };

        template <typename F>
        class FactoryInterfaceHelper<F, 2> : public Factory
        {
        public:
            typedef typename boost::function_types::result_type<F>::type ResultType;
            typedef typename boost::mpl::at_c<typename boost::function_types::parameter_types<F>, 0>::type Arg1Type;
            typedef typename boost::mpl::at_c<typename boost::function_types::parameter_types<F>, 1>::type Arg2Type;

            virtual ResultType Construct(Arg1Type, Arg2Type) const = 0;
        };

        template <typename F>
        class FactoryInterfaceHelper<F, 3> : public Factory
        {
        public:
            typedef typename boost::function_types::result_type<F>::type ResultType;
            typedef typename boost::mpl::at_c<typename boost::function_types::parameter_types<F>, 0>::type Arg1Type;
            typedef typename boost::mpl::at_c<typename boost::function_types::parameter_types<F>, 1>::type Arg2Type;
            typedef typename boost::mpl::at_c<typename boost::function_types::parameter_types<F>, 2>::type Arg3Type;

            virtual ResultType Construct(Arg1Type, Arg2Type, Arg3Type) const = 0;
        };

        template <typename F>
        class FactoryInterfaceHelper<F, 4> : public Factory
        {
        public:
            typedef typename boost::function_types::result_type<F>::type ResultType;
            typedef typename boost::mpl::at_c<typename boost::function_types::parameter_types<F>,0>::type Arg1Type;
            typedef typename boost::mpl::at_c<typename boost::function_types::parameter_types<F>,1>::type Arg2Type;
            typedef typename boost::mpl::at_c<typename boost::function_types::parameter_types<F>,2>::type Arg3Type;
            typedef typename boost::mpl::at_c<typename boost::function_types::parameter_types<F>,3>::type Arg4Type;

            virtual ResultType Construct(Arg1Type, Arg2Type, Arg3Type, Arg4Type) const = 0;
        };

        ///
        /// Interface for a Factory which produces objects of a given type.
        ///
        /// @tparam F Function signature for the Construct method.
        ///
        template <typename F>
        class FactoryInterface : public FactoryInterfaceHelper<F, boost::function_types::function_arity<F>::value>
        {
        public:
            typedef F SignatureType;
        };

        //
        //  Helper class for implementing BasicFactory.
        //
        template <typename T, typename I, size_t Arity>
        class BasicFactoryHelper
        {
            static_assert(Arity >= 4, "Signatures with more than 4 parameters are not supported.");
        };

        template <typename T, typename I>
        class BasicFactoryHelper<T, I, 0> : public I
        {
        public:
            typedef typename boost::function_types::result_type<typename I::SignatureType>::type ResultType;

            virtual ResultType Construct() const
            {
                return ResultType(new T());
            }
        };

        template <typename T, typename I>
        class BasicFactoryHelper<T, I, 1> : public I
        {
        public:
            typedef typename boost::function_types::result_type<typename I::SignatureType>::type ResultType;
            typedef typename boost::mpl::at_c<typename boost::function_types::parameter_types<typename I::SignatureType>, 0>::type Arg1Type;

            virtual ResultType Construct(Arg1Type arg1) const
            {
                return ResultType(new T(std::forward<Arg1Type>(arg1)));
            };
        };

        template <typename T, typename I>
        class BasicFactoryHelper<T, I, 2> : public I
        {
        public:
            typedef typename boost::function_types::result_type<typename I::SignatureType>::type ResultType;
            typedef typename boost::mpl::at_c<typename boost::function_types::parameter_types<typename I::SignatureType>, 0>::type Arg1Type;
            typedef typename boost::mpl::at_c<typename boost::function_types::parameter_types<typename I::SignatureType>, 1>::type Arg2Type;

            virtual ResultType Construct(Arg1Type arg1, Arg2Type arg2) const
            {
                return ResultType(new T(std::forward<Arg1Type>(arg1),
                                        std::forward<Arg2Type>(arg2)));
            }
        };

        template <typename T, typename I>
        class BasicFactoryHelper<T, I, 3> : public I
        {
        public:
            typedef typename boost::function_types::result_type<typename I::SignatureType>::type ResultType;
            typedef typename boost::mpl::at_c<typename boost::function_types::parameter_types<typename I::SignatureType>, 0>::type Arg1Type;
            typedef typename boost::mpl::at_c<typename boost::function_types::parameter_types<typename I::SignatureType>, 1>::type Arg2Type;
            typedef typename boost::mpl::at_c<typename boost::function_types::parameter_types<typename I::SignatureType>, 2>::type Arg3Type;

            virtual ResultType Construct(Arg1Type arg1, Arg2Type arg2, Arg3Type arg3) const
            {
                return ResultType(new T(std::forward<Arg1Type>(arg1),
                                        std::forward<Arg2Type>(arg2),
                                        std::forward<Arg3Type>(arg3)));
            }
        };

        template <typename T, typename I>
        class BasicFactoryHelper<T, I, 4> : public I
        {
        public:
            typedef typename boost::function_types::result_type<typename I::SignatureType>::type ResultType;
            typedef typename boost::mpl::at_c<typename boost::function_types::parameter_types<typename I::SignatureType>,0>::type Arg1Type;
            typedef typename boost::mpl::at_c<typename boost::function_types::parameter_types<typename I::SignatureType>,1>::type Arg2Type;
            typedef typename boost::mpl::at_c<typename boost::function_types::parameter_types<typename I::SignatureType>,2>::type Arg3Type;
            typedef typename boost::mpl::at_c<typename boost::function_types::parameter_types<typename I::SignatureType>,3>::type Arg4Type;

            virtual ResultType Construct(Arg1Type arg1, Arg2Type arg2, Arg3Type arg3, Arg4Type arg4) const
            {
                return ResultType(new T(std::forward<Arg1Type>(arg1),
                                        std::forward<Arg2Type>(arg2),
                                        std::forward<Arg3Type>(arg3),
                                        std::forward<Arg4Type>(arg4)));
            }
        };

        ///
        /// Basic Factory implementation.
        ///
        /// @tparam T Concrete type to construct.
        /// @tparam I FactoryInterface specialization to inherit from.
        ///
        template <typename T, typename I>
        class BasicFactory : public BasicFactoryHelper<T, I, boost::function_types::function_arity<typename I::SignatureType>::value>
        {
        };
    }   //  namespace core
    using core::Factory;
    using core::FactoryInterface;
    using core::BasicFactory;
}   //  namespace spire

#endif  //  SPIRE_CORE_FACTORY_HPP
