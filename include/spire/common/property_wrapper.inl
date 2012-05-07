////////////////////////////////////////////////////////////////////////////////
//  Copyright (C) 2012 Robert Engeln (engeln@gmail.com)
//  See accompanying LICENSE file for full license information.
////////////////////////////////////////////////////////////////////////////////

#ifndef SPIRE_COMMON_PROPERTY_WRAPPER_INL
#define SPIRE_COMMON_PROPERTY_WRAPPER_INL

namespace spire
{
    namespace common
    {
        template <typename T, typename C, T (C::*G)(void) const, void (C::*S)(T)>
        PropertyWrapper<T, C, G, S>::PropertyWrapper(C& obj)
        : m_obj(obj)
        {
        }

        template <typename T, typename C, T (C::*G)(void) const, void (C::*S)(T)>
        T PropertyWrapper<T, C, G, S>::Get() const
        {
            return ((m_obj).*(G))();
        }

        template <typename T, typename C, T (C::*G)(void) const, void (C::*S)(T)>
        void PropertyWrapper<T, C, G, S>::Set(T v)
        {
            ((m_obj).*(S))(v);
        }
    }
}

#endif  //  SPIRE_COMMON_PROPERTY_WRAPPER_INL
