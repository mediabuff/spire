////////////////////////////////////////////////////////////////////////////////
//  Copyright (C) 2012 Robert Engeln (engeln@gmail.com)
//  See accompanying LICENSE file for full license information.
////////////////////////////////////////////////////////////////////////////////
/// @file spire/common/dictionary_property.hpp 
/// Defines the DictionaryProperty class.
/// @addtogroup common
/// @{

#ifndef SPIRE_COMMON_DICTIONARY_PROPERTY_HPP
#define SPIRE_COMMON_DICTIONARY_PROPERTY_HPP

namespace spire
{
    namespace common
    {
        class Property;
        class DictionaryPropertyProxy;
        template <typename T, typename Enabler> class PropertyProxy;
        template <typename T, typename Enabler> class PropertyTraits;

        ///
        /// Encapsulates a dynamic key-value store.
        ///
        class DictionaryProperty
        {
        public:
            //
            //  Copy constructor.
            //
            DictionaryProperty(const DictionaryProperty&);

            //
            //  Construct from a proxy object.
            //
            DictionaryProperty(const DictionaryPropertyProxy&);
            
            //
            //  Destructor.
            //
            ~DictionaryProperty();
            
            //
            //  Returns the property associated with a given key, or an empty
            //  Property object if there is no such element.
            //
            Property Get(const std::string& key);

            //
            //  Enumerates through the dictionary.
            //
            template <typename T>
            void Enumerate(T visitor);
            
            //
            //  Filters the dictionary, removing any elements which are rejected
            //  by the filter.
            //
            template <typename T>
            void Filter(T visitor);

            //
            //  Adds a new element to the dictionary.
            //
            Property Grow(const std::string& key);

        private:
            DictionaryPropertyProxy* m_proxy;
            char m_storage[16];
        };


        //
        //  Functor for enumerating through a dictionary.
        //
        //  Parameters:
        //      [in] key
        //          Key associated with the element.
        //      [in] p
        //          Value of the element as a Property object.
        //
        //  Return value:
        //      True if the enumeration should continue, or false to terminate.
        //
        class DictionaryPropertyEnumerator
        {
        public:
            virtual bool operator()(const std::string& key, Property p) = 0;
        };

        //
        //  Functor for filtering a dictionary.
        //
        //  Parameters:
        //      [in] key
        //          Key associated with the element.
        //      [in] p
        //          Value of the element as a Property object.
        //
        //  Return value:
        //      True if the enumeration should continue, or false to terminate.
        //
        class DictionaryPropertyFilter
        {
        public:
            virtual bool operator()(const std::string& key, Property p) = 0;
        };

        //
        //  Interface for Dictionary property proxy objects.
        //
        class DictionaryPropertyProxy
        {
        public:
            virtual Property Get(const std::string& key) = 0;
            virtual void Enumerate(DictionaryPropertyEnumerator& visitor) = 0;
            virtual void Filter(DictionaryPropertyFilter& visitor) = 0;
            virtual Property Grow(const std::string& key) = 0;
            virtual DictionaryPropertyProxy* Clone(void* ptr, size_t len) const = 0;
        };

        template <typename T>
        class PropertyProxy<T, typename boost::enable_if<boost::is_same<typename PropertyTraits<T, void>::PropertyType, DictionaryProperty>>::type> 
            : public DictionaryPropertyProxy
        {
        public:
            typedef typename boost::enable_if<boost::is_same<typename PropertyTraits<T, void>::PropertyType, DictionaryProperty>>::type Enabler;
            typedef PropertyProxy<T, Enabler> ThisType;
            typedef typename PropertyTraits<T, void>::ReferenceType ReferenceType;

            static DictionaryProperty ToProperty(ReferenceType ref);

            PropertyProxy(ReferenceType ref);
            PropertyProxy(const ThisType& cpy);
            virtual Property Get(const std::string& key);
            virtual void Enumerate(DictionaryPropertyEnumerator& visitor);
            virtual void Filter(DictionaryPropertyFilter& visitor);
            virtual Property Grow(const std::string& key);
            virtual DictionaryPropertyProxy* Clone(void* ptr, size_t len) const;

        private:
            ReferenceType m_ref;
        };
    }
}

#endif  //  SPIRE_COMMON_DICTIONARY_PROPERTY_HPP
