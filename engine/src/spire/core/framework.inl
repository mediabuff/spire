////////////////////////////////////////////////////////////////////////////////
//  Copyright (C) 2012 Robert Engeln (engeln@gmail.com) All rights reserved.
//  See accompanying LICENSE file for full license information.
////////////////////////////////////////////////////////////////////////////////
///
/// @file spire/core/framework.inl
/// Inline functions for the Framework class.
/// @addtogroup core
/// @{

#ifndef SPIRE_CORE_FRAMEWORK_INL
#define SPIRE_CORE_FRAMEWORK_INL

namespace spire
{
    namespace core
    {
        template <typename T>
        inline void Framework::Register(Service* svcPtr)
        {
            RegisterService(typeid(T).name(), svcPtr);
        }

        template <typename T>
        inline T& Framework::Acquire()
        {
            Service& svc = AcquireService(typeid(T).name());
            return *static_cast<T*>(&svc);
        }

        template <typename T>
        inline T& Framework::Acquire(const std::string& name)
        {
            Factory& factory = AcquireFactory(name);
            T* ptr = dynamic_cast<T*>(&factory);
            if (!ptr)
            {
                throw FactoryTypeError(boost::format("Type not supported for factory \"%s\"")
                                       % name);
            }
            return *ptr;
        }
    }   //  namespace core
}   //  namespace spire

#endif  //  SPIRE_CORE_FRAMEWORK_INL

