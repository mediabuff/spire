////////////////////////////////////////////////////////////////////////////////
//  Copyright (C) 2012 Robert Engeln (engeln@gmail.com) All rights reserved.
//  See accompanying LICENSE file for full license information.
////////////////////////////////////////////////////////////////////////////////
///
/// @file spire/core/service.hpp
/// Defines the Service interface and BasicService class.
/// @addtogroup core
/// @{

#ifndef SPIRE_CORE_SERVICE_HPP
#define SPIRE_CORE_SERVICE_HPP

namespace spire
{
    namespace core
    {
        class Framework;

        ///
        /// Interface for a Service class.
        ///
        /// Services may be registered with the Framework class, allowing them
        /// to be accessed globally. 
        ///
        class Service : public boost::noncopyable
        {
        public:
            ///
            /// Destructor.
            ///
            virtual ~Service() = 0 { };
        };

        ///
        /// Mixin implementation for the Service interface.
        ///
        /// @tparam T Service type.
        /// 
        template <typename T>
        class BasicService : public T
        {
        public:
            ///
            /// Destructor.
            ///
            /// Automatically unregisters the service with the framework.
            ///
            virtual ~BasicService();

        protected:
            ///
            /// Constructor.
            ///
            /// Automatically registers the service with the framework.
            ///
            BasicService();
        };
    }   //  namespace core
    using core::Service;
    using core::BasicService;
}   //  namespace spire

#include "service.inl"

#endif  //  SPIRE_CORE_SERVICE_HPP
