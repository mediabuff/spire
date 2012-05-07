////////////////////////////////////////////////////////////////////////////////
//  Copyright (C) 2012 Robert Engeln (engeln@gmail.com)
//  See accompanying LICENSE file for full license information.
////////////////////////////////////////////////////////////////////////////////

#include "prefix.hpp"
#include "spire/common/property.hpp"

using namespace spire;

TEST(PropertyTests, BooleanPropertyEncapsulatesBoolValue)
{
    bool b = false;
    Property p = b;
    ASSERT_EQ(p.Type(), PropertyTypes::Boolean);
    ASSERT_NO_THROW(p.AsBool());
    ASSERT_EQ(p.AsBool().Get(), false);
    p.AsBool().Set(true);
    ASSERT_EQ(p.AsBool().Get(), true);
    ASSERT_EQ(b, true);
    b = false;
    ASSERT_EQ(p.AsBool().Get(), false);
}

TEST(PropertyTests, IntegerPropertyEncapsulatesCharValue)
{
    char c = 1;
    Property p = c;
    ASSERT_EQ(p.Type(), PropertyTypes::Integer);
    ASSERT_NO_THROW(p.AsInt());
    ASSERT_EQ(p.AsInt().Get(), 1);
    c = 2;
    ASSERT_EQ(p.AsInt().Get(), 2);
    p.AsInt().Set(3);
    ASSERT_EQ(p.AsInt().Get(), 3);
    ASSERT_EQ(c, 3);
    ASSERT_THROW(p.AsInt().Set(-129), std::out_of_range);
    ASSERT_THROW(p.AsInt().Set(128), std::out_of_range);
}

TEST(PropertyTests, IntegerPropertyEncapsulatesUnsignedCharValue)
{
    unsigned char c = 1;
    Property p = c;
    ASSERT_EQ(p.Type(), PropertyTypes::Integer);
    ASSERT_NO_THROW(p.AsInt());
    ASSERT_EQ(p.AsInt().Get(), 1);
    c = 2;
    ASSERT_EQ(p.AsInt().Get(), 2);
    p.AsInt().Set(3);
    ASSERT_EQ(p.AsInt().Get(), 3);
    ASSERT_EQ(c, 3);
    ASSERT_THROW(p.AsInt().Set(-1), std::out_of_range);
    ASSERT_THROW(p.AsInt().Set(256), std::out_of_range);
}

TEST(PropertyTests, IntegerPropertyEncapsulatesShortValue)
{
    short c = 1;
    Property p = c;
    ASSERT_EQ(p.Type(), PropertyTypes::Integer);
    ASSERT_NO_THROW(p.AsInt());
    ASSERT_EQ(p.AsInt().Get(), 1);
    c = 2;
    ASSERT_EQ(p.AsInt().Get(), 2);
    p.AsInt().Set(3);
    ASSERT_EQ(p.AsInt().Get(), 3);
    ASSERT_EQ(c, 3);
    ASSERT_THROW(p.AsInt().Set(-32769), std::out_of_range);
    ASSERT_THROW(p.AsInt().Set(32768), std::out_of_range);
}

TEST(PropertyTests, IntegerPropertyEncapsulatesUnsignedShortValue)
{
    unsigned short c = 1;
    Property p = c;
    ASSERT_EQ(p.Type(), PropertyTypes::Integer);
    ASSERT_NO_THROW(p.AsInt());
    ASSERT_EQ(p.AsInt().Get(), 1);
    c = 2;
    ASSERT_EQ(p.AsInt().Get(), 2);
    p.AsInt().Set(3);
    ASSERT_EQ(p.AsInt().Get(), 3);
    ASSERT_EQ(c, 3);
    ASSERT_THROW(p.AsInt().Set(-1), std::out_of_range);
    ASSERT_THROW(p.AsInt().Set(65537), std::out_of_range);
}

