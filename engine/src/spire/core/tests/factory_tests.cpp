////////////////////////////////////////////////////////////////////////////////
//  Copyright (C) 2012 Robert Engeln (engeln@gmail.com) All rights reserved.
//  See accompanying LICENSE file for full license information.
////////////////////////////////////////////////////////////////////////////////

#include "prefix.hpp"
#include "spire/core/factory.hpp"
#include "spire/core/framework.hpp"

using namespace spire;

namespace
{
    class FooInterface
    {
    public:
        virtual ~FooInterface() = 0 { };
        virtual bool IsFoo() const = 0;
        virtual int GetValue() const = 0;
    };

    class FakeInterface
    {
    public:
        virtual ~FakeInterface() = 0 { };
    };

    typedef FactoryInterface<std::unique_ptr<FooInterface>(int)> FooFactory;
    typedef FactoryInterface<std::unique_ptr<FakeInterface>(int)> FakeFactory;

    class Foo : public FooInterface
    {
    public:
        int m_value;

        Foo(int value)
        : m_value(value)
        {
        }

        virtual ~Foo()
        {
        }

        virtual bool IsFoo() const
        {
            return true;
        }

        virtual int GetValue() const
        {
            return m_value;
        }
    };

    class Bar : public FooInterface
    {
    public:
        int m_value;

        Bar(int value)
        : m_value(value)
        {
        }

        virtual ~Bar()
        {
        }

        virtual bool IsFoo() const
        {
            return false;
        }

        virtual int GetValue() const
        {
            return m_value;
        }
    };
}

class FactoryTests : public testing::Test
{
public:
    FactoryTests()
    {
        GetFramework().Register(std::unique_ptr<Factory>(new BasicFactory<Foo, FooFactory>()),
                                "foo");
        GetFramework().Register(std::unique_ptr<Factory>(new BasicFactory<Bar, FooFactory>()),
                                "bar");
    }

    ~FactoryTests()
    {
        GetFramework().Register(std::unique_ptr<Factory>(), "foo");
        GetFramework().Register(std::unique_ptr<Factory>(), "bar");
    }
};

TEST_F(FactoryTests, RegisteredFactoriesCanBeAcquired)
{
    std::unique_ptr<FooInterface> a = GetFramework().Acquire<FooFactory>("foo").Construct(1);
    ASSERT_TRUE(a->IsFoo());
    ASSERT_EQ(a->GetValue(), 1);
    std::unique_ptr<FooInterface> b = GetFramework().Acquire<FooFactory>("bar").Construct(2);
    ASSERT_FALSE(b->IsFoo());
    ASSERT_EQ(b->GetValue(), 2);
}

TEST_F(FactoryTests, ErrorIsThrownWhenFactoryIsNotRegistered)
{
    ASSERT_THROW(GetFramework().Acquire<FooFactory>("fake"),
                 core::FactoryNotFoundError);
}

TEST_F(FactoryTests, ErrorIsThrownWhenFactoryDoesNotImplementRequestedInterface)
{
    ASSERT_THROW(GetFramework().Acquire<FakeFactory>("foo"),
                 core::FactoryTypeError);
}
