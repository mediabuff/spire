////////////////////////////////////////////////////////////////////////////////
//  Copyright (C) 2012 Robert Engeln (engeln@gmail.com)
//  See accompanying LICENSE file for full license information.
////////////////////////////////////////////////////////////////////////////////

#ifndef SPIRE_COMMON_DICTIONARY_PROPERTY_INL
#define SPIRE_COMMON_DICTIONARY_PROPERTY_INL

namespace spire
{
    namespace common
    {
        inline DictionaryProperty::DictionaryProperty(const DictionaryProperty& cpy)
        : m_proxy(cpy.m_proxy->Clone(m_storage, sizeof(m_storage)))
        {
        }

        inline DictionaryProperty::DictionaryProperty(const DictionaryPropertyProxy& proxy)
        : m_proxy(proxy.Clone(m_storage, sizeof(m_storage)))
        {
        }

        inline DictionaryProperty::~DictionaryProperty()
        {
            if (m_proxy == reinterpret_cast<DictionaryPropertyProxy*>(m_storage))
            {
                m_proxy->~DictionaryPropertyProxy();
            }
            else
            {
                delete m_proxy;
            }
        }

        inline Property DictionaryProperty::Get(const std::string& key)
        {
            return m_proxy->Get(key);
        }

        template <typename F>
        class DictionaryPropertyEnumeratorProxy : public DictionaryPropertyEnumerator
        {
        public:
            DictionaryPropertyEnumeratorProxy(F& func)
            : m_func(func)
            {
            }

            virtual bool operator()(size_t i, Property p)
            {
                return m_func(i, p);
            }

        private:
            F& m_func;
        };

        template <typename T>
        inline void DictionaryProperty::Enumerate(T visitor)
        {
            m_proxy->Enumerate(DictionaryPropertyEnumeratorProxy<T>(visitor));
        }

        template <typename F>
        class DictionaryPropertyFilterProxy : public DictionaryPropertyFilter
        {
        public:
            DictionaryPropertyFilterProxy(F& func)
            : m_func(func)
            {
            }

            virtual bool operator()(size_t i, Property p)
            {
                return m_func(i, p);
            }

        private:
            F& m_func;
        };

        template <typename T>
        inline void DictionaryProperty::Filter(T visitor)
        {
            m_proxy->Filter(DictionaryPropertyFilterProxy<T>(visitor));
        }

        inline Property DictionaryProperty::Grow(const std::string& key)
        {
            return m_proxy->Grow(key);
        }

#define PROXY_CLASS    \
        PropertyProxy<T, typename boost::enable_if<boost::is_same<typename PropertyTraits<T, void>::PropertyType,  \
                                                                  DictionaryProperty>>::type>

        template <typename T>
        DictionaryProperty PROXY_CLASS::ToProperty(ReferenceType ref)
        {
            return DictionaryProperty(ThisType(ref));
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
        void PROXY_CLASS::Enumerate(DictionaryPropertyEnumerator& visitor)
        {
            return PropertyTraits<T, void>::Enumerate(m_ref, visitor);
        }

        template <typename T>
        void PROXY_CLASS::Filter(DictionaryPropertyFilter& visitor)
        {
            return PropertyTraits<T, void>::Filter(m_ref, visitor);
        }

        template <typename T>
        Property PROXY_CLASS::Grow(const std::string& key)
        {
            return PropertyTraits<T, void>::Grow(m_ref, key);
        }

        template <typename T>
        DictionaryPropertyProxy* PROXY_CLASS::Clone(void* ptr, size_t len) const
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

#endif  //  SPIRE_COMMON_DICTIONARY_PROPERTY_INL