TEST(PropertyTests, IntegerPropertyEncapsulatesIntValue)
{
    int c = 1;
    Property p = c;
    ASSERT_EQ(p.Type(), PropertyTypes::Integer);
    ASSERT_NO_THROW(p.AsInt());
    ASSERT_EQ(p.AsInt().Get(), 1);
    c = 2;
    ASSERT_EQ(p.AsInt().Get(), 2);
    p.AsInt().Set(3);
    ASSERT_EQ(p.AsInt().Get(), 3);
    ASSERT_EQ(c, 3);
    ASSERT_THROW(p.AsInt().Set(-2147483649LL), std::out_of_range);
    ASSERT_THROW(p.AsInt().Set(2147483648LL), std::out_of_range);
}

TEST(PropertyTests, IntegerPropertyEncapsulatesUnsignedIntValue)
{
    unsigned int c = 1;
    Property p = c;
    ASSERT_EQ(p.Type(), PropertyTypes::Integer);
    ASSERT_NO_THROW(p.AsInt());
    ASSERT_EQ(p.AsInt().Get(), 1);
    c = 2;
    ASSERT_EQ(p.AsInt().Get(), 2);
    p.AsInt().Set(3);
    ASSERT_EQ(p.AsInt().Get(), 3);
    ASSERT_EQ(c, 3);
    ASSERT_THROW(p.AsInt().Set(-1), std::out_of_range);
    ASSERT_THROW(p.AsInt().Set(4294967296LL), std::out_of_range);
}

TEST(PropertyTests, RealPropertyEncapsulatesFloat)
{
    float f = 1.0f;
    Property p = f;
    ASSERT_EQ(p.Type(), PropertyTypes::Real);
    ASSERT_NO_THROW(p.AsReal());
    ASSERT_EQ(p.AsReal().Get(), 1.0f);
    f = 2.0f;
    ASSERT_EQ(p.AsReal().Get(), 2.0f);
    p.AsReal().Set(3.0f);
    ASSERT_EQ(p.AsReal().Get(), 3.0f);
    ASSERT_EQ(f, 3.0f);
}

TEST(PropertyTests, RealPropertyEncapsulatesDouble)
{
    double f = 1.0f;
    Property p = f;
    ASSERT_EQ(p.Type(), PropertyTypes::Real);
    ASSERT_NO_THROW(p.AsReal());
    ASSERT_EQ(p.AsReal().Get(), 1.0f);
    f = 2.0f;
    ASSERT_EQ(p.AsReal().Get(), 2.0f);
    p.AsReal().Set(3.0f);
    ASSERT_EQ(p.AsReal().Get(), 3.0f);
    ASSERT_EQ(f, 3.0f);
}

TEST(PropertyTests, StringPropertyEncapsulatesStlString)
{
    std::string s = "Hello";
    Property p = s;
    ASSERT_EQ(p.Type(), PropertyTypes::String);
    ASSERT_NO_THROW(p.AsString());
    ASSERT_EQ(strcmp(p.AsString().Get(), "Hello"), 0);
    s = "world";
    ASSERT_EQ(strcmp(p.AsString().Get(), "world"), 0);
    p.AsString().Set("foobar");
    ASSERT_EQ(strcmp(p.AsString().Get(), "foobar"), 0);
    ASSERT_TRUE(s == "foobar");
}

TEST(PropertyTests, StringPropertyEncapsulatesCharArray)
{
    char buf[16];
    strcpy_s(buf, "Hello");
    Property p = buf;
    ASSERT_EQ(p.Type(), PropertyTypes::String);
    ASSERT_NO_THROW(p.AsString());
    ASSERT_EQ(strcmp(p.AsString().Get(), "Hello"), 0);
    strcpy_s(buf, "world");
    ASSERT_EQ(strcmp(p.AsString().Get(), "world"), 0);
    p.AsString().Set("foobar");
    ASSERT_EQ(strcmp(p.AsString().Get(), "foobar"), 0);
    ASSERT_EQ(strcmp(buf, "foobar"), 0);
    ASSERT_THROW(p.AsString().Set("averylongstringthatwontfit"), std::overflow_error);
}

TEST(PropertyTests, CollectionPropertyEncapsulatesVectorOfInts)
{
    std::vector<int> v;
    v.push_back(0);
    v.push_back(1);
    v.push_back(2);
    Property p = v;
    ASSERT_EQ(p.AsCollection().GetSize(), 3);
    Property new_int = p.AsCollection().Grow();
    new_int.AsInt().Set(3);
    ASSERT_EQ(v.size(), 4);
    ASSERT_EQ(v.back(), 3);
}

