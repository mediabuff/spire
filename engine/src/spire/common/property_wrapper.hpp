////////////////////////////////////////////////////////////////////////////////
//  Copyright (C) 2012 Robert Engeln (engeln@gmail.com)
//  See accompanying LICENSE file for full license information.
////////////////////////////////////////////////////////////////////////////////
/// @file spire/common/property_wrapper.hpp 
/// Defines the PropertyWrapper class.
/// @addtogroup common
/// @{

#ifndef SPIRE_COMMON_PROPERTY_WRAPPER_HPP
#define SPIRE_COMMON_PROPERTY_WRAPPER_HPP

namespace spire
{
    namespace common
    {
        ///
        /// Enables a getter and setter functions to be encapsulated by a Property.
        ///
        /// @param T Type to get and set.
        /// @param C Host class.
        /// @param G Getter method.
        /// @param S Setter method.
        ///
        template <typename T, typename C, T (C::*G)(void) const, void (C::*S)(T)>
        class PropertyWrapper
        {
        public:
            typedef T ValueType;

            PropertyWrapper(C& obj);
            T Get() const;
            void Set(T);

        private:
            C& m_obj;
        };

    }   //  namespace common
}   //  namespace spire

#endif  //  SPIRE_COMMON_PROPERTY_VALIDATOR_HPP
