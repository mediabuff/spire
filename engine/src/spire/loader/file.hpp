////////////////////////////////////////////////////////////////////////////////
//  Copyright (C) 2012 Robert Engeln (engeln@gmail.com)
//  See accompanying LICENSE file for full license information.
////////////////////////////////////////////////////////////////////////////////
///
/// @file spire/loader/file.hpp
/// Defines the File class.
/// @addtogroup loader
/// @{

#ifndef SPIRE_LOADER_FILE_HPP
#define SPIRE_LOADER_FILE_HPP

namespace spire
{
    namespace loader
    {
        ///
        /// Encapsulates a file for reading.
        ///
        class File
        {
        public:
            ///
            /// Destructor.
            ///
            virtual ~File() = 0 { };

            ///
            /// Returns the size of the file in bytes.
            ///
            virtual size_t Size() const = 0;

            ///
            /// Reads data from the file.
            ///
            /// @param offset Offset to begin reading at.
            /// @param count Maximum number of bytes to read.
            /// @return Future containing a vector holding the read data, or
            ///         an exception if an error occured.
            /// 
            virtual boost::unique_future<std::vector<char>> Read(size_t offset, size_t count) const = 0;
        };
    }   //  namespace loader
}   //  namespace spire

#endif  //  SPIRE_LOADER_FILE_HPP