TEST(PropertyTests, CollectionPropertyCanBeEnumerated)
{
    std::vector<int> v;
    v.push_back(0);
    v.push_back(1);
    v.push_back(2);
    std::vector<int> o;
    Property p = v;
    p.AsCollection().Enumerate([&] (size_t, Property p)
    {
        return o.push_back(static_cast<int>(p.AsInt().Get())), true;
    });
    ASSERT_EQ(o.size(), 3);
    ASSERT_EQ(o[0], 0);
    ASSERT_EQ(o[1], 1);
    ASSERT_EQ(o[2], 2);
}

TEST(PropertyTests, CollectionPropertyCanBeFiltered)
{
    std::vector<int> v;
    v.push_back(0);
    v.push_back(1);
    v.push_back(2);
    v.push_back(3);
    v.push_back(4);
    Property p = v;
    p.AsCollection().Filter([&] (size_t, Property p)
    {
        return (p.AsInt().Get() & 1) != 0;
    });
    ASSERT_EQ(v.size(), 2);
    ASSERT_EQ(v[0], 1);
    ASSERT_EQ(v[1], 3);
}

TEST(PropertyTests, CollectionPropertyCanGrow)
{
    std::vector<int> v;
    Property p = v;
    p.AsCollection().Grow().AsInt().Set(0);
    p.AsCollection().Grow().AsInt().Set(1);
    p.AsCollection().Grow().AsInt().Set(2);
    p.AsCollection().Grow().AsInt().Set(3);
    ASSERT_EQ(v.size(), 4);
    ASSERT_EQ(v[0], 0);
    ASSERT_EQ(v[1], 1);
    ASSERT_EQ(v[2], 2);
    ASSERT_EQ(v[3], 3);
}

TEST(PropertyTests, CollectionPropertyEncapsulatesCompositeCollections)
{
    std::vector<std::vector<int>> v;
    v.resize(2);
    v[0].resize(2);
    v[0][0] = 0;
    v[0][1] = 1;
    v[1].resize(2);
    v[1][0] = 2;
    v[1][1] = 3;
    Property p = v;
    ASSERT_EQ(p.AsCollection().Get(0).AsCollection().Get(0).AsInt().Get(), 0);
    ASSERT_EQ(p.AsCollection().Get(0).AsCollection().Get(1).AsInt().Get(), 1);
    ASSERT_EQ(p.AsCollection().Get(1).AsCollection().Get(0).AsInt().Get(), 2);
    ASSERT_EQ(p.AsCollection().Get(1).AsCollection().Get(1).AsInt().Get(), 3);
}

TEST(PropertyTests, DictionaryPropertyEncapsulatesMapOfInts)
{
    std::map<std::string, int> m;
    m["zero"] = 0;
    m["one"] = 1;
    m["two"] = 2;
    Property p = m;
    ASSERT_EQ(p.Type(), PropertyTypes::Dictionary);
    ASSERT_NO_THROW(p.AsDictionary());
    ASSERT_EQ(p.AsDictionary().Get("zero").AsInt().Get(), 0);
    ASSERT_EQ(p.AsDictionary().Get("one").AsInt().Get(), 1);
    ASSERT_EQ(p.AsDictionary().Get("two").AsInt().Get(), 2);
}

TEST(PropertyTests, DictionaryPropertyCanGrow)
{
    std::map<std::string, int> m;
    Property p = m;
    p.AsDictionary().Grow("zero").AsInt().Set(0);
    p.AsDictionary().Grow("one").AsInt().Set(1);
    p.AsDictionary().Grow("two").AsInt().Set(2);
    ASSERT_EQ(m.size(), 3);
    ASSERT_EQ(m["zero"], 0);
    ASSERT_EQ(m["one"], 1);
    ASSERT_EQ(m["two"], 2);
}

namespace ObjectPropertyEncapsulatesPodStructNamespace
{
    struct Foo
    {
        int a;
        float b;
        bool c;
        std::string d;
    };
}

BEGIN_PROPERTY_MAP(ObjectPropertyEncapsulatesPodStructNamespace::Foo)
    DEF_PROPERTY(a)
    DEF_PROPERTY(b)
    DEF_PROPERTY(c)
    DEF_PROPERTY(d)
