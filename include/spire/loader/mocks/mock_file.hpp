////////////////////////////////////////////////////////////////////////////////
//  Copyright (C) 2012 Robert Engeln (engeln@gmail.com)
//  See accompanying LICENSE file for full license information.
////////////////////////////////////////////////////////////////////////////////
///
/// @file spire/loader/mock_file_provider.hpp
/// Defines the MockFileProvider class.
/// @addtogroup loader
/// @{

#ifndef SPIRE_LOADER_MOCKS_MOCK_FILE_HPP
#define SPIRE_LOADER_MOCKS_MOCK_FILE_HPP

#include "spire/loader/file.hpp"

namespace spire
{
    namespace loader
    {
        template <typename T>
        class Mover
        {
        public:
            Mover(T&& obj)
            : m_obj(std::move(obj)), m_valid(true)
            {
            }

            Mover(const Mover<T>& rhs)
            : m_obj(const_cast<T&&>(rhs.m_obj)), m_valid(true)
            {
                assert(rhs.m_valid);
                rhs.m_valid = false;
            }

            Mover& operator=(const Mover& rhs)
            {
                assert(rhs.m_valid);
                m_obj = const_cast<T&&>(rhs.m_obj);
                rhs.m_valid = false;
                m_valid = true;
            }

            bool Valid() const
            {
                return m_valid;
            }

            T& Get()
            {
                assert(m_valid);
                return m_obj;
            }

            const T& Get() const
            {
                assert(m_valid);
                return *m_obj;
            }

        private:
            T m_obj;
            mutable bool m_valid;
        };

        template <typename T>
        inline Mover<T> Movable(T&& obj)
        {
            return Mover<T>(std::move(obj));
        }

        ///
        /// Mock implementation for File.
        ///
        class MockFile : public File
        {
        public:
            MOCK_CONST_METHOD0(Size, size_t());
            MOCK_CONST_METHOD2(Read_, Mover<boost::unique_future<std::vector<char>>>(size_t, size_t));

            virtual boost::unique_future<std::vector<char>> Read(size_t a, size_t b) const
            {
                return std::move(Read_(a, b).Get());
            }
        };
    }   //  namespace loader
}   //  namespace spire

#endif  //  SPIRE_LOADER_MOCKS_MOCK_FILE_HPP
