////////////////////////////////////////////////////////////////////////////////
//  Copyright (C) 2012 Robert Engeln (engeln@gmail.com)
//  See accompanying LICENSE file for full license information.
////////////////////////////////////////////////////////////////////////////////
///
/// @file spire/loader/default_loader_service.hpp
/// Defines the DefaultLoaderService class.
/// @addtogroup loader
/// @{

#ifndef SPIRE_LOADER_DEFAULT_LOADER_SERVICE_HPP
#define SPIRE_LOADER_DEFAULT_LOADER_SERVICE_HPP

#include "spire/loader/loader_service.hpp"

namespace spire
{
    namespace loader
    {       
        class FileProvider;

        ///
        /// Default implementation of LoaderService.
        ///
        class DefaultLoaderService : public BasicService<LoaderService>
        {
        public:
            ///
            /// Constructor.
            ///
            DefaultLoaderService();

            ///
            /// Destructor.
            ///
            virtual ~DefaultLoaderService();

            ///
            /// From LoaderService.
            ///
            /// @{
            virtual void RegisterProtocol(std::unique_ptr<FileProtocol> protocol,
                                          const char* name);
            virtual FileProvider& Mount(const char* uri,
                                        const char* mount);
            virtual void Unmount(FileProvider& provider);
            virtual std::shared_ptr<File> Open(const char* path);
            //! @}

        private:
            std::map<std::string, std::unique_ptr<FileProtocol>> m_protocols;
            std::vector<std::pair<std::string, std::unique_ptr<FileProvider>>> m_providers;
        };
    }   //  namespace loader
}   //  namespace spire

#endif  //  SPIRE_LOADER_DEFAULT_LOADER_SERVICE_HPP
