////////////////////////////////////////////////////////////////////////////////
//  Copyright (C) 2012 Robert Engeln (engeln@gmail.com)
//  See accompanying LICENSE file for full license information.
////////////////////////////////////////////////////////////////////////////////
/// @file spire/common/enum_property.inl 
/// Inline functions for EnumProperty.
/// @addtogroup common
/// @{

#ifndef SPIRE_COMMON_ENUM_PROPERTY_INL
#define SPIRE_COMMON_ENUM_PROPERTY_INL

namespace spire
{
    namespace common
    {
        inline EnumProperty::EnumProperty(const EnumProperty& cpy)
        : m_proxy(cpy.m_proxy->Clone(m_storage, sizeof(m_storage)))
        {
        }

        inline EnumProperty::EnumProperty(const EnumPropertyProxy& proxy)
        : m_proxy(proxy.Clone(m_storage, sizeof(m_storage)))
        {
        }

        inline EnumProperty::~EnumProperty()
        {
            if (m_proxy == reinterpret_cast<EnumPropertyProxy*>(m_storage))
            {
                m_proxy->~EnumPropertyProxy();
            }
            else
            {
                delete m_proxy;
            }
        }

        inline int EnumProperty::Get() const
        {
            return m_proxy->Get();
        }

        inline const char* EnumProperty::GetString() const
        {
            return m_proxy->GetString();
        }

        inline EnumProperty& EnumProperty::Set(int v)
        {
            m_proxy->Set(v);
            return *this;
        }

        inline EnumProperty& EnumProperty::Set(const char* str)
        {
            m_proxy->Set(str);
            return *this;
        }

#define PROXY_CLASS    \
        PropertyProxy<T, typename boost::enable_if<boost::is_same<typename PropertyTraits<T, void>::PropertyType,  \
                                                                  EnumProperty>>::type>

        template <typename T>
        inline EnumProperty PROXY_CLASS::ToProperty(ReferenceType ref)
        {
            return EnumProperty(ThisType(ref));
        }

        template <typename T>
        inline PROXY_CLASS::PropertyProxy(ReferenceType ref)
        : m_ref(ref)
        {
        }

        template <typename T>
        inline PROXY_CLASS::PropertyProxy(const ThisType& cpy)
        : m_ref(cpy.m_ref)
        {
        }

        template <typename T>
        inline int PROXY_CLASS::Get() const
        {
            return PropertyTraits<T, void>::Get(m_ref);
        }

        template <typename T>
        inline const char* PROXY_CLASS::GetString() const
        {
            return PropertyTraits<T, void>::GetString(m_ref);
        }

        template <typename T>
        inline void PROXY_CLASS::Set(int v)
        {
            PropertyTraits<T, void>::Set(m_ref, v);
        }

        template <typename T>
        inline void PROXY_CLASS::Set(const char* str)
        {
            PropertyTraits<T, void>::Set(m_ref, str);
        }

        template <typename T>
        inline EnumPropertyProxy* PROXY_CLASS::Clone(void* ptr, size_t len) const
        {
            if (len >= sizeof(*this))
            {
                return new (ptr) ThisType(*this);
            }
            else
            {
                return new ThisType(*this);
            }
        }
#undef PROXY_CLASS
    }   //  namespace common
}   //  namespace spire

#endif  //  SPIRE_COMMON_ENUM_PROPERTY_INL


