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
        };
    }   //  namespace loader
    using loader::FileProvider;
}   //  namespace spire

#endif  //  SPIRE_LOADER_FILE_PROVIDER_HPP

