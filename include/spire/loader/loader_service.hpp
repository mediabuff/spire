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
        /// Error thrown when an attempt to register a protocol fails because
        /// another protocol was already registered under the same name.
        ///
        typedef Error<struct _ProtocolAlreadyRegisteredError, RuntimeError> ProtocolAlreadyRegisteredError;

        ///
        /// Error thrown when an attempt to open a file fails because the
        /// protocol specified in the file's URI has not been registered.
        ///
        typedef Error<struct _ProtocolNotFoundError, RuntimeError> ProtocolNotFoundError;

        ///
        /// Error thrown when a URI cannot be processed because it is malformed.
        ///
        typedef Error<struct _MalformedUriError, RuntimeError> MalformedUriError;

        ///
        /// Error thrown when an attempt to open a file fails because none of the
        /// providers supplied a file with the given path.
        ///
        typedef Error<struct _FileNotFoundError, RuntimeError> FileNotFoundError;

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
            /// @return Reference to the FileProvider instance; may be passed to
            ///         Unmount to reverse this operation.
            ///
            virtual FileProvider& Mount(const char* uri,
                                        const char* mount) = 0;
         
            ///
            /// Unmounts a FileProvider.
            ///
            /// @param provider FileProvider instance returned from a previous
            ///                 call to Mount().
            ///
            virtual void Unmount(FileProvider& provider) = 0;

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
