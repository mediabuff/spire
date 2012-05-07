////////////////////////////////////////////////////////////////////////////////
//  Copyright (C) 2012 Robert Engeln (engeln@gmail.com)
//  See accompanying LICENSE file for full license information.
////////////////////////////////////////////////////////////////////////////////
///
/// @file spire/loader/loader_service.hpp
/// Defines the LoaderService class.
/// @addtogroup loader
/// @{

#ifndef SPIRE_LOADER_LOADER_SERVICE_HPP
#define SPIRE_LOADER_LOADER_SERVICE_HPP

#include "spire/core/service.hpp"

namespace spire
{
    namespace loader
    {
        class FileProtocol;
        class File;

        ///
        /// Manages the virtual filesystem.
        ///
        class LoaderService : public Service
        {
        public:
            ///
            /// Destructor.
            ///
            virtual ~LoaderService() = 0;

            ///
            /// Registers a protocol.
            ///
            /// @param protocol Protocol instance; the LoaderService will take
            ///                 ownership.
            /// @param name Protocol string.
            ///
            virtual void RegisterProtocol(std::unique_ptr<FileProtocol> protocol,
                                          const char* name) = 0;

            ///
            /// Mounts a file source into the virtual file system.
            ///
            /// @param uri URI to mount; the protocol must have previously been
            ///            registered via RegisterProtocol.
            /// @param mount Mount point in the virtual filesystem.
            ///
            virtual void Mount(const char* uri,
                               const char* mount) = 0;
         
            ///
            /// Opens a file.
            ///
            /// @param path Path (in the virtual filesystem) to the file.
            /// @return File object which can be used for reading.
            ///
            virtual std::shared_ptr<File> Open(const char* path) = 0;
        };

        ///
        /// Factory interface for constructing LoaderService instances.
        ///
        typedef FactoryInterface<std::unique_ptr<LoaderService>()> LoaderServiceFactory;
    }   //  namespace loader
    using loader::LoaderService;
}   //  namespace spire

#endif  //  SPIRE_LOADER_LOADER_SERVICE_HPP
