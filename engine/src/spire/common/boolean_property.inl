////////////////////////////////////////////////////////////////////////////////
//  Copyright (C) 2012 Robert Engeln (engeln@gmail.com)
//  See accompanying LICENSE file for full license information.
////////////////////////////////////////////////////////////////////////////////

#ifndef SPIRE_COMMON_BOOLEAN_PROPERTY_INL
#define SPIRE_COMMON_BOOLEAN_PROPERTY_INL

namespace spire
{
    namespace common
    {
        inline BooleanProperty::BooleanProperty(const BooleanProperty& cpy)
        : m_proxy(cpy.m_proxy->Clone(m_storage, sizeof(m_storage)))
        {
        }

        inline BooleanProperty::BooleanProperty(const BooleanPropertyProxy& proxy)
        : m_proxy(proxy.Clone(m_storage, sizeof(m_storage)))
        {
        }

        inline BooleanProperty::~BooleanProperty()
        {
            if (m_proxy == reinterpret_cast<BooleanPropertyProxy*>(m_storage))
            {
                m_proxy->~BooleanPropertyProxy();
            }
            else
            {
                delete m_proxy;
            }
        }

        inline bool BooleanProperty::Get() const
        {
            return m_proxy->Get();
        }

        inline BooleanProperty& BooleanProperty::Set(bool v)
        {
            m_proxy->Set(v);
            return *this;
        }

#define PROXY_CLASS    \
        PropertyProxy<T, typename boost::enable_if<boost::is_same<typename PropertyTraits<T, void>::PropertyType,  \
                                                                  BooleanProperty>>::type>

        template <typename T>
        inline BooleanProperty PROXY_CLASS::ToProperty(ReferenceType ref)
        {
            return BooleanProperty(ThisType(ref));
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
        inline bool PROXY_CLASS::Get() const
        {
            return PropertyTraits<T, void>::Get(m_ref);
        }

        template <typename T>
        inline void PROXY_CLASS::Set(bool v)
        {
            PropertyTraits<T, void>::Set(m_ref, v);
        }

        template <typename T>
        inline BooleanPropertyProxy* PROXY_CLASS::Clone(void* ptr, size_t len) const
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

#endif  //  SPIRE_COMMON_BOOLEAN_PROPERTY_INL
