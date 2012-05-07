////////////////////////////////////////////////////////////////////////////////
//  Copyright (C) 2012 Robert Engeln (engeln@gmail.com)
//  See accompanying LICENSE file for full license information.
////////////////////////////////////////////////////////////////////////////////
///
/// @file spire/loader/file_provider.hpp
/// Defines the FileProvider class.
/// @addtogroup loader
/// @{

#ifndef SPIRE_LOADER_FILE_PROVIDER_HPP
#define SPIRE_LOADER_FILE_PROVIDER_HPP

namespace spire
{
    namespace loader
    {
        ///
        /// Encapsulates a source for files.
        ///
        class FileProvider
        {
        public:
            ///
            /// Destructor.
            ///
            virtual ~FileProvider();

            ///
            /// Opens a file.
            ///
            /// @param path Path to the file, relative to the path the provider
            ///             was created from.
            /// @return File object, or null if the file does not exist.
            ///
            virtual std::unique_ptr<File> Open(const char* path) = 0;
        };
    }   //  namespace loader
    using loader::FileProvider;
}   //  namespace spire

#endif  //  SPIRE_LOADER_FILE_PROVIDER_HPP

