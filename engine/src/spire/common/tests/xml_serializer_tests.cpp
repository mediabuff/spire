////////////////////////////////////////////////////////////////////////////////
//  Copyright (C) 2012 Robert Engeln (engeln@gmail.com)
//  See accompanying LICENSE file for full license information.
////////////////////////////////////////////////////////////////////////////////

#include "prefix.hpp"
#include "spire/common/xml_serializer.hpp"

using namespace spire;

TEST(XmlSerializerTests, DeserializeValueFromString)
{
    std::string src = "<node>1</node>";
    int a = 0; 
    src >> XmlSerializer(a);
    ASSERT_EQ(a, 1); 
}

TEST(XmlSerializerTests, DeserializeCollectionFromString)
{
    std::string src =  
        "<array>"
        "<item>1</item>"
        "<item>2</item>"
        "<item>3</item>"
        "</array>";
    std::vector<int> v;
    src >> XmlSerializer(v);
    ASSERT_EQ(v.size(), 3);
    ASSERT_EQ(v[0], 1);
    ASSERT_EQ(v[1], 2);
    ASSERT_EQ(v[2], 3);
}

TEST(XmlSerializerTests, DeserializeDictionaryFromString)
{
    std::string src = 
        "<dict>"
        "<item key=\"one\">1</item>"
        "<item key=\"two\">2</item>"
        "<item key=\"three\">3</item>"
        "</dict>";
    std::map<std::string, int> m;
    src >> XmlSerializer(m);
    ASSERT_EQ(m.size(), 3);
    ASSERT_EQ(m["one"], 1);
    ASSERT_EQ(m["two"], 2);
    ASSERT_EQ(m["three"], 3);
}

struct Foo123
{
    int a;
    std::string b;
    std::vector<int> c;
};

BEGIN_PROPERTY_MAP(Foo123)
    DEF_PROPERTY(a)
    DEF_PROPERTY(b);
    DEF_PROPERTY(c)
END_PROPERTY_MAP()

TEST(XmlSerializerTests, DeserializeObjectFromString)
{
    std::string src = 
        "<object>"
        "<a>1</a>"
        "<b>hello world</b>"
        "<c><item>1</item><item>2</item><item>3</item></c>"
        "</object>";
    Foo123 f;
    f.a = 0;
    src >> XmlSerializer(f);
    ASSERT_EQ(f.a, 1);
    ASSERT_STREQ(f.b.c_str(), "hello world");
    ASSERT_EQ(f.c.size(), 3);
    ASSERT_EQ(f.c[0], 1);
    ASSERT_EQ(f.c[1], 2);
    ASSERT_EQ(f.c[2], 3);
}

struct CompositeOuter
{
    struct CompositeInner
    {
        int a;
    };
    std::vector<CompositeInner> inners;
};

BEGIN_PROPERTY_MAP(CompositeOuter)
    DEF_PROPERTY(inners)
END_PROPERTY_MAP()

BEGIN_PROPERTY_MAP(CompositeOuter::CompositeInner)
    DEF_PROPERTY(a)
END_PROPERTY_MAP()

TEST(XmlSerializerTests, DeserializeCompositeObjectFromString)
{
    std::string src =
        "<object>"
        "   <inners>"
        "       <item><a>1</a></item>"
        "       <item><a>2</a></item>"
        "   </inners>"
        "</object>";
    CompositeOuter obj;
    src >> XmlSerializer(obj);
    ASSERT_EQ(obj.inners.size(), 2);
    ASSERT_EQ(obj.inners[0].a, 1);
    ASSERT_EQ(obj.inners[1].a, 2);
}

TEST(XmlSerializerTests, NamedBooleanValuesAreSerializedCorrectly)
{
    std::string src;
    bool b;

    src = "<bool>true</bool>";
    b = false;
    src >> XmlSerializer(b);
    ASSERT_TRUE(b);

    src = "<bool>false</bool>";
    b = true;
    src >> XmlSerializer(b);
    ASSERT_FALSE(b);

    src = "<bool>TrUe</bool>";
    b = false;
    src >> XmlSerializer(b);
    ASSERT_TRUE(b);

    src = "<bool>fALse</bool>";
    b = true;
    src >> XmlSerializer(b);
    ASSERT_FALSE(b);
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

TEST(XmlSerializerTests, EnumsCanSerializeByName)
{
    std::string src;
    Color c;

    src = "<enum>Blue</enum>";
    c = Red;
    src >> XmlSerializer(c);
    ASSERT_EQ(Blue, c);
}

TEST(XmlSerializerTests, EnumsCanSerializeByValue)
{
    std::string src;
    Color c;

    src = "<enum>1</enum>";
    c = Red;
    src >> XmlSerializer(c);
    ASSERT_EQ(Blue, c);
}

