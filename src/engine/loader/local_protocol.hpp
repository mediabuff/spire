////////////////////////////////////////////////////////////////////////////////
//  Copyright (C) 2012 Robert Engeln (engeln@gmail.com)
//  See accompanying LICENSE file for full license information.
////////////////////////////////////////////////////////////////////////////////

#ifndef SPIRE_LOADER_LOCAL_PROTOCOL_HPP
#define SPIRE_LOADER_LOCAL_PROTOCOL_HPP

#include "spire/loader/file_protocol.hpp"

namespace spire
{
    namespace core
    {
        ///
        /// FileProtocol implementation for loading files from the local filesystem.
        ///
        class LocalProtocol : public FileProtocol
        {
        public:
            ///
            /// Constructor.
            ///
            LocalProtocol();

            ///
            /// Destructor.
            ///
            virtual ~LocalProtocol();

            ///
            /// From FileProtocol.
            /// @{
            virtual std::unique_ptr<FileProvider> CreateProvider(const char* path);
            //! @}
        };
    }   //  namespace core
}   //  namespace spire

#endif  //  SPIRE_LOADER_LOCAL_PROTOCOL_HPP
