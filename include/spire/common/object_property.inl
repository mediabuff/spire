////////////////////////////////////////////////////////////////////////////////
//  Copyright (C) 2012 Robert Engeln (engeln@gmail.com)
//  See accompanying LICENSE file for full license information.
////////////////////////////////////////////////////////////////////////////////

#ifndef SPIRE_COMMON_OBJECT_PROPERTY_INL
#define SPIRE_COMMON_OBJECT_PROPERTY_INL

namespace spire
{
    namespace common
    {
        inline ObjectProperty::ObjectProperty(const ObjectProperty& cpy)
        : m_proxy(cpy.m_proxy->Clone(m_storage, sizeof(m_storage)))
        {
        }

        inline ObjectProperty::ObjectProperty(const ObjectPropertyProxy& proxy)
        : m_proxy(proxy.Clone(m_storage, sizeof(m_storage)))
        {
        }

        inline ObjectProperty::~ObjectProperty()
        {
            if (m_proxy == reinterpret_cast<ObjectPropertyProxy*>(m_storage))
            {
                m_proxy->~ObjectPropertyProxy();
            }
            else
            {
                delete m_proxy;
            }
        }

        inline Property ObjectProperty::Get(const std::string& key)
        {
            return m_proxy->Get(key);
        }

        template <typename F>
        class ObjectPropertyEnumeratorProxy : public ObjectPropertyEnumerator
        {
        public:
            ObjectPropertyEnumeratorProxy(F& func)
            : m_func(func)
            {
            }

            virtual bool operator()(const std::string& str, Property p)
            {
                return m_func(str, p);
            }

        private:
            F& m_func;
        };

        template <typename T>
        inline void ObjectProperty::Enumerate(T visitor)
        {       
            m_proxy->Enumerate(ObjectPropertyEnumeratorProxy<T>(visitor));
        }

#define PROXY_CLASS    \
        PropertyProxy<T, typename boost::enable_if<boost::is_same<typename PropertyTraits<T, void>::PropertyType,  \
                                                                  ObjectProperty>>::type>

        template <typename T>
        ObjectProperty PROXY_CLASS::ToProperty(ReferenceType ref)
        {
            return ObjectProperty(ThisType(ref));
        }

        template <typename T>
        PROXY_CLASS::PropertyProxy(ReferenceType ref)
        : m_ref(ref)
        {
        }

        template <typename T>
        PROXY_CLASS::PropertyProxy(const ThisType& cpy)
        : m_ref(cpy.m_ref)
        {
        }

        template <typename T>
        Property PROXY_CLASS::Get(const std::string& key)
        {
            return PropertyTraits<T, void>::Get(m_ref, key);
        }

        template <typename T>
        void PROXY_CLASS::Enumerate(ObjectPropertyEnumerator& visitor)
        {
            return PropertyTraits<T, void>::Enumerate(m_ref, visitor);
        }

        template <typename T>
        ObjectPropertyProxy* PROXY_CLASS::Clone(void* ptr, size_t len) const
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
    }
}

#endif  //  SPIRE_COMMON_OBJECT_PROPERTY_INL
