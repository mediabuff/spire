////////////////////////////////////////////////////////////////////////////////
//  Copyright (C) 2012 Robert Engeln (engeln@gmail.com) All rights reserved.
//  See accompanying LICENSE file for full license information.
////////////////////////////////////////////////////////////////////////////////
///
/// @file spire/core/framework.hpp
/// Defines the Framework class.
///

#ifndef SPIRE_CORE_FRAMEWORK_HPP
#define SPIRE_CORE_FRAMEWORK_HPP

namespace spire
{
    namespace core
    {
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
            /// Destructor.
            /// 
            ~Framework();

        private:
            friend Framework& GetFrameworkInstance();

            /// @internal
            /// Constructor.
            ///
            Framework();
        };
    }   //  namespace core
    using core::Framework;
}   //  namespace spire

#endif  //  SPIRE_CORE_FRAMEWORK_HPP