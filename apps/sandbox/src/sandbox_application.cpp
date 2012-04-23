////////////////////////////////////////////////////////////////////////////////
//  Copyright (C) 2012 Robert Engeln (engeln@gmail.com) All rights reserved.
//  See accompanying LICENSE file for full license information.
////////////////////////////////////////////////////////////////////////////////

#include "prefix.hpp"
#include "sandbox_application.hpp"
#include "spire/core/framework.hpp"

const TCHAR* WindowClass = _T("SpireClient");
const TCHAR* WindowTitle = _T("Spire");
const size_t WindowWidth = 1024;
const size_t WindowHeight = 768;
const DWORD WindowStyle = WS_OVERLAPPEDWINDOW ^ WS_SIZEBOX;

SandboxApplication::SandboxApplication()
: m_window(nullptr),
  m_exitCode(0)
{
    try
    {
        WNDCLASSEX wc;
        ZeroMemory(&wc, sizeof(wc));
        wc.cbSize = sizeof(wc);
        wc.hInstance = GetModuleHandle(NULL);
        wc.lpfnWndProc = WindowProc;
        wc.lpszClassName = WindowClass;
        wc.style = CS_OWNDC;
        WIN_CHECK(RegisterClassEx(&wc));

        RECT wndRect = {0, 0, WindowWidth, WindowHeight};
        AdjustWindowRect(&wndRect, WindowStyle, false);

        WIN_CHECK(m_window = CreateWindow(WindowClass,
                                          WindowTitle,
                                          WindowStyle,
                                          CW_USEDEFAULT,
                                          CW_USEDEFAULT,
                                          wndRect.right - wndRect.left,
                                          wndRect.bottom - wndRect.top,
                                          NULL,
                                          NULL,
                                          GetModuleHandle(NULL),
                                          NULL));
        ShowWindow(m_window, SW_SHOW);
        SetWindowLongPtr(m_window,
                         GWLP_USERDATA,
                         reinterpret_cast<LONG>(this));

        spire::GetFramework();
    }
    catch (spire::Exception&)
    {
        Dispose();
        throw;
    }
}

SandboxApplication::~SandboxApplication()
{
    Dispose();
}

void SandboxApplication::Dispose()
{
    if (m_window)
    {
        DestroyWindow(m_window);
        m_window = nullptr;
    }
}

int SandboxApplication::Run()
{
    while (PumpMessageQueue())
    {
    }
    return m_exitCode;
}

bool SandboxApplication::PumpMessageQueue()
{
    MSG msg;
    while (PeekMessage(&msg, 0, 0, 0, PM_REMOVE))
    {
        if (msg.message == WM_QUIT)
        {
            m_exitCode = static_cast<int>(msg.wParam);
            return false;
        }
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }
    return true;
}

LRESULT CALLBACK SandboxApplication::WindowProc(HWND hwnd,
                                               UINT msg,
                                               WPARAM wparam,
                                               LPARAM lparam)
{
    SandboxApplication* app = reinterpret_cast<SandboxApplication*>
        (GetWindowLongPtr(hwnd, GWLP_USERDATA));

    switch (msg)
    {
    case WM_CLOSE: 
        {
            PostQuitMessage(0);
            return 0;
        }
    default:
        {
            return DefWindowProc(hwnd, msg, wparam, lparam);
        }
    }
}

int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int)
{
    try
    {
        SandboxApplication app;
        return app.Run();
    }
    catch (spire::Exception& e)
    {
        std::string info = boost::diagnostic_information(e);
        OutputDebugStringA("Exception caught:\n");
        OutputDebugStringA(info.c_str());
        OutputDebugStringA("\n\n");
        MessageBoxA(NULL, info.c_str(), "A fatal error has occured", MB_OK | MB_ICONERROR);
        return -1;
    }
}