////////////////////////////////////////////////////////////////////////////////
//  Copyright (C) 2012 Robert Engeln (engeln@gmail.com)
//  See accompanying LICENSE file for full license information.
////////////////////////////////////////////////////////////////////////////////

#include "prefix.hpp"
#include "spire/core/framework.hpp"
#include "spire/loader/loader_service.hpp"
#include "spire/loader/mocks/mock_file_protocol.hpp"
#include "spire/loader/mocks/mock_file_provider.hpp"
#include "spire/loader/mocks/mock_file.hpp"

using namespace spire;
using namespace testing;

namespace
{
    class Init : public Environment
    {
    public:
        virtual void SetUp()
        {
            GetFramework().LoadModule("spire_loader");
			GetFramework().Acquire<loader::LoaderServiceFactory>("DefaultLoaderService").Construct();

        }
    };

    const Environment* g_env = AddGlobalTestEnvironment(new Init());

	class DefaultLoaderServiceTests : public Test
	{
	public:
		virtual void SetUp()
		{
			loaderService = GetFramework().Acquire<loader::LoaderServiceFactory>
				("DefaultLoaderService").Construct();
		}

		std::unique_ptr<LoaderService> loaderService;
	};
}

TEST_F(DefaultLoaderServiceTests, ProtocolCannotBeRegisteredMoreThanOnce)
{
    auto protocol = std::unique_ptr<FileProtocol>();
    loaderService->RegisterProtocol(std::move(protocol), "mock");
    ASSERT_THROW(loaderService->RegisterProtocol(std::move(protocol), "mock"),
                 loader::ProtocolAlreadyRegisteredError);
}


TEST_F(DefaultLoaderServiceTests, MountMalformedUriThrowsException)
{
    auto mockProtocol = std::make_shared<loader::MockFileProtocol>();
    ASSERT_THROW(loaderService->Mount("", ""), loader::MalformedUriError);
    ASSERT_THROW(loaderService->Mount("abc", ""), loader::MalformedUriError);
    ASSERT_THROW(loaderService->Mount("abc:", ""), loader::MalformedUriError);
    ASSERT_THROW(loaderService->Mount(":abc", ""), loader::MalformedUriError);
    ASSERT_THROW(loaderService->Mount(":abc:", ""), loader::MalformedUriError);
}

TEST_F(DefaultLoaderServiceTests, MountSingleProvider)
{
	auto mockProvider = new loader::MockFileProvider();
	auto mockProtocol = new loader::MockFileProtocol();
	auto mockFile = new loader::MockFile();

    EXPECT_CALL(*mockProtocol, CreateProvider_(StrEq("this_is_a_test/")))
        .WillOnce(Return(mockProvider));
    EXPECT_CALL(*mockProvider, Open_(StrEq("b/abc.txt")))
        .WillOnce(Return(mockFile));

    loaderService->RegisterProtocol(std::unique_ptr<FileProtocol>(mockProtocol),
									"mock");
    loaderService->Mount("mock://this_is_a_test/", "a/");

    auto result = loaderService->Open("a/b/abc.txt");
    ASSERT_EQ(result.get(), mockFile);
}

TEST_F(DefaultLoaderServiceTests, UnmountSingleProvider)
{
    auto mockProvider = new loader::MockFileProvider();
    auto mockProtocol = new loader::MockFileProtocol();

    EXPECT_CALL(*mockProtocol, CreateProvider_(StrEq("this_is_a_test/")))
        .WillOnce(Return(mockProvider));
    EXPECT_CALL(*mockProvider, Open_(_))
        .Times(0);

    loaderService->RegisterProtocol(std::unique_ptr<FileProtocol>(mockProtocol), "mock");

    auto& providerRef = loaderService->Mount("mock://this_is_a_test/", "");
	ASSERT_EQ(static_cast<loader::MockFileProvider*>(&providerRef), mockProvider);
	loaderService->Unmount(providerRef);

    ASSERT_THROW(loaderService->Open("abc.txt"), loader::FileNotFoundError);
}

TEST_F(DefaultLoaderServiceTests, ProvidersAreSearchedInExpectedOrder)
{
    auto mockProvider1 = new loader::MockFileProvider();
    auto mockProvider2 = new loader::MockFileProvider();
    auto mockProtocol = new loader::MockFileProtocol();
    auto mockFile = new loader::MockFile();

    EXPECT_CALL(*mockProtocol, CreateProvider_(StrEq("one/")))
        .WillOnce(Return(mockProvider1));
    EXPECT_CALL(*mockProtocol, CreateProvider_(StrEq("two/")))
        .WillOnce(Return(mockProvider2));
    EXPECT_CALL(*mockProvider1, Open_(StrEq("abc.txt")))
        .WillOnce(Return(mockFile));
    EXPECT_CALL(*mockProvider2, Open_(StrEq("abc.txt")))
        .WillOnce(Return(nullptr));

    loaderService->RegisterProtocol(std::unique_ptr<FileProtocol>(mockProtocol),
									"mock");
    loaderService->Mount("mock://one/", "");
    loaderService->Mount("mock://two/", "");

    auto result = loaderService->Open("abc.txt");
    ASSERT_EQ(result.get(), mockFile);
}
