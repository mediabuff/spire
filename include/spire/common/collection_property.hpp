////////////////////////////////////////////////////////////////////////////////
//  Copyright (C) 2012 Robert Engeln (engeln@gmail.com)
//  See accompanying LICENSE file for full license information.
////////////////////////////////////////////////////////////////////////////////
/// @file spire/common/collection_property.hpp 
/// Defines the CollectionProperty class.
/// @addtogroup common
/// @{

#ifndef SPIRE_COMMON_COLLECTION_PROPERTY_HPP
#define SPIRE_COMMON_COLLECTION_PROPERTY_HPP

namespace spire
{
    namespace common
    {
        class Property;
        class CollectionPropertyProxy;
        template <typename T, typename Enabler> class PropertyProxy;
        template <typename T, typename Enabler> class PropertyTraits;

        ///
        /// Property encapsulating a collection of elements, each of which
        /// is accessible as another Property.
        ///
        class CollectionProperty
        {
        public:
            //
            //  Copy constructor.
            //
            CollectionProperty(const CollectionProperty&);

            //
            //  Construct from a proxy object.
            //
            CollectionProperty(const CollectionPropertyProxy&);

            //
            //  Destructor.
            //
            ~CollectionProperty();

            //
            //  Returns the number of items in the collection.
            //
            size_t GetSize() const;

            //
            //  Returns the element at the given index.
            //
            Property Get(size_t index);

            //
            //  Enumerates through the collection.
            //
            template <typename T>
            void Enumerate(T visitor);

            //
            //  Filters the collection, removing elements rejected by the filter.
            //
            template <typename T>
            void Filter(T visistor);

            //
            //  Adds an item to the collection and returns it as a Property object.
            //
            Property Grow();

        private:
            CollectionPropertyProxy* m_proxy;
            char m_storage[16];
        };

        // 
        //  Functor which can enumerate through a collection property.
        //
        //  @param index Index of the element in the collection.
        //  @param p Property object wrapping the element.
        //  @return True if the enumeration should continue,
        //          or false to terminate.
        //
        class CollectionPropertyEnumerator
        {
        public:
            virtual bool operator()(size_t index, Property p) = 0;
        };

        //
        //  Functor which can filter a collection property.
        //
        //  @param index Index of the element in the collection.
        //  @param p Property object wrapping the element.
        //  @return True if the element should remain in the collection, or
        //          false if it should be removed.
        //
        class CollectionPropertyFilter
        {
        public:
            virtual bool operator()(size_t index, Property p) = 0;
        };

        //
        //  Internal interface for Collection property proxy objects.
        //
        class CollectionPropertyProxy
        {
        public:
            virtual size_t GetSize() const = 0;
            virtual Property Get(size_t index) = 0;
            virtual void Enumerate(CollectionPropertyEnumerator& visitor) = 0;
            virtual void Filter(CollectionPropertyFilter& visitor) = 0;
            virtual Property Grow() = 0;
            virtual CollectionPropertyProxy* Clone(void* ptr, size_t len) const = 0;
        };

        //
        //  Proxy class for Collection properties.
        //
        template <typename T>
        class PropertyProxy<T, typename boost::enable_if<boost::is_same<typename PropertyTraits<T, void>::PropertyType, CollectionProperty>>::type> 
            : public CollectionPropertyProxy
        {
        public:
            typedef typename boost::enable_if<boost::is_same<typename PropertyTraits<T, void>::PropertyType, CollectionProperty>>::type Enabler;
            typedef PropertyProxy<T, Enabler> ThisType;
            typedef typename PropertyTraits<T, void>::ReferenceType ReferenceType;

            static CollectionProperty ToProperty(ReferenceType);

            PropertyProxy(ReferenceType);
            PropertyProxy(const ThisType& cpy);
            virtual size_t GetSize() const;
            virtual Property Get(size_t index);
            virtual void Enumerate(CollectionPropertyEnumerator& visitor);
            virtual void Filter(CollectionPropertyFilter& visitor);
            virtual Property Grow();
            virtual CollectionPropertyProxy* Clone(void* ptr, size_t len) const;

        private:
            ReferenceType m_ref;
        };
    }
}

#endif  //  SPIRE_COMMON_COLLECTION_PROPERTY_HPP
