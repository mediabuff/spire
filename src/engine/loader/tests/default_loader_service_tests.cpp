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
        }
    };

    const Environment* g_env = AddGlobalTestEnvironment(new Init());
}

TEST(DefaultLoaderServiceTests, ProtocolCannotBeRegisteredMoreThanOnce)
{
    auto svc = GetFramework().Acquire<loader::LoaderServiceFactory>("DefaultLoaderService").Construct();
    auto protocol = std::unique_ptr<FileProtocol>();
    svc->RegisterProtocol(std::move(protocol), "mock");
    ASSERT_THROW(svc->RegisterProtocol(std::move(protocol), "mock"),
                 loader::ProtocolAlreadyRegisteredError);
}

