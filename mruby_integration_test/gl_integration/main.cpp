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

#include <windows.h>
#include <string>
#include <sstream>
#include <vector>
#include "application.h"

using namespace dhpoware;

class Demo : public GL3Application
{
public:
    Demo();
    virtual ~Demo();

protected:
    virtual void init(int argc, char *argv[]);
    virtual void update(float elapsedTimeSec);
	virtual void render();

private:
	bool testSupportedExtensions() const;
};

//-----------------------------------------------------------------------------
// Demo class implementation.
//-----------------------------------------------------------------------------

Demo::Demo()
{
}

Demo::~Demo()
{
}

void Demo::init(int argc, char *argv[])
{
	enableVerticalSync(true);

	int major = 0;
	int minor = 0;

	gl::GetGLVersion(major, minor);

	std::ostringstream title;
	title << "OpenGL " << major << "." << minor << " Framework Demo";

	SetWindowText(hWnd(), title.str().c_str());

	if (!testSupportedExtensions())
		MessageBox(hWnd(), "Extension testing failed!", "textSupportedExtensions()", MB_OK);
}

void Demo::update(float elapsedTimeSec)
{
	if (keyDown(Keyboard::KEY_LALT) || keyDown(Keyboard::KEY_RALT))
	{
		if (keyPressed(Keyboard::KEY_ENTER))
			toggleFullScreen();
	}

	if (keyPressed(Keyboard::KEY_ESCAPE))
		quit();
}

void Demo::render()
{
    glViewport(0, 0, viewportWidth(), viewportHeight());
    glClearColor(1.0f, 1.0f, 1.0f, 0.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
}

bool Demo::testSupportedExtensions() const
{
	std::vector<std::string> supportedExtensions = gl::GetExtensions();
	std::vector<std::string>::size_type totalSupported = 0;

	for (std::vector<std::string>::const_iterator i = supportedExtensions.begin(); i != supportedExtensions.end(); ++i)
	{
		if (gl::ExtensionSupported(i->c_str()))
			++totalSupported;
	}

	return (supportedExtensions.empty()) ? false : totalSupported == supportedExtensions.size();
}

//-----------------------------------------------------------------------------
// WinMain - application entry point.
//-----------------------------------------------------------------------------

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nShowCmd)
{
    Demo demo;
    
    demo.preferAntiAliasing();
    demo.preferWindowed();

    return demo.run();
}