////////////////////////////////////////////////////////////////////////////////
//  Copyright (C) 2012 Robert Engeln (engeln@gmail.com)
//  See accompanying LICENSE file for full license information.
////////////////////////////////////////////////////////////////////////////////
///
/// @file spire/loader/file_protocol.hpp
/// Defines the FileProtocol class.
/// @addtogroup loader
/// @{

#ifndef SPIRE_LOADER_FILE_PROTOCOL_HPP
#define SPIRE_LOADER_FILE_PROTOCOL_HPP

namespace spire
{
    namespace loader
    {
        ///
        /// Describes a protocol used to load files.
        ///
        class FileProtocol
        {
        public:
            ///
            /// Destructor.
            ///
            virtual ~FileProtocol();
        };
    }   //  namespace loader
    using loader::FileProtocol;
}   //  namespace spire

#endif  //  SPIRE_LOADER_FILE_PROTOCOL_HPP
