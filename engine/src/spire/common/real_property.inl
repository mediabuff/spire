////////////////////////////////////////////////////////////////////////////////
//  Copyright (C) 2012 Robert Engeln (engeln@gmail.com)
//  See accompanying LICENSE file for full license information.
////////////////////////////////////////////////////////////////////////////////

#ifndef SPIRE_COMMON_REAL_PROPERTY_INL
#define SPIRE_COMMON_REAL_PROPERTY_INL

namespace spire
{
    namespace common
    {
        inline RealProperty::RealProperty(const RealProperty& cpy)
        : m_proxy(cpy.m_proxy->Clone(m_storage, sizeof(m_storage)))
        {
        }

        inline RealProperty::RealProperty(const RealPropertyProxy& proxy)
        : m_proxy(proxy.Clone(m_storage, sizeof(m_storage)))
        {
        }

        inline RealProperty::~RealProperty()
        {
            if (m_proxy == reinterpret_cast<RealPropertyProxy*>(m_storage))
            {
                m_proxy->~RealPropertyProxy();
            }
            else
            {
                delete m_proxy;
            }
        }

        inline double RealProperty::Get() const
        {
            return m_proxy->Get();
        }

        inline RealProperty& RealProperty::Set(double v)
        {
            m_proxy->Set(v);
            return *this;
        }

#define PROXY_CLASS    \
        PropertyProxy<T, typename boost::enable_if<boost::is_same<typename PropertyTraits<T, void>::PropertyType,  \
                                                                  RealProperty>>::type>

        template <typename T>
        inline RealProperty PROXY_CLASS::ToProperty(ReferenceType ref)
        {
            return RealProperty(ThisType(ref));
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
        inline double PROXY_CLASS::Get() const
        {
            return PropertyTraits<T, void>::Get(m_ref);
        }

        template <typename T>
        inline void PROXY_CLASS::Set(double v)
        {
            PropertyTraits<T, void>::Set(m_ref, v);
        }

        template <typename T>
        inline RealPropertyProxy* PROXY_CLASS::Clone(void* ptr, size_t len) const
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

#endif  //  SPIRE_COMMON_REAL_PROPERTY_INL
