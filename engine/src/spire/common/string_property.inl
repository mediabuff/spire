////////////////////////////////////////////////////////////////////////////////
//  Copyright (C) 2012 Robert Engeln (engeln@gmail.com)
//  See accompanying LICENSE file for full license information.
////////////////////////////////////////////////////////////////////////////////

#ifndef SPIRE_COMMON_STRING_PROPERTY_INL
#define SPIRE_COMMON_STRING_PROPERTY_INL

namespace spire
{
    namespace common
    {
        inline StringProperty::StringProperty(const StringProperty& cpy)
        : m_proxy(cpy.m_proxy->Clone(m_storage, sizeof(m_storage)))
        {
        }

        inline StringProperty::StringProperty(const StringPropertyProxy& proxy)
        : m_proxy(proxy.Clone(m_storage, sizeof(m_storage)))
        {
        }

        inline StringProperty::~StringProperty()
        {
            if (m_proxy == reinterpret_cast<StringPropertyProxy*>(m_storage))
            {
                m_proxy->~StringPropertyProxy();
            }
            else
            {
                delete m_proxy;
            }
        }

        inline const char* StringProperty::Get() const
        {
            return m_proxy->Get();
        }

        inline StringProperty& StringProperty::Set(const char* str)
        {
            assert(str);
            m_proxy->Set(str);
            return *this;
        }

        inline StringProperty& StringProperty::Set(const std::string& str)
        {
            m_proxy->Set(str.c_str());
            return *this;
        }

#define PROXY_CLASS    \
        PropertyProxy<T, typename boost::enable_if<boost::is_same<typename PropertyTraits<T, void>::PropertyType,  \
                                                                  StringProperty>>::type>

        template <typename T>
        inline StringProperty PROXY_CLASS::ToProperty(ReferenceType ref)
        {
            return StringProperty(ThisType(ref));
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
        inline const char* PROXY_CLASS::Get() const
        {
            return PropertyTraits<T, void>::Get(m_ref);
        }

        template <typename T>
        inline void PROXY_CLASS::Set(const char* str)
        {
            PropertyTraits<T, void>::Set(m_ref, str);
        }

        template <typename T>
        inline StringPropertyProxy* PROXY_CLASS::Clone(void* ptr, size_t len) const
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

#endif  //  SPIRE_COMMON_STRING_PROPERTY_INL
