////////////////////////////////////////////////////////////////////////////////
//  Copyright (C) 2012 Robert Engeln (engeln@gmail.com) All rights reserved.
//  See accompanying LICENSE file for full license information.
////////////////////////////////////////////////////////////////////////////////

#include "prefix.hpp"
#include "spire/core/framework.hpp"
#include "spire/core/service.hpp"

using namespace spire;

namespace
{
    class FooServiceInterface : public Service
    {
    public:
        virtual void DoSomething() = 0;
    };

    class FooService : public BasicService<FooServiceInterface>
    {
    public:
        MOCK_METHOD0(DoSomething, void());
    };

    class BarService : public BasicService<FooServiceInterface>
    {
    public:
        MOCK_METHOD0(DoSomething, void());
    };
}

TEST(ServiceTests, ServiceAutoRegistersAndUnregisters)
{
    ASSERT_THROW(GetFramework().Acquire<FooServiceInterface>(),
                 core::ServiceNotFoundError);
    {
        FooService fooSvc;
        EXPECT_CALL(fooSvc, DoSomething()).Times(1);
        GetFramework().Acquire<FooServiceInterface>().DoSomething();
    }
    ASSERT_THROW(GetFramework().Acquire<FooServiceInterface>(),
                 core::ServiceNotFoundError);
}
