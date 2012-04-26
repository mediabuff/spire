////////////////////////////////////////////////////////////////////////////////
//  Copyright (C) 2012 Robert Engeln (engeln@gmail.com)
//  See accompanying LICENSE file for full license information.
////////////////////////////////////////////////////////////////////////////////

#include "prefix.hpp"
#include "spire/common/property.hpp"
#include "spire/core/blueprint.hpp"
#include "spire/core/default_blueprint_service.hpp"

using namespace spire;

namespace
{
    struct Foo
    {
        int a;
        int b;
    };

    typedef BlueprintInterface<std::unique_ptr<Foo>(void)> FooBlueprintInterface;

    class FooBlueprint : public BasicBlueprint<FooBlueprint, FooBlueprintInterface>
    {
    public:
        virtual std::unique_ptr<Foo> Construct()
        {
            std::unique_ptr<Foo> ptr(new Foo());
            ptr->a = a;
            ptr->b = b;
            return std::move(ptr);
        }

    private:
        int a;
        int b;

        BEGIN_HOST_PROPERTY_MAP()
            DEF_PROPERTY(a)
            DEF_PROPERTY(b)
        END_HOST_PROPERTY_MAP()
    };
}

TEST(BlueprintTests, aaa)
{
    core::DefaultBlueprintService svc;
    svc.Register("foo", new FooBlueprint());
    
    const char* xml =
        "<blueprints>\n"
        "   <foo name=\"one\">\n"
        "       <b>2</b>\n"
        "   </foo>\n"
        "   <foo name=\"two\">\n"
        "       <a>2</a>\n"
        "       <b>4</b>\n"
        "   </foo>\n"
        "</blueprints>\n";
    std::vector<char> buf;
    buf.resize(strlen(xml) + 1);
    std::copy(xml, xml + strlen(xml) + 1, buf);
    svc.Parse(std::move(buf));

    auto one = svc.Acquire<FooBlueprintInterface>("one").Construct();
    ASSERT_EQ(one.a, 1);
    ASSERT_EQ(one.b, 2);
    auto two = svc.Acquire<FooBlueprintInterface>("two").Construct();
    ASSERT_EQ(two.a, 2);
    ASSERT_EQ(two.b, 4);
}