END_PROPERTY_MAP()

TEST(PropertyTests, ObjectPropertyEncapsulatesPodStruct)
{
    using namespace ObjectPropertyEncapsulatesPodStructNamespace;
    Foo f;
    Property p = f;
    p.AsObject().Get("a").AsInt().Set(2);
    p.AsObject().Get("b").AsReal().Set(12.0);
    p.AsObject().Get("c").AsBool().Set(true);
    p.AsObject().Get("d").AsString().Set("hello");
    ASSERT_EQ(f.a, 2);
    ASSERT_EQ(f.b, 12.0f);
    ASSERT_EQ(f.c, true);
    ASSERT_STREQ(f.d.c_str(), "hello");
}

namespace ObjectPropertyEncapsulatesObjectsWithInheritanceNamespace
{
    struct Base
    {
        int a;
    };
    struct Derived : public Base
    {
        bool b;
    };
}

BEGIN_PROPERTY_MAP(ObjectPropertyEncapsulatesObjectsWithInheritanceNamespace::Base)
    DEF_PROPERTY(a)
END_PROPERTY_MAP()

BEGIN_PROPERTY_MAP(ObjectPropertyEncapsulatesObjectsWithInheritanceNamespace::Derived)
    INHERIT_PROPERTIES(ObjectPropertyEncapsulatesObjectsWithInheritanceNamespace::Base)
    DEF_PROPERTY(b)
END_PROPERTY_MAP()

TEST(PropertyTests, ObjectPropertyEncapsulatesObjectsWithInheritance)
{
    using namespace ObjectPropertyEncapsulatesObjectsWithInheritanceNamespace;
    Derived d;
    Property p = d;
    ASSERT_NO_THROW(p.AsObject().Get("a").AsInt());
    ASSERT_NO_THROW(p.AsObject().Get("b").AsBool());
}

namespace ObjectPropertyHasCollectionFieldNamespace
{
    struct CollectionContainer
    {
        int a;
        std::vector<int> v;
    };
}

BEGIN_PROPERTY_MAP(ObjectPropertyHasCollectionFieldNamespace::CollectionContainer)
    DEF_PROPERTY(a)
    DEF_PROPERTY(v)
END_PROPERTY_MAP()

TEST(PropertyTests, ObjectPropertyCanHaveCollectionMember)
{
    using namespace ObjectPropertyHasCollectionFieldNamespace;
    CollectionContainer cc;
    Property p = cc;
    p.AsObject().Get("v").AsCollection().Grow();
    ASSERT_EQ(cc.v.size(), 1);
}

namespace ObjectPropertyEncapsulatesCompositeObjectNamespace
{
    struct Bar
    {
        int a;
    };

    struct Baz
    {
        Bar b;
    };
}
BEGIN_PROPERTY_MAP(ObjectPropertyEncapsulatesCompositeObjectNamespace::Bar)
    DEF_PROPERTY(a)
END_PROPERTY_MAP()

BEGIN_PROPERTY_MAP(ObjectPropertyEncapsulatesCompositeObjectNamespace::Baz)
    DEF_PROPERTY(b)
END_PROPERTY_MAP()

TEST(PropertyTests, ObjectPropertyEncapsulatesCompositeObject)
{
    using namespace ObjectPropertyEncapsulatesCompositeObjectNamespace;
    Baz b;
    b.b.a = 0;
    Property p = b;
    p.AsObject().Get("b").AsObject().Get("a").AsInt().Set(1);
    ASSERT_EQ(b.b.a, 1);
}

namespace ObjectPropertyEncapsulatesInnerClassNamespace
{
    struct Outer
    {
        struct Inner
        {
            int a;
        };
        Inner i;
    };
}

BEGIN_PROPERTY_MAP(ObjectPropertyEncapsulatesInnerClassNamespace::Outer::Inner)
    DEF_PROPERTY(a)
END_PROPERTY_MAP()

BEGIN_PROPERTY_MAP(ObjectPropertyEncapsulatesInnerClassNamespace::Outer)
    DEF_PROPERTY(i)
END_PROPERTY_MAP()

