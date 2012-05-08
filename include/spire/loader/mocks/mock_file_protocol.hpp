////////////////////////////////////////////////////////////////////////////////
//  Copyright (C) 2012 Robert Engeln (engeln@gmail.com)
//  See accompanying LICENSE file for full license information.
////////////////////////////////////////////////////////////////////////////////
///
/// @file spire/loader/mock_file_provider.hpp
/// Defines the MockFileProvider class.
/// @addtogroup loader
/// @{

#ifndef SPIRE_LOADER_MOCKS_MOCK_FILE_PROTOCOL_HPP
#define SPIRE_LOADER_MOCKS_MOCK_FILE_PROTOCOL_HPP

#include "spire/loader/file_protocol.hpp"

namespace spire
{
    namespace loader
    {
        ///
        /// Mock implementation for FileProtocol.
        ///
        class MockFileProtocol : public FileProtocol
        {
        public:
            MOCK_METHOD1(CreateProvider_, FileProvider*(const char*));

            virtual std::unique_ptr<FileProvider> CreateProvider(const char* str)
            {
                return std::unique_ptr<FileProvider>(CreateProvider_(str));
            }
        };
    }   //  namespace loader
}   //  namespace spire

#endif  //  SPIRE_LOADER_MOCKS_MOCK_FILE_PROTOCOL_HPP
