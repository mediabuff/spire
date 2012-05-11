////////////////////////////////////////////////////////////////////////////////
//  Copyright (C) 2012 Robert Engeln (engeln@gmail.com)
//  See accompanying LICENSE file for full license information.
////////////////////////////////////////////////////////////////////////////////

#ifndef SPIRE_LOADER_LOCAL_FILE_HPP
#define SPIRE_LOADER_LOCAL_FILE_HPP

#include "spire/loader/file.hpp"

namespace spire
{
    namespace loader
    {
        ///
        /// Implementation of File for direct reading from a file in the
        /// local filesystem.
        ///
        class LocalFile : public File
        {
        public:
            ///
            /// Constructor.
            ///
            /// @param path Path to the file.
            ///
            LocalFile(const char* path);

            ///
            /// Destructor.
            ///
            virtual ~LocalFile();

            ///
            /// From File.
            /// @{
            virtual size_t Size() const;
            virtual boost::unique_future<std::vector<char>> Read(size_t offset, size_t count) const;
            //! @}
        };
    }   //  namespace loader
}   //  namespace spire

#endif  //  SPIRE_LOADER_LOCAL_FILE_HPP
