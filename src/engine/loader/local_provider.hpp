////////////////////////////////////////////////////////////////////////////////
//  Copyright (C) 2012 Robert Engeln (engeln@gmail.com)
//  See accompanying LICENSE file for full license information.
////////////////////////////////////////////////////////////////////////////////

#ifndef SPIRE_LOADER_LOCAL_PROVIDER_HPP
#define SPIRE_LOADER_LOCAL_PROVIDER_HPP

#include "spire/loader/file_provider.hpp"

namespace spire
{
    namespace loader
    {
        ///
        /// Implementation of FileProvider mapping to a directory in the
        /// local system (associated with LocalProtocol.)
        ///
        class LocalProvider : public FileProvider
        {
        public:
            ///
            /// Constructor.
            ///
            /// @param path Root path in the local filesystem.
            ///
            LocalProvider(const char* path);

            ///
            /// Destructor.
            ///
            virtual ~LocalProvider();

            ///
            /// From FileProvider.
            /// @{
            virtual std::unique_ptr<File> Open(const char* path);
            //! @}
        };
    }   //  namespace loader
}   //  namespace spire

#endif  //  SPIRE_LOADER_LOCAL_PROVIDER_HPP
