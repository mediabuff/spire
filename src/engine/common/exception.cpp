////////////////////////////////////////////////////////////////////////////////
//  Copyright (C) 2012 Robert Engeln (engeln@gmail.com) All rights reserved.
//  See accompanying LICENSE file for full license information.
////////////////////////////////////////////////////////////////////////////////

#include "prefix.hpp"

using namespace spire;
using namespace common;

Exception::Exception(std::string msg)
: m_message(std::move(msg))
{
}

Exception::Exception(const Exception& rhs)
: m_message(rhs.m_message)
{
}

Exception::Exception(Exception&& rhs)
: m_message(std::move(rhs.m_message))
{
}

Exception::~Exception()
{
}

Exception& Exception::operator<<(const std::string& msg)
{
    m_message.append("\n");
    m_message.append(msg);
    return *this;
}

Exception& Exception::operator<<(const boost::format& msg)
{
    return *this << msg.str();
}

const char* Exception::what() const throw()
{
    return m_message.c_str();

}
