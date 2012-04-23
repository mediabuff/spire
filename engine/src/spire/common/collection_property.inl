////////////////////////////////////////////////////////////////////////////////
//  Copyright (C) 2012 Robert Engeln (engeln@gmail.com)
//  See accompanying LICENSE file for full license information.
////////////////////////////////////////////////////////////////////////////////

#ifndef SPIRE_COMMON_COLLECTION_PROPERTY_INL
#define SPIRE_COMMON_COLLECTION_PROPERTY_INL

namespace spire
{
    namespace common
    {
        inline CollectionProperty::CollectionProperty(const CollectionProperty& cpy)
        : m_proxy(cpy.m_proxy->Clone(m_storage, sizeof(m_storage)))
        {
        }

        inline CollectionProperty::CollectionProperty(const CollectionPropertyProxy& proxy)
        : m_proxy(proxy.Clone(m_storage, sizeof(m_storage)))
        {
        }

        inline CollectionProperty::~CollectionProperty()
        {
            if (m_proxy == reinterpret_cast<CollectionPropertyProxy*>(m_storage))
            {
                m_proxy->~CollectionPropertyProxy();
            }
            else
            {
                delete m_proxy;
            }
        }

        inline size_t CollectionProperty::GetSize() const
        {
            return m_proxy->GetSize();
        }

        inline Property CollectionProperty::Get(size_t index)
        {
            return m_proxy->Get(index);
        }

        template <typename F>
        class CollectionPropertyEnumeratorImpl : public CollectionPropertyEnumerator
        {
        public:
            CollectionPropertyEnumeratorImpl(F& func)
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
        inline void CollectionProperty::Enumerate(T visitor)
        {
            auto e = CollectionPropertyEnumeratorImpl<T>(visitor);
            m_proxy->Enumerate(e);
        }

        template <typename F>
        class CollectionPropertyFilterImpl : public CollectionPropertyFilter
        {
        public:
            CollectionPropertyFilterImpl(F& func)
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
        inline void CollectionProperty::Filter(T visitor)
        {
            auto f = CollectionPropertyFilterImpl<T>(visitor);
            m_proxy->Filter(f);
        }

        inline Property CollectionProperty::Grow()
        {
            return m_proxy->Grow();
        }

#define PROXY_CLASS    \
        PropertyProxy<T, typename boost::enable_if<boost::is_same<typename PropertyTraits<T, void>::PropertyType,  \
                                                                  CollectionProperty>>::type>

        template <typename T>
        CollectionProperty PROXY_CLASS::ToProperty(ReferenceType ref)
        {
            return CollectionProperty(ThisType(ref));
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
        size_t PROXY_CLASS::GetSize() const
        {
            return PropertyTraits<T, void>::GetSize(m_ref);
        }

        template <typename T>
        Property PROXY_CLASS::Get(size_t index)
        {
            return PropertyTraits<T, void>::Get(m_ref, index);
        }

        template <typename T>
        void PROXY_CLASS::Enumerate(CollectionPropertyEnumerator& visitor)
        {
            PropertyTraits<T, void>::Enumerate(m_ref, visitor);
        }

        template <typename T>
        void PROXY_CLASS::Filter(CollectionPropertyFilter& visitor)
        {
            PropertyTraits<T, void>::Filter(m_ref, visitor);
        }

        template <typename T>
        Property PROXY_CLASS::Grow()
        {
            return PropertyTraits<T, void>::Grow(m_ref);
        }

        template <typename T>
        CollectionPropertyProxy* PROXY_CLASS::Clone(void* ptr, size_t len) const
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

#endif  //  SPIRE_COMMON_COLLECTION_PROPERTY_INL
