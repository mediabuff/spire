////////////////////////////////////////////////////////////////////////////////
//  Copyright (C) 2012 Robert Engeln (engeln@gmail.com) All rights reserved.
//  See accompanying LICENSE file for full license information.
////////////////////////////////////////////////////////////////////////////////

#ifndef SANDBOX_SANDBOX_APPLICATION_HPP
#define SANDBOX_SANDBOX_APPLICATION_HPP

class SandboxApplication : public boost::noncopyable
{
public:
    SandboxApplication();
    ~SandboxApplication();
    int Run();

private:
    void Dispose();
    bool PumpMessageQueue();
    static LRESULT CALLBACK WindowProc(HWND, UINT, WPARAM, LPARAM);

    int m_exitCode;
    HWND m_window;
};

#endif  //  SANDBOX_SANDBOX_APPLICATION_HPP