TEST(PropertyTests, ObjectPropertyEncapsulatesInnerClass)
{
    using namespace ObjectPropertyEncapsulatesInnerClassNamespace;
    Outer o;
    o.i.a = 0;
    Property p = o;
    p.AsObject().Get("i").AsObject().Get("a").AsInt().Set(1);
    ASSERT_EQ(o.i.a, 1);
}

namespace ObjectPropertyEncapsulatesPropertyHostNamespace
{
    class DynamicPropertyBase : public PropertyHost
    {
    public:
        int a;
        float b;
    protected:
        BEGIN_HOST_PROPERTY_MAP()
            DEF_PROPERTY(a)
            DEF_PROPERTY(b)
        END_HOST_PROPERTY_MAP()
    };

    class DynamicPropertyChild : public DynamicPropertyBase
    {
    public:
        std::string c;
    protected:
        BEGIN_HOST_PROPERTY_MAP()
            INHERIT_PROPERTIES(DynamicPropertyBase)
            DEF_PROPERTY(c)
        END_HOST_PROPERTY_MAP()
    };
}

TEST(PropertyTests, ObjectPropertyEncapsulatesPropertyHost)
{
    using namespace ObjectPropertyEncapsulatesPropertyHostNamespace;
    DynamicPropertyChild c;
    Property p = c;
    p.AsObject().Get("c").AsString().Set("hello");
    ASSERT_STREQ(c.c.c_str(), "hello");
    p.AsObject().Get("b").AsReal().Set(4.0f);
    ASSERT_EQ(c.b, 4.0f);
    p.AsObject().Get("a").AsInt().Set(21);
    ASSERT_EQ(c.a, 21);
}

namespace BoolPropertyEncapsulatesBoolPropertyWrapperNamespace
{
    class B
    {
    public:
        bool value;
        bool Get() const { return value; }
        void Set(bool b) { value = b; }
    };
}

TEST(PropertyTests, BoolPropertyEncapsulatesBoolPropertyWrapper)
{
    using namespace BoolPropertyEncapsulatesBoolPropertyWrapperNamespace;
    B b;
    b.value = false;
    auto pw = common::PropertyWrapper<bool, B, &B::Get, &B::Set>(b);
    Property p = pw;
    ASSERT_EQ(b.value, false);
    ASSERT_EQ(p.AsBool().Get(), false);
    b.value = true;
    ASSERT_EQ(p.AsBool().Get(), true);
    p.AsBool().Set(false);
    ASSERT_EQ(p.AsBool().Get(), false);
    ASSERT_EQ(b.value, false);
}

namespace IntegerPropertyEncapsulatesIntPropertyWrapperNamespace
{
    class X
    {
    public:
        int value;
        int Get() const
        {
            return value;
        }
        void Set(int v)
        {
            value = v;
        }
    };
}

TEST(PropertyTests, IntegerPropertyEncapsulatesIntPropertyWrapper)
{
    using namespace IntegerPropertyEncapsulatesIntPropertyWrapperNamespace;
    X x;
    x.value = 0;
    auto pw = common::PropertyWrapper<int, X, &X::Get, &X::Set>(x);
    Property p = pw;
    ASSERT_EQ(p.AsInt().Get(), 0);
    x.value = 1;
    ASSERT_EQ(p.AsInt().Get(), 1);
    p.AsInt().Set(2);
    ASSERT_EQ(p.AsInt().Get(), 2);
    ASSERT_EQ(x.value, 2);
}

namespace IntegerPropertyEncapsulatesConstIntRefPropertyWrapperNamespace
{
    class X
    {
    public:
        int value;
        const int& Get() const
        {
            return value;
        }
        void Set(const int& v)
        {
            value = v;
        }
    };
}

TEST(PropertyTests, IntegerPropertyEncapsulatesConstIntRefPropertyWrapper)
{
    using namespace IntegerPropertyEncapsulatesConstIntRefPropertyWrapperNamespace;
    X x;
    x.value = 0;
    auto pw = common::PropertyWrapper<const int&, X, &X::Get, &X::Set>(x);
    Property p = pw;
    ASSERT_EQ(p.AsInt().Get(), 0);
    x.value = 1;
    ASSERT_EQ(p.AsInt().Get(), 1);
    p.AsInt().Set(2);
    ASSERT_EQ(p.AsInt().Get(), 2);
    ASSERT_EQ(x.value, 2);    
}

