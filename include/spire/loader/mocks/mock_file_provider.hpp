////////////////////////////////////////////////////////////////////////////////
//  Copyright (C) 2012 Robert Engeln (engeln@gmail.com)
//  See accompanying LICENSE file for full license information.
////////////////////////////////////////////////////////////////////////////////
///
/// @file spire/loader/mock_file_provider.hpp
/// Defines the MockFileProvider class.
/// @addtogroup loader
/// @{

#ifndef SPIRE_LOADER_MOCKS_MOCK_FILE_PROVIDER_HPP
#define SPIRE_LOADER_MOCKS_MOCK_FILE_PROVIDER_HPP

#include "spire/loader/file_provider.hpp"

namespace spire
{
    namespace loader
    {
        class File;

        ///
        /// Mock implementation for FileProvider.
        ///
        class MockFileProvider : public FileProvider
        {
        public:
            MOCK_METHOD1(Open_, File*(const char*));

            virtual std::unique_ptr<File> Open(const char* str)
            {
                return std::unique_ptr<File>(Open_(str));
            }
        };
    }   //  namespace loader
}   //  namespace spire

#endif  //  SPIRE_LOADER_MOCKS_MOCK_FILE_PROVIDER_HPP
