//-----------------------------------------------------------------------------
// Copyright (c) 2009-2012 dhpoware. All Rights Reserved.
//
// Permission is hereby granted, free of charge, to any person obtaining a
// copy of this software and associated documentation files (the "Software"),
// to deal in the Software without restriction, including without limitation
// the rights to use, copy, modify, merge, publish, distribute, sublicense,
// and/or sell copies of the Software, and to permit persons to whom the
// Software is furnished to do so, subject to the following conditions:
//
// The above copyright notice and this permission notice shall be included in
// all copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS
// OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
// FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS
// IN THE SOFTWARE.
//-----------------------------------------------------------------------------

#pragma comment (lib, "gdiplus.lib")

#include <windows.h>
#include <gdiplus.h>
#include <algorithm>
#include <cctype>
#include <cmath>
#include <cstdlib>
#include <cstring>
#include <exception>
#include <fstream>
#include <functional>
#include <string>
#include <sstream>

#if defined(DEBUG) || defined(_DEBUG)
#include <crtdbg.h>
#endif

#include "application.h"
#include "texture.h"

namespace dhpoware {

const float GL3Application::MAXIMUM_FRAME_RATE = 60.0f;
const float GL3Application::MINIMUM_FRAME_RATE = 15.0f;
const float GL3Application::UPDATE_INTERVAL = 1.0f / GL3Application::MAXIMUM_FRAME_RATE;
const float GL3Application::MAX_CYCLES_PER_FRAME = GL3Application::MAXIMUM_FRAME_RATE / GL3Application::MINIMUM_FRAME_RATE;

const int GL3Application::ATTRIB_LIST_GL_VERSION_3_0[] =
{
	WGL_CONTEXT_MAJOR_VERSION_ARB, 3,
	WGL_CONTEXT_MINOR_VERSION_ARB, 0,
	WGL_CONTEXT_FLAGS_ARB, WGL_CONTEXT_FORWARD_COMPATIBLE_BIT_ARB,
	0
};

const int GL3Application::ATTRIB_LIST_GL_VERSION_3_1[] =
{
	WGL_CONTEXT_MAJOR_VERSION_ARB, 3,
	WGL_CONTEXT_MINOR_VERSION_ARB, 1,
	WGL_CONTEXT_FLAGS_ARB, WGL_CONTEXT_FORWARD_COMPATIBLE_BIT_ARB,
	0
};

const int GL3Application::ATTRIB_LIST_GL_VERSION_3_2[] =
{
	WGL_CONTEXT_MAJOR_VERSION_ARB, 3,
	WGL_CONTEXT_MINOR_VERSION_ARB, 2,
	WGL_CONTEXT_FLAGS_ARB, WGL_CONTEXT_FORWARD_COMPATIBLE_BIT_ARB,
	WGL_CONTEXT_PROFILE_MASK_ARB, WGL_CONTEXT_CORE_PROFILE_BIT_ARB,
	0
};

const int GL3Application::ATTRIB_LIST_GL_VERSION_3_3[] =
{
	WGL_CONTEXT_MAJOR_VERSION_ARB, 3,
	WGL_CONTEXT_MINOR_VERSION_ARB, 3,
	WGL_CONTEXT_FLAGS_ARB, WGL_CONTEXT_FORWARD_COMPATIBLE_BIT_ARB,
	WGL_CONTEXT_PROFILE_MASK_ARB, WGL_CONTEXT_CORE_PROFILE_BIT_ARB,
	0
};

const int GL3Application::ATTRIB_LIST_GL_VERSION_4_0[] =
{
	WGL_CONTEXT_MAJOR_VERSION_ARB, 4,
	WGL_CONTEXT_MINOR_VERSION_ARB, 0,
	WGL_CONTEXT_FLAGS_ARB, WGL_CONTEXT_FORWARD_COMPATIBLE_BIT_ARB,
	WGL_CONTEXT_PROFILE_MASK_ARB, WGL_CONTEXT_CORE_PROFILE_BIT_ARB,
	0
};

const int GL3Application::ATTRIB_LIST_GL_VERSION_4_1[] =
{
	WGL_CONTEXT_MAJOR_VERSION_ARB, 4,
	WGL_CONTEXT_MINOR_VERSION_ARB, 1,
	WGL_CONTEXT_FLAGS_ARB, WGL_CONTEXT_FORWARD_COMPATIBLE_BIT_ARB,
	WGL_CONTEXT_PROFILE_MASK_ARB, WGL_CONTEXT_CORE_PROFILE_BIT_ARB,
	0
};

const int GL3Application::ATTRIB_LIST_GL_VERSION_4_2[] =
{
	WGL_CONTEXT_MAJOR_VERSION_ARB, 4,
	WGL_CONTEXT_MINOR_VERSION_ARB, 2,
	WGL_CONTEXT_FLAGS_ARB, WGL_CONTEXT_FORWARD_COMPATIBLE_BIT_ARB,
	WGL_CONTEXT_PROFILE_MASK_ARB, WGL_CONTEXT_CORE_PROFILE_BIT_ARB,
	0
};

const int * const GL3Application::ATTRIB_LISTS[] =
{
	GL3Application::ATTRIB_LIST_GL_VERSION_3_0,
	GL3Application::ATTRIB_LIST_GL_VERSION_3_1,
	GL3Application::ATTRIB_LIST_GL_VERSION_3_2,
	GL3Application::ATTRIB_LIST_GL_VERSION_3_3,
	GL3Application::ATTRIB_LIST_GL_VERSION_4_0,
	GL3Application::ATTRIB_LIST_GL_VERSION_4_1,
	GL3Application::ATTRIB_LIST_GL_VERSION_4_2
};

Mouse &GL3Application::m_mouse = Mouse::instance();
Keyboard &GL3Application::m_keyboard = Keyboard::instance();
INT64 GL3Application::m_freq;
INT64 GL3Application::m_lastTime;
int   GL3Application::m_sampleCount;
float GL3Application::m_timeScale;
float GL3Application::m_actualElapsedTimeSec;
float GL3Application::m_frameTimes[MAX_SAMPLE_COUNT];
bool  GL3Application::m_initialized;

//-----------------------------------------------------------------------------
// Public methods.
//-----------------------------------------------------------------------------

GL3Application::GL3Application()
{
    initApplication("");
}

GL3Application::GL3Application(const char *pszWindowName)
{
    initApplication(pszWindowName);
}

GL3Application::~GL3Application()
{
}

void GL3Application::preferAnisotropicTextureFiltering()
{
	Texture2D::preferAnisotropicTextureFiltering();
}

void GL3Application::preferAnisotropicTextureFiltering(int degreeOfAnisotrophy)
{
    Texture2D::preferAnisotropicTextureFiltering(degreeOfAnisotrophy);
}

void GL3Application::preferAntiAliasing()
{
    m_antiAliasingSamples = BEST_ANTI_ALIASING_SAMPLES;
}

void GL3Application::preferAntiAliasing(int samples)
{
    m_antiAliasingSamples = samples;
}

void GL3Application::preferFullScreen()
{
    m_startFullScreen = true;
}

void GL3Application::preferOpenGLVersion(GLVersion version)
{
	m_preferredGLVersion = version;
}

void GL3Application::preferWindowed()
{
    m_startFullScreen = false;
}

int GL3Application::run()
{
#if defined(DEBUG) | defined(_DEBUG)
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
#endif

    int status = 0;
    ULONG_PTR gdiplusToken = 0;
	
	Gdiplus::GdiplusStartupInput gdiplusStartupInput;
    Gdiplus::GdiplusStartup(&gdiplusToken, &gdiplusStartupInput, 0);

    try
    {
        if (create())
        {
            try
            {
                initOpenGL();
                init(__argc, __argv);                
                status = mainLoop();
                shutdown();
            }
            catch (...)
            {
                shutdown();
                throw;
            }
            
            destroy();
        }
    }
    catch (const std::exception &e)
    {
        destroy();
        status = EXIT_FAILURE;
		MessageBox(0, e.what(), "GL3Application Unhandled Exception", MB_ICONERROR);
    }

    Gdiplus::GdiplusShutdown(gdiplusToken);

    return status;
}

//-----------------------------------------------------------------------------
// Protected methods.
//-----------------------------------------------------------------------------

void GL3Application::displayFullScreen()
{
    if (!m_isFullScreen)
        toggleFullScreen();
}

void GL3Application::displayWindowed()
{
    if (m_isFullScreen)
        toggleFullScreen();
}

void GL3Application::enableVerticalSync(bool enableVerticalSync)
{
    wglSwapIntervalEXT(enableVerticalSync ? 1 : 0);
}

void GL3Application::quit(int status)
{
    m_status = status;
    PostMessage(m_hWnd, WM_CLOSE, 0, 0);
}

void GL3Application::toggleFullScreen()
{
    m_isFullScreen = !m_isFullScreen;

    if (m_isFullScreen)
    {
        // Moving to full screen mode.

        m_savedExStyle = GetWindowLong(m_hWnd, GWL_EXSTYLE);
        m_savedStyle = GetWindowLong(m_hWnd, GWL_STYLE);
        GetWindowRect(m_hWnd, &m_rcSaved);

        SetWindowLong(m_hWnd, GWL_EXSTYLE, 0);
        SetWindowLong(m_hWnd, GWL_STYLE, WS_POPUP | WS_CLIPCHILDREN | WS_CLIPSIBLINGS);
        SetWindowPos(m_hWnd, HWND_TOPMOST, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE | SWP_FRAMECHANGED | SWP_SHOWWINDOW);

        m_windowWidth = GetSystemMetrics(SM_CXSCREEN);
        m_windowHeight = GetSystemMetrics(SM_CYSCREEN);

        SetWindowPos(m_hWnd, HWND_TOPMOST, 0, 0, m_windowWidth, m_windowHeight, SWP_SHOWWINDOW);
    }
    else
    {
        // Moving back to windowed mode.

        SetWindowLong(m_hWnd, GWL_EXSTYLE, m_savedExStyle);
        SetWindowLong(m_hWnd, GWL_STYLE, m_savedStyle);
        SetWindowPos(m_hWnd, HWND_NOTOPMOST, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE | SWP_FRAMECHANGED | SWP_SHOWWINDOW);

        m_windowWidth = m_rcSaved.right - m_rcSaved.left;
        m_windowHeight = m_rcSaved.bottom - m_rcSaved.top;

        SetWindowPos(m_hWnd, HWND_NOTOPMOST, m_rcSaved.left, m_rcSaved.top, m_windowWidth, m_windowHeight, SWP_SHOWWINDOW);
    }
}

bool GL3Application::verticalSyncEnabled() const
{
    return (wglGetSwapIntervalEXT() == 0) ? false : true;
}

//-----------------------------------------------------------------------------
// Private methods.
//-----------------------------------------------------------------------------

bool GL3Application::create()
{      
    if (!RegisterClassEx(&m_wcl))
        return false;

    // Create a window that is centered on the desktop. It's exactly 1/4 the
    // size of the desktop. Don't allow it to be resized.

    DWORD wndExStyle = WS_EX_OVERLAPPEDWINDOW;
    DWORD wndStyle = WS_OVERLAPPED | WS_CAPTION | WS_SYSMENU | WS_MINIMIZEBOX | WS_CLIPCHILDREN | WS_CLIPSIBLINGS;

    m_hWnd = CreateWindowEx(wndExStyle, m_wcl.lpszClassName, m_pszWindowName, wndStyle, 0, 0, 0, 0, 0, 0, m_wcl.hInstance, this);

    if (!m_hWnd)
    {
        UnregisterClass(m_wcl.lpszClassName, m_hInstance);
        return false;
    }
    else
    {
        int screenWidth = GetSystemMetrics(SM_CXSCREEN);
        int screenHeight = GetSystemMetrics(SM_CYSCREEN);
        int halfScreenWidth = screenWidth / 2;
        int halfScreenHeight = screenHeight / 2;
        int left = (screenWidth - halfScreenWidth) / 2;
        int top = (screenHeight - halfScreenHeight) / 2;
        RECT rc = {0};

        SetRect(&rc, left, top, left + halfScreenWidth, top + halfScreenHeight);
        AdjustWindowRectEx(&rc, wndStyle, FALSE, wndExStyle);
        MoveWindow(m_hWnd, rc.left, rc.top, rc.right - rc.left, rc.bottom - rc.top, TRUE);

        GetClientRect(m_hWnd, &rc);
        m_windowWidth = rc.right - rc.left;
        m_windowHeight = rc.bottom - rc.top;   

        return true;
    }
}

void GL3Application::destroy()
{
    if (m_hDC)
    {
        if (m_hRC)
        {
            wglMakeCurrent(m_hDC, 0);
            wglDeleteContext(m_hRC);
            m_hRC = 0;
        }

        ReleaseDC(m_hWnd, m_hDC);
        m_hDC = 0;
    }
    
    UnregisterClass(m_wcl.lpszClassName, m_hInstance);
}

void GL3Application::initOpenGL()
{
    if (!(m_hDC = GetDC(m_hWnd)))
        throw std::runtime_error("GetDC() failed.");

    int pf = 0;
    PIXELFORMATDESCRIPTOR pfd = {0};
    OSVERSIONINFO osvi = {0};

    // Create and set a pixel format for the window.

    pfd.nSize = sizeof(pfd);
    pfd.nVersion = 1;
    pfd.dwFlags = PFD_DRAW_TO_WINDOW | PFD_SUPPORT_OPENGL | PFD_DOUBLEBUFFER;
    pfd.iPixelType = PFD_TYPE_RGBA;
    pfd.cColorBits = 24;
    pfd.cDepthBits = 16;
    pfd.iLayerType = PFD_MAIN_PLANE;

    osvi.dwOSVersionInfoSize = sizeof(OSVERSIONINFO);

    if (!GetVersionEx(&osvi))
        throw std::runtime_error("GetVersionEx() failed.");

    if (m_antiAliasingSamples == 0)
        pf = ChoosePixelFormat(m_hDC, &pfd);
    else if (m_antiAliasingSamples == BEST_ANTI_ALIASING_SAMPLES)
        gl::ChooseBestAntiAliasingPixelFormat(pf);
    else
        gl::ChooseAntiAliasingPixelFormat(pf, m_antiAliasingSamples);

    if (!pf)
        pf = ChoosePixelFormat(m_hDC, &pfd);

    if (!SetPixelFormat(m_hDC, pf, &pfd))
        throw std::runtime_error("SetPixelFormat() failed.");

    // When running under Windows Vista or later support desktop composition.
    // This doesn't really apply when running in full screen mode.

    if (osvi.dwMajorVersion > 6 || (osvi.dwMajorVersion == 6 && osvi.dwMinorVersion >= 0))
        pfd.dwFlags |= PFD_SUPPORT_COMPOSITION;

    // Verify that this OpenGL implementation supports the required extensions.

	if (!gl::ExtensionSupported("WGL_ARB_create_context"))
        throw std::runtime_error("Required extension WGL_ARB_create_context is not supported.");
    
	// Create an OpenGL 4.x or 3.x rendering context.
	// Always try to create the preferred rendering context.
	// If that's not available try the next (lower) rendering context.
	// When no preference is specified always choose the best one.

	if (m_preferredGLVersion == GL_VERSION_UNKNOWN)
		m_preferredGLVersion = static_cast<GLVersion>((sizeof(ATTRIB_LISTS) / sizeof(ATTRIB_LISTS[0])) - 1);

	for (int i = m_preferredGLVersion; i >= 0; --i)
	{
		m_hRC = wglCreateContextAttribsARB(m_hDC, 0, ATTRIB_LISTS[i]);

		if (m_hRC)
		{
			m_actualGLVersion = static_cast<GLVersion>(i);
			break;
		}
	}

	if (!m_hRC)
	{
		m_actualGLVersion = GL_VERSION_UNKNOWN;
		throw std::runtime_error("wglCreateContextAttribsARB() failed.");
	}
				
    if (!wglMakeCurrent(m_hDC, m_hRC))
        throw std::runtime_error("wglMakeCurrent() failed.");
}

void GL3Application::initApplication(const char *pszWindowName)
{
    m_pszWindowName = pszWindowName;
    m_hWnd = 0;
    m_hInstance = GetModuleHandle(0);
    m_hDC = 0;
    m_hRC = 0;
    m_windowWidth = 0;
    m_windowHeight = 0;
    m_framesPerSecond = 0;
    m_status = 0;
    m_antiAliasingSamples = 0;
    m_savedExStyle = 0;
    m_savedStyle = 0;
	m_cyclesLeftOver = 0.0f;
    m_isFullScreen = false;
    m_hasFocus = false;
    m_startFullScreen = false;

    memset(&m_rcSaved, 0, sizeof(m_rcSaved));
    memset(&m_wcl, 0, sizeof(m_wcl));
    
    m_wcl.cbSize = sizeof(m_wcl);
    m_wcl.style = CS_OWNDC | CS_HREDRAW | CS_VREDRAW;
    m_wcl.lpfnWndProc = windowProc;
    m_wcl.cbClsExtra = 0;
    m_wcl.cbWndExtra = 0;
    m_wcl.hInstance = m_hInstance;
    m_wcl.hIcon = LoadIcon(0, IDI_APPLICATION);
    m_wcl.hCursor = LoadCursor(0, IDC_ARROW);
    m_wcl.hbrBackground = 0;
    m_wcl.lpszMenuName = 0;
    m_wcl.lpszClassName = "GL3ApplicationWindowClass";
    m_wcl.hIconSm = 0;

	m_preferredGLVersion = GL_VERSION_UNKNOWN;
	m_actualGLVersion = GL_VERSION_UNKNOWN;
}

int GL3Application::mainLoop()
{
    if (m_startFullScreen)
        displayFullScreen();

	float updateIterations = 0.0f;
    MSG msg;
    
    memset(&msg, 0, sizeof(msg));
    ShowWindow(m_hWnd, SW_SHOWDEFAULT);
    UpdateWindow(m_hWnd);

    while (true)
    {
        while (PeekMessage(&msg, 0, 0, 0, PM_REMOVE))
        {
            if (msg.message == WM_QUIT)
                break;

            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }

        if (msg.message == WM_QUIT)
            break;

        if (m_hasFocus)
        {
			updateIterations = elapsedTimeInSeconds() + m_cyclesLeftOver;

			if (updateIterations > MAX_CYCLES_PER_FRAME * UPDATE_INTERVAL)
				updateIterations = MAX_CYCLES_PER_FRAME * UPDATE_INTERVAL;

			while (updateIterations > UPDATE_INTERVAL)
			{
				updateIterations -= UPDATE_INTERVAL;

				Mouse::instance().update();
				Keyboard::instance().update();

				update(UPDATE_INTERVAL);
			}
			
			m_cyclesLeftOver = updateIterations;

            render();
            SwapBuffers(m_hDC);
        }
        else
        {
            WaitMessage();
        }
    }

    return static_cast<int>(msg.wParam);
}

LRESULT GL3Application::windowProcImpl(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
    Mouse::instance().handleMsg(hWnd, msg, wParam, lParam);
    Keyboard::instance().handleMsg(hWnd, msg, wParam, lParam);

    switch (msg)
    {
    case WM_ACTIVATE:
        switch (wParam)
        {
        default:
            break;

        case WA_ACTIVE:
        case WA_CLICKACTIVE:
            Mouse::instance().attach(hWnd);
            m_hasFocus = true;
            break;

        case WA_INACTIVE:
            if (m_isFullScreen)
                ShowWindow(hWnd, SW_MINIMIZE);
            Mouse::instance().detach();
            m_hasFocus = false;
            break;
        }
        break;

    case WM_DESTROY:
        PostQuitMessage(m_status);
        return 0;

    case WM_SIZE:
        m_windowWidth = static_cast<int>(LOWORD(lParam));
        m_windowHeight = static_cast<int>(HIWORD(lParam));
        break;

	case WM_SYSKEYDOWN:
	case WM_SYSKEYUP:
		return 0;

	case WM_SYSCOMMAND:
		switch (wParam)
		{
		case SC_KEYMENU:
		case SC_SCREENSAVE:
			return 0;
		}
		break;

    default:
        break;
    }
    
    return wndProc(hWnd, msg, wParam, lParam);
}

//-----------------------------------------------------------------------------
// Static methods.
//-----------------------------------------------------------------------------

float GL3Application::elapsedTimeInSeconds()
{
    // Returns the elapsed time (in seconds) since the last time this method
    // was called. This elaborate setup is to guard against large spikes in
    // the time returned by QueryPerformanceCounter().
    
    INT64 time = 0;
    float elapsedTimeSec = 0.0f;

    if (!m_initialized)
    {
        m_initialized = true;
        QueryPerformanceFrequency(reinterpret_cast<LARGE_INTEGER*>(&m_freq));
        QueryPerformanceCounter(reinterpret_cast<LARGE_INTEGER*>(&m_lastTime));
        m_timeScale = 1.0f / m_freq;
    }

    QueryPerformanceCounter(reinterpret_cast<LARGE_INTEGER*>(&time));
    elapsedTimeSec = (time - m_lastTime) * m_timeScale;
    m_lastTime = time;

    if (fabsf(elapsedTimeSec - m_actualElapsedTimeSec) < 1.0f)
    {
        memmove(&m_frameTimes[1], m_frameTimes, sizeof(m_frameTimes) - sizeof(m_frameTimes[0]));
        m_frameTimes[0] = elapsedTimeSec;

        if (m_sampleCount < MAX_SAMPLE_COUNT)
            ++m_sampleCount;
    }

    m_actualElapsedTimeSec = 0.0f;

    for (int i = 0; i < m_sampleCount; ++i)
        m_actualElapsedTimeSec += m_frameTimes[i];

    if (m_sampleCount > 0)
        m_actualElapsedTimeSec /= m_sampleCount;

    return m_actualElapsedTimeSec;
}

LRESULT CALLBACK GL3Application::windowProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
    GL3Application *pApplication = 0;

    if (msg == WM_NCCREATE)
    {
        pApplication = reinterpret_cast<GL3Application *>((reinterpret_cast<LPCREATESTRUCT>(lParam))->lpCreateParams);
        SetWindowLongPtr(hWnd, GWL_USERDATA, reinterpret_cast<LONG_PTR>(pApplication));
    }
    else
    {
        pApplication = reinterpret_cast<GL3Application *>(GetWindowLongPtr(hWnd, GWL_USERDATA));
    }

    if (!pApplication)
        return DefWindowProc(hWnd, msg, wParam, lParam);

    pApplication->m_hWnd = hWnd;
    return pApplication->windowProcImpl(hWnd, msg, wParam, lParam);
}

//-----------------------------------------------------------------------------
// Virtual methods.
//-----------------------------------------------------------------------------

void GL3Application::init(int argc, char *argv[])
{
}

void GL3Application::render()
{
    glViewport(0, 0, m_windowWidth, m_windowHeight);
    glClearColor(0.3f, 0.5f, 0.9f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
}

void GL3Application::shutdown()
{
}

void GL3Application::update(float elapsedTimeSec)
{
}

LRESULT GL3Application::wndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	return DefWindowProc(hWnd, msg, wParam, lParam);
}

} // namespace dhpoware