namespace RealPropertyEncapsulatesFloatRefPropertyWrapperNamespace
{
    class X
    {
    public:
        float value;
        float Get() const
        {
            return value;
        }
        void Set(float v)
        {
            value = v;
        }
    };
}

TEST(PropertyTests, RealPropertyEncapsulatesFloatRefPropertyWrapper)
{
    using namespace RealPropertyEncapsulatesFloatRefPropertyWrapperNamespace;
    X x;
    x.value = 0;
    auto pw = common::PropertyWrapper<float, X, &X::Get, &X::Set>(x);
    Property p = pw;
    ASSERT_EQ(p.AsReal().Get(), 0);
    x.value = 1.0f;
    ASSERT_EQ(p.AsReal().Get(), 1.0f);
    p.AsReal().Set(2.0f);
    ASSERT_EQ(p.AsReal().Get(), 2.0f);
    ASSERT_EQ(x.value, 2.0f);    
}

namespace StringPropertyEncapsulatesStlStringPropertyWrapperNamespace
{
    class Foo
    {
    public:
        std::string value;
        const std::string& Get() const
        {
            return value;
        }
        void Set(const std::string& str)
        {
            value = str;
        }
    };
}

TEST(PropertyTests, StringPropertyEncapsulatesStlStringPropertyWrapper)
{
    using namespace StringPropertyEncapsulatesStlStringPropertyWrapperNamespace;
    Foo f;
    f.value = "hello";
    auto pw = common::PropertyWrapper<const std::string&, Foo, &Foo::Get, &Foo::Set>(f);
    Property p = pw;
    ASSERT_STREQ(p.AsString().Get(), "hello");
    f.value = "world";
    ASSERT_STREQ(p.AsString().Get(), "world");
    p.AsString().Set("foobar");
    ASSERT_STREQ(p.AsString().Get(), "foobar");
    ASSERT_STREQ(f.value.c_str(), "foobar");
}

namespace StringPropertyEncapsulatesConstCharPtrPropertyWrapperNamespace
{
    class Foo
    {
    public:
        char value[64];
        const char* Get() const
        {
            return value;
        }
        void Set(const char* str)
        {
            strcpy_s(value, str);
        }
    };
}

TEST(PropertyTests, StringPropertyEncapsulatesConstCharPtrPropertyWrapper)
{
    using namespace StringPropertyEncapsulatesConstCharPtrPropertyWrapperNamespace;
    Foo f;
    strcpy_s(f.value, "hello");
    auto pw = common::PropertyWrapper<const char*, Foo, &Foo::Get, &Foo::Set>(f);
    Property p = pw;
    ASSERT_STREQ(p.AsString().Get(), "hello");
    strcpy_s(f.value, "world");
    ASSERT_STREQ(p.AsString().Get(), "world");
    p.AsString().Set("foobar");
    ASSERT_STREQ(p.AsString().Get(), "foobar");
    ASSERT_STREQ(f.value, "foobar");
}

namespace
{
    enum Color
    {
        Red = 0,
        Blue = 1,
        Green = 2
    };

    BEGIN_ENUM_LABELS(Color)
        DEF_ENUM_LABEL("red", Red);
        DEF_ENUM_LABEL("blue", Blue);
        DEF_ENUM_LABEL("green", Green);
    END_ENUM_LABELS()
}

TEST(PropertyTests, EnumPropertyCanSetByValue)
{
    Color c = Red;
    Property p = c;
    p.AsEnum().Set(Blue);
    ASSERT_EQ(Blue, c);
    ASSERT_EQ(static_cast<int>(Blue), p.AsEnum().Get());
}

TEST(PropertyTests, EnumPropertyCanSetByLabel)
{
    Color c = Red;
    Property p = c;
    p.AsEnum().Set("blue");
    ASSERT_EQ(Blue, c);
    ASSERT_STREQ("blue", p.AsEnum().GetString());
    p.AsEnum().Set("GREEN");
    ASSERT_EQ(Green, c);
    ASSERT_STREQ("green", p.AsEnum().GetString());
}
