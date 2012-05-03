////////////////////////////////////////////////////////////////////////////////
//  Copyright (C) 2012 Robert Engeln (engeln@gmail.com) All rights reserved.
//  See accompanying LICENSE file for full license information.
////////////////////////////////////////////////////////////////////////////////
///
/// @file spire/core/framework.hpp
/// Defines the Framework class.
/// @addtogroup core
/// @{

#ifndef SPIRE_CORE_FRAMEWORK_HPP
#define SPIRE_CORE_FRAMEWORK_HPP

#include "spire/common/exception.hpp"

namespace spire
{
    namespace core
    {
        class Factory;
        class Service;

        ///
        /// Exception thrown when an attempt to acquire a service fails
        /// because no service implementation was registered.
        /// 
        typedef Error<struct _ServiceNotFoundError, RuntimeError> ServiceNotFoundError;

        ///
        /// Exception thrown when an attempt is made to register more than
        /// one service instance under a single type.
        ///
        typedef Error<struct _ServiceAlreadyRegisteredError, RuntimeError> ServiceAlreadyRegisteredError;

        ///
        /// Exception thrown when an attempt to acquire a factory fails
        /// because no factory was registered under that name.
        ///
        typedef Error<struct _FactoryNotFoundError, RuntimeError> FactoryNotFoundError;

        ///
        /// Exception thrown when an attempt to acquire a factory fails
        /// because the requested factory interface is not supported by
        /// the factory under that particular name.
        ///
        typedef Error<struct _FactoryTypeError, RuntimeError> FactoryTypeError;

        ///
        /// Global service broker and facilitator.
        ///
        /// The Framework class is what connects the various modules together,
        /// allowing each piece of the engine access to the rest. Access to the
        /// singleton Framework instance is available via the GetFramework()
        /// function.
        ///
        class Framework : public boost::noncopyable
        {
        public:
            ///
            /// Acquires a service.
            ///
            /// @tparam T Service type to acquire.
            /// @throw ServiceNotFoundError No service of the requested type was
            ///                             registered.
            ///
            template <typename T>
            T& Acquire();

            ///
            /// Attaches a service to the framework.
            ///
            /// This causes the framework to take ownership of the service
            /// instance, which will persist until termination.
            ///
            /// @param svc Service instance to attach.
            ///
            virtual void Attach(std::unique_ptr<Service> svc) = 0;

            ///
            /// Registers a service.
            ///
            /// @tparam Service type; this corresponds to the type parameter of
            ///         the Acquire method.
            /// @param svc Pointer to the service instance. If null, any existing
            ///            service registered under the provided type will be
            ///            unregistered.   
            ///
            template <typename T>
            void Register(Service* svc);

            ///
            /// Acquires a factory.
            ///
            /// @tparam T Requested factory interface.
            /// @param name Name of the factory to acquire.
            ///
            template <typename T>
            T& Acquire(const std::string& name);

            ///
            /// Registers a factory.
            ///
            /// @param factory Factory instance. The framework will take ownership
            ///                of the factory. If null, any existing factory
            ///                registered under the given name will be unregistered.
            /// @param name Name to register the factory under.
            ///
            virtual void Register(std::unique_ptr<Factory> factory,
                                  std::string name) = 0;
            
        protected:
            ///
            /// Destructor.
            ///
            virtual ~Framework() = 0 { };

        private:
            virtual Factory& AcquireFactory(const std::string& name) = 0;
            virtual void RegisterService(std::string type, Service* svc) = 0;
            virtual Service& AcquireService(const std::string& type) = 0;
        };
    }   //  namespace core
    using core::Framework;
}   //  namespace spire

#include "framework.inl"

#endif  //  SPIRE_CORE_FRAMEWORK_HPP