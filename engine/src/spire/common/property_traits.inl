////////////////////////////////////////////////////////////////////////////////
//  Copyright (C) 2012 Robert Engeln (engeln@gmail.com)
//  See accompanying LICENSE file for full license information.
////////////////////////////////////////////////////////////////////////////////

#ifndef SPIRE_COMMON_PROPERTY_TRAITS_INL
#define SPIRE_COMMON_PROPERTY_TRAITS_INL

namespace spire
{
    namespace common
    {
        //
        //  Helper trait to differentiate between bool and integer.
        //
        template <typename T>
        class IsIntegral
        {
        public:
            static const bool value = boost::is_integral<T>::value &&
                                      !(boost::is_same<T, bool>::value);
        };

        //
        //  PropertyTraits implementation for bool.
        //
        template <>
        class PropertyTraits<bool>
        {
        public:
            typedef BooleanProperty PropertyType;
            typedef bool& ReferenceType;

            static bool Get(const bool& b)
            {
                return b;
            }
            static void Set(bool& b, bool v)
            {
                b = v;
            }
        };

        //
        //  PropertyTraits implementation for boolean PropertyWrappers
        //
        template <typename C, typename T, T (C::*G)(void) const, void (C::*S)(T)>
        class PropertyTraits<PropertyWrapper<T, C, G, S>,
                             typename boost::enable_if<boost::is_same<typename boost::remove_reference<T>::type,
                                                                      bool>>::type>
        {
        public:
            typedef BooleanProperty PropertyType;
            typedef PropertyWrapper<T, C, G, S> ReferenceType;

            static bool Get(const PropertyWrapper<T, C, G, S>& p)
            {
                return p.Get();
            }
            static void Set(PropertyWrapper<T, C, G, S>& p, bool v)
            {
                p.Set(v);
            }
        };

        //
        //  PropertyTraits implementation for integral types.
        //
        template <typename T>
        class PropertyTraits<T, typename boost::enable_if<IsIntegral<T>>::type>
        {
        public:
            typedef IntegerProperty PropertyType;
            typedef T& ReferenceType;

            static int64_t Get(const T& i)
            {
                return static_cast<int64_t>(i);
            }
            static void Set(T& i, int64_t v)
            {
                auto lim = Limits(i);
                if (v < lim.first || v > lim.second)
                    throw std::out_of_range("Integer range overflow");
                i = static_cast<T>(v);
            }
            static std::pair<int64_t, int64_t> Limits(const T&)
            {
                return std::make_pair(static_cast<int64_t>(std::numeric_limits<T>::min()),
                                      static_cast<int64_t>(std::numeric_limits<T>::max()));
            }
        };

        //
        //  PropertyTraits implementation for integral PropertyWrappers
        //
        template <typename C, typename T, T (C::*G)(void) const, void (C::*S)(T)>
        class PropertyTraits<PropertyWrapper<T, C, G, S>,
                             typename boost::enable_if<IsIntegral<typename boost::remove_reference<T>::type>>::type>
        {
        public:
            typedef IntegerProperty PropertyType;
            typedef PropertyWrapper<T, C, G, S> ReferenceType;

            static int64_t Get(const PropertyWrapper<T, C, G, S>& p)
            {
                return static_cast<int64_t>(p.Get());
            }
            static void Set(PropertyWrapper<T, C, G, S>& p, int64_t v)
            {
                p.Set(static_cast<typename boost::remove_reference<T>::type>(v));
            }
        };

        //
        //  Macro for defining EnumTraits implementations.
        //
#define BEGIN_ENUM_LABELS(x)                                                    \
        class x ## _EnumTraits                                                  \
        {                                                                       \
        public:                                                                 \
            template <typename T>                                               \
            static void EnumerateLabels(T& fn)                                  \
            {                                                                   
#define DEF_ENUM_LABEL(str, val)                                                \
                if (!fn(str, static_cast<int>(val))) return;                              
#define END_ENUM_LABELS(...)                                                    \
            }                                                                   \
        };                                                                      \
        inline Color_EnumTraits GetEnumTraits(Color*);  

