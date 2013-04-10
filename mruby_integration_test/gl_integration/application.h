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

#if !defined(GL3APPLICATION_H)
#define GL3APPLICATION_H

#if !defined(WIN32_LEAN_AND_MEAN)
#define WIN32_LEAN_AND_MEAN
#endif

#include <windows.h>
#include "gl.h"
#include "input.h"
#include "WGL_ARB_create_context.h"
#include "WGL_ARB_multisample.h"
#include "WGL_EXT_swap_control.h"

namespace dhpoware {

class GL3Application
{
public:
	enum GLVersion
	{
		GL_VERSION_3_0		= 0,
		GL_VERSION_3_1		= 1,
		GL_VERSION_3_2		= 2,
		GL_VERSION_3_3		= 3,
		GL_VERSION_4_0		= 4,
		GL_VERSION_4_1		= 5,
		GL_VERSION_4_2		= 6,
		GL_VERSION_UNKNOWN	= 65536
	};

    GL3Application();
    GL3Application(const char *pszWindowName);
    virtual ~GL3Application();
    
    void preferAnisotropicTextureFiltering();
    void preferAnisotropicTextureFiltering(int degreeOfAnisotrophy);
    void preferAntiAliasing();
    void preferAntiAliasing(int samples);
    void preferFullScreen();
	void preferOpenGLVersion(GLVersion version);
    void preferWindowed();
    int run();

protected:
    void displayFullScreen();
    void displayWindowed();
    void enableVerticalSync(bool enableVerticalSync);
    
	inline GLVersion glVersion() const;

	inline HINSTANCE hInstance() const;
	inline HWND hWnd() const;

    inline bool isFullScreen() const;

    inline Keyboard &keyboard() const;  
    inline bool keyDown(Keyboard::Key key) const;
    inline bool keyPressed(Keyboard::Key key) const;
    inline bool keyUp(Keyboard::Key key) const;
       
    inline Mouse &mouse() const;
    inline bool mouseButtonDown(Mouse::MouseButton button) const;
    inline bool mouseButtonPressed(Mouse::MouseButton button) const;
    inline bool mouseButtonUp(Mouse::MouseButton button) const;
    inline int mousePositionX() const;
    inline int mousePositionY() const;

	void quit(int status = 0);
		
    void toggleFullScreen();
    void toggleVerticalSync();

    bool verticalSyncEnabled() const;

    inline int viewportHeight() const;
    inline int viewportWidth() const;
    
	inline const char *windowTitle() const;

protected:
    virtual void init(int argc, char *argv[]);
    virtual void render();
    virtual void shutdown();
    virtual void update(float elapsedTimeSec);
	virtual LRESULT wndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);

private:
    GL3Application(const GL3Application &);
    GL3Application &operator=(const GL3Application &);

    static float elapsedTimeInSeconds();
    static LRESULT CALLBACK windowProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);
    
    bool create();
    void destroy();
    void initOpenGL();
    void initApplication(const char *pszWindowName);
	
    int mainLoop();
    LRESULT windowProcImpl(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);
    
    static const int BEST_ANTI_ALIASING_SAMPLES = -1;
    static const int MAX_SAMPLE_COUNT = 50;
	
	static const float MAXIMUM_FRAME_RATE;
	static const float MINIMUM_FRAME_RATE;
	static const float UPDATE_INTERVAL;
	static const float MAX_CYCLES_PER_FRAME;

	static const int ATTRIB_LIST_GL_VERSION_3_0[];
	static const int ATTRIB_LIST_GL_VERSION_3_1[];
	static const int ATTRIB_LIST_GL_VERSION_3_2[];
	static const int ATTRIB_LIST_GL_VERSION_3_3[];
	static const int ATTRIB_LIST_GL_VERSION_4_0[];
	static const int ATTRIB_LIST_GL_VERSION_4_1[];
	static const int ATTRIB_LIST_GL_VERSION_4_2[];

	static const int * const ATTRIB_LISTS[];

    static Mouse    &m_mouse;
    static Keyboard &m_keyboard;
    static INT64     m_freq;
    static INT64     m_lastTime;
    static int       m_sampleCount;
    static float     m_timeScale;
    static float     m_actualElapsedTimeSec;
    static float     m_frameTimes[MAX_SAMPLE_COUNT];
    static bool      m_initialized;
        
    const char *m_pszWindowName;
    HWND        m_hWnd;
    HINSTANCE   m_hInstance;
    HDC         m_hDC;
    HGLRC       m_hRC;
    int         m_windowWidth;
    int         m_windowHeight;
    int         m_framesPerSecond;
    int         m_status;
    int         m_antiAliasingSamples;
    DWORD       m_savedExStyle;
    DWORD       m_savedStyle;
	float		m_cyclesLeftOver;
    bool        m_isFullScreen;
    bool        m_hasFocus;
    bool        m_startFullScreen;
    RECT        m_rcSaved;
    WNDCLASSEX  m_wcl;
	GLVersion	m_preferredGLVersion;
	GLVersion	m_actualGLVersion;
};

//-----------------------------------------------------------------------------

inline HINSTANCE GL3Application::hInstance() const
{ return m_hInstance; }

inline HWND GL3Application::hWnd() const
{ return m_hWnd; }

inline bool GL3Application::isFullScreen() const
{ return m_isFullScreen; }

inline Keyboard &GL3Application::keyboard() const
{ return m_keyboard; }

inline bool GL3Application::keyDown(Keyboard::Key key) const
{ return m_keyboard.keyDown(key); }

inline bool GL3Application::keyPressed(Keyboard::Key key) const
{ return m_keyboard.keyPressed(key); }

inline bool GL3Application::keyUp(Keyboard::Key key) const
{ return m_keyboard.keyUp(key); }

inline Mouse &GL3Application::mouse() const
{ return m_mouse; }

inline bool GL3Application::mouseButtonDown(Mouse::MouseButton button) const
{ return m_mouse.buttonDown(button); }

inline bool GL3Application::mouseButtonPressed(Mouse::MouseButton button) const
{ return m_mouse.buttonPressed(button); }

inline bool GL3Application::mouseButtonUp(Mouse::MouseButton button) const
{ return m_mouse.buttonUp(button); }

inline int GL3Application::mousePositionX() const
{ return m_mouse.xPosAbsolute(); }

inline int GL3Application::mousePositionY() const
{ return m_mouse.yPosAbsolute(); }

inline int GL3Application::viewportHeight() const
{ return m_windowHeight; }

inline int GL3Application::viewportWidth() const
{ return m_windowWidth; }

inline const char *GL3Application::windowTitle() const
{ return m_pszWindowName; }

inline GL3Application::GLVersion GL3Application::glVersion() const
{ return m_actualGLVersion; }

}

#endif