        //
        //  PropertyTraits implementation for enums.
        //
        template <typename T>
        class PropertyTraits<T, typename boost::enable_if<boost::is_enum<T>>::type>
        {
        public:
            typedef EnumProperty PropertyType;
            typedef T& ReferenceType;

            static int Get(const T& e)
            {
                return static_cast<int>(e);
            }
            static const char* GetString(const T& e)
            {
                //  Note: an error here means you didn't define the enum traits
                //  using the BEGIN_ENUM_LABELS()/DEF_LABEL()/END_ENUM_LABELS() macro
                typedef decltype(GetEnumTraits(static_cast<T*>(nullptr))) EnumTraits;
                const char* label = nullptr;
                EnumTraits::EnumerateLabels([&] (const char* str, int val) -> bool
                {
                    if (val == static_cast<int>(e))
                    {
                        label = str;
                        return false;
                    }
                    return true;
                });
                assert(label);
                return label;
            }
            static void Set(T& e, int v)
            {
                e = static_cast<T>(v);
            }
            static void Set(T& e, const char* label)
            {
                typedef decltype(GetEnumTraits(static_cast<T*>(nullptr))) EnumTraits;
                bool found = false;
                EnumTraits::EnumerateLabels([&] (const char* str, int val) -> bool
                {
                    if (_stricmp(str, label) == 0)
                    {
                        e = static_cast<T>(val);
                        found = true;
                        return false;
                    }
                    return true;
                });
                assert(found);
            }
        };

        //
        //  PropertyTraits implementation for floating-point types.
        //
        template <typename T>
        class PropertyTraits<T, typename boost::enable_if<boost::is_floating_point<T>>::type>
        {
        public:
            typedef RealProperty PropertyType;
            typedef T& ReferenceType;
            static double Get(const T& f)
            {
                return static_cast<double>(f);
            }
            static void Set(T& f, double d)
            {
                f = static_cast<T>(d);
            }
        };

        //
        //  PropertyTraits implementation for floating-point PropertyWrappers
        //
        template <typename C, typename T, T (C::*G)(void) const, void (C::*S)(T)>
        class PropertyTraits<PropertyWrapper<T, C, G, S>,
                             typename boost::enable_if<boost::is_floating_point<typename boost::remove_reference<T>::type>>::type>
        {
        public:
            typedef RealProperty PropertyType;
            typedef PropertyWrapper<T, C, G, S> ReferenceType;

            static double Get(const PropertyWrapper<T, C, G, S>& p)
            {
                return static_cast<double>(p.Get());
            }
            static void Set(PropertyWrapper<T, C, G, S>& p, double v)
            {
                p.Set(static_cast<typename boost::remove_reference<T>::type>(v));
            }
        };

        //
        //  PropertyTraits implementation for std::string.
        //
        template <>
        class PropertyTraits<std::string>
        {
        public:
            typedef StringProperty PropertyType;
            typedef std::string& ReferenceType;
            static const char* Get(const std::string& str)
            {
                return str.c_str();
            }
            static void Set(std::string& str, const char* rhs)
            {
                str = rhs;
            }
        };        

        //
        //  PropertyTraits implementation for char arrays.
        //
        template <size_t N>
        class PropertyTraits<char[N]>
        {
        public:
            typedef StringProperty PropertyType;
            typedef char (&ReferenceType)[N];
            static const char* Get(const char (&str)[N])
            {
                return str;
            }
            static void Set(char (&str)[N], const char* rhs)
            {
                if (strlen(rhs) > (N-1))
                {
                    throw std::overflow_error("Not enough capacity for string");
                }
                strcpy_s(str, rhs);
            }
        };

        //
        //  PropertyTraits implementation for const std::string& PropertyWrappers
        //
        template <typename C, const std::string& (C::*G)(void) const, void (C::*S)(const std::string&)>
        class PropertyTraits<PropertyWrapper<const std::string&, C, G, S>>
        {
        public:
            typedef StringProperty PropertyType;
            typedef PropertyWrapper<const std::string&, C, G, S> ReferenceType;

            static const char* Get(const PropertyWrapper<const std::string&, C, G, S>& p)
            {
                return p.Get().c_str();
            }
            static void Set(PropertyWrapper<const std::string&, C, G, S>& p, const char* str)
            {
                p.Set(str);
            }
        };

        //
        //  PropertyTraits implementation for const char* PropertyWrappers
        //
        template <typename C, const char* (C::*G)(void) const, void (C::*S)(const char*)>
        class PropertyTraits<PropertyWrapper<const char*, C, G, S>>
        {
        public:
            typedef StringProperty PropertyType;
            typedef PropertyWrapper<const char*, C, G, S> ReferenceType;

            static const char* Get(const PropertyWrapper<const char*, C, G, S>& p)
            {
                return p.Get();
            }
            static void Set(PropertyWrapper<const char*, C, G, S>& p, const char* str)
            {
                p.Set(str);
            }
        };

        //
        //  PropertyTraits implementation for std::vector.
        //
        template <typename T>
        class PropertyTraits<std::vector<T>>
        {
        public:
            typedef CollectionProperty PropertyType;
            typedef std::vector<T>& ReferenceType;

            static size_t GetSize(const std::vector<T>& obj)
            {
                return obj.size();
            }

            static Property Get(std::vector<T>& obj, size_t index)
            {
                return obj[index];
            }

            static void Enumerate(std::vector<T>& obj, CollectionPropertyEnumerator& visitor)
            {
                size_t index = 0;
                for (auto i = obj.begin(); i != obj.end(); ++i)
                {
                    if (!visitor(index++, *i))
                    {
                        break;
                    }
                }
            }

            static void Filter(std::vector<T>& obj, CollectionPropertyFilter& visitor)
            {
                size_t index = 0;
                auto pred = [&] (decltype(*obj.begin())& v)
                {
                    return !visitor(index++, v);
                };
                obj.erase(std::remove_if(obj.begin(),
                                         obj.end(),
                                         pred),
                          obj.end());
            }

            static Property Grow(std::vector<T>& obj)
            {
                obj.push_back(T());
                return obj.back();
            }
        };

        //
        //  PropertyTraits implementation for std::map.
        //
        template <typename T>
        class PropertyTraits<std::map<std::string, T>>
        {
        public:
            typedef DictionaryProperty PropertyType;
            typedef std::map<std::string, T>& ReferenceType;

            static Property Get(std::map<std::string, T>& m, const std::string& key)
            {
                auto i = m.find(key);
                if (i == m.end())
                {
                    return Property();
                }
                else
                {
                    return i->second;
                }
            }

            static void Enumerate(std::map<std::string, T>& m, DictionaryPropertyEnumerator& visitor)
            {
                for (auto i = m.begin(); i != m.end(); ++i)
                {
                    if (!visitor(i->first, i->second))
                    {
                        break;
                    }
                }
            }

            static void Filter(std::map<std::string, T>& m, DictionaryPropertyFilter& visitor)
            {
                for (auto i = m.begin(); i != m.end();)
                {
                    auto j = i++;
                    if (!visitor(j->first, j->second))
                    {
                        m.erase(j);
                    }
                }
            }

            static Property Grow(std::map<std::string, T>& m, const std::string& key)
            {
                auto result = m.insert(std::make_pair(key, T()));
                return result.first->second;
            }
        };

        //
        //  PropertyTraits implementation for a PropertyHost-derived type.
        //
        template <typename T>
        class PropertyTraits<T, typename boost::enable_if<boost::is_base_of<class PropertyHost, T>>::type>
        {
        public:
            typedef ObjectProperty PropertyType;
            typedef T& ReferenceType;

            static void Enumerate(T& obj, ObjectPropertyEnumerator& visitor)
            {
                return static_cast<PropertyHost&>(obj).EnumerateProperties(visitor);
            }

            static Property Get(T& obj, const std::string& key)                    
            {                                                                   
                struct Enumerator : ObjectPropertyEnumerator                     
                {                                                               
                    Enumerator(Property& p, const std::string& name)                
                    : pRef(p), name(name)                                       
                    {                                                           
                    }                                                           
                                                                                
                    bool operator()(const std::string& key, Property p)             
                    {                                                           
                        if (key == name)                                        
                        {                                                       
                            pRef = p;                                           
                            return false;                                       
                        }                                                       
                        return true;                                            
                    }                                                           
                                                                                
                    Property& pRef;                                             
                    const std::string& name;                                        
                };                                                              
                Property result;                                                
                Enumerator e(result, key);                                      
                Enumerate(obj, e);                                              
                return result;                                                  
            }  
        };

        //
        //  Functions which allow the INHERIT_PROPERTIES macro to work for
        //  both static and dynamic property hosts. They are classes because
        //  it's syntactically simpler to befriend a class than a function
        //  with a dependent return type.
        //
        template <typename T, typename Enabler = void>
        class InheritProperties
        {
        public:
            static void Do(T& obj, ObjectPropertyEnumerator& e)
            {
                PropertyTraits<T>::Enumerate(obj, e);
            }
        };

        template <typename T>
        class InheritProperties<T, typename boost::enable_if<boost::is_base_of<PropertyHost, T>>::type>
        {
        public:
            static void Do(T& obj, ObjectPropertyEnumerator& e)
            {
                obj.EnumeratePropertiesNonVirtual(e);
            }
        };

        //  Enable us to introspect the class from a pointer-to-member function
        template <typename T, typename C>
        auto GetterType(T (C::*func)(void) const) -> C;

        //
        //  Macro for generating a PropertyTraits implementation for an object.
        //
#define BEGIN_PROPERTY_MAP(T)                                                   \
        template <>                                                             \
        class spire::common::PropertyTraits<T>                                    \
        {                                                                       \
        public:                                                                 \
            typedef ObjectProperty PropertyType;                                \
            typedef T ObjectType;                                               \
            typedef T& ReferenceType;                                           \
                                                                                \
            static void Enumerate(T& obj, ObjectPropertyEnumerator& e)     \
            {                                                                   \
                typedef T _Self;
#define DEF_PROPERTY(p) \
            e(#p, obj.p);
#define DEF_PROPERTY_ALIAS(name, p) \
            e(name, obj.p);
#define DEF_PROPERTY_WRAPPER(name, get, set) \
            e(name, PropertyWrapper<decltype(spire::common::GetterType(get)), _Self, &_Self::get, &_Self::set>(obj));
#define INHERIT_PROPERTIES(c) \
            spire::common::InheritProperties<c>::Do(static_cast<c&>(obj), e);
#define END_PROPERTY_MAP(...)                                                   \
            }                                                                   \
                                                                                \
            static Property Get(ObjectType& obj, const std::string& key)                    \
            {                                                                   \
                struct Enumerator : ObjectPropertyEnumerator                     \
                {                                                               \
                    Enumerator(Property& p, const std::string& name)                \
                    : pRef(p), name(name)                                       \
                    {                                                           \
                    }                                                           \
                                                                                \
                    bool operator()(const std::string& key, Property p)             \
                    {                                                           \
                        if (key == name)                                        \
                        {                                                       \
                            pRef = p;                                           \
                            return false;                                       \
                        }                                                       \
                        return true;                                            \
                    }                                                           \
                                                                                \
                    Property& pRef;                                             \
                    const std::string& name;                                        \
                };                                                              \
                Property result;                                                \
                Enumerator e(result, key);                                      \
                Enumerate(obj, e);                                              \
                return result;                                                  \
            }                                                                   \
        };
    }
}

#endif  //  SPIRE_COMMON_PROPERTY_TRAITS_HPP
