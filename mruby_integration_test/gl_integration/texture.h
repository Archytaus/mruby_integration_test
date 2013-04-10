//-----------------------------------------------------------------------------
// Copyright (c) 2011-2012 dhpoware. All Rights Reserved.
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

#if !defined(TEXTURE_H)
#define TEXTURE_H

#include <windows.h>
#include <gdiplus.h>
#include <memory>
#include <string>
#include <vector>
#include "gl.h"

namespace dhpoware {

//-----------------------------------------------------------------------------
// Wrapper class around a 2D texture object.
//
// The anisotropic texture filtering setting applies to all textures. All the
// other texture settings are per texture.
//
// The Texture2D class maintains a local copy of the pixel data whenever the
// create() or load() methods are called to create a texture.
//
// Updating the pixel data of a texture object is not currently supported.
//
// How to use the Texture2D class:
//
// 1. Declare a new instance of the Texture2D class:
//      Texture2D myTexture;
//
// 2. To create a new texture from an array of pixels call:
//      GLubyte pixels[] = your array of pixels;
//      myTexture.create("my new texture", ... , pixels);
//
// 3. To create a new empty texture call one of the overloaded create()
//    methods that doesn't accept an array of pixels as an argument.
//
// 4. To load a texture from a file call:
//      myTexture.load("myFile.jpg");
//    GDI+ is used to load the file. The image file formats that GDI+ supports
//    include: BMP, GIF, JPEG, PNG, and TIFF.
//
// 5. A Texture2D object can be saved to a PNG file. To do this call:
//      myTexture.save("someCoolFileName");
//    The output image format is always PNG. If the file name doesn't include
//    the ".png" extension then the save() method will append it to the file
//    name that is provided.
//-----------------------------------------------------------------------------

class Texture2D
{
public:
	static void preferAnisotropicTextureFiltering();
	static void preferAnisotropicTextureFiltering(int degreeOfAnisotrophy);

	Texture2D();
	~Texture2D();

	inline GLenum format() const;
	inline GLsizei height() const;
	inline GLint magFilter() const;
	inline GLint minFilter() const;
	inline const std::string &name() const;
	inline GLsizei pitch() const;
	inline const GLubyte *pixels() const;
	inline GLenum type() const;
	inline GLuint textureObject() const;
	inline GLsizei width() const;
	inline GLint wrapS() const;
	inline GLint wrapT() const;
	
	void create(const char *pszName, GLsizei width, GLsizei height, GLsizei pitch, GLenum format, GLenum type, GLint magFilter, GLint minFilter, GLint wrapS, GLint wrapT, const GLubyte *pPixels);
	void create(const char *pszName, GLsizei width, GLsizei height, GLsizei pitch, GLenum format, GLenum type, GLint magFilter, GLint minFilter, GLint wrapS, GLint wrapT);
	void create(const char *pszName, GLsizei width, GLsizei height, GLsizei pitch, GLenum format, GLenum type, const GLubyte *pPixels);
	void create(const char *pszName, GLsizei width, GLsizei height, GLsizei pitch, GLenum format, GLenum type);
	void destroy();
	bool load(const char *pszFilename);
	bool load(const char *pszFilename, GLint magFilter, GLint minFilter, GLint wrapS, GLint wrapT);
	bool loadFromResource(int resourceId);
	bool loadFromResource(int resourceId, GLint magFilter, GLint minFilter, GLint wrapS, GLint wrapT);
	bool save(const char *pszFileName);
	bool save(const char *pszSaveDirectory, const char *pszSaveFileName);

private:
	bool getPngEncoderClsid(CLSID *pClsid);
	std::string getPngSaveFileName(const char *pszFilename) const;
	bool loadFromBitmap(std::tr1::shared_ptr<Gdiplus::Bitmap> &pBitmap, GLint magFilter, GLint minFilter, GLint wrapS, GLint wrapT, const char *pszName);
	
	static const int BEST_DEGREE_OF_ANISOTROPY = -1;
	
	static int m_maxDegreeOfAnisotropy;
	static int m_degreeOfAnisotropy;
	
	GLuint m_texture;					// texture object
	GLsizei m_width;					// in pixels
	GLsizei m_height;					// in pixels
	GLsizei m_pitch;					// in bytes; normally 4-byte aligned
	GLint m_magFilter;					// texture magnification filter
	GLint m_minFilter;					// texture minification filter
	GLint m_wrapS;						// texture x-axis wrapping mode
	GLint m_wrapT;						// texture y-axis wrapping mode
	GLenum m_format;					// for saving MUST be GL_BGRA
	GLenum m_type;						// for saving MUST be GL_UNSIGNED_BYTE
	std::vector<GLubyte> m_pixels;		// pixel data; usually 4-byte aligned
	std::string m_name;					// unique identifier; usually file name
};

//-----------------------------------------------------------------------------

inline GLenum Texture2D::format() const
{ return m_format; }

inline GLsizei Texture2D::height() const
{ return m_height; }

inline GLint Texture2D::magFilter() const
{ return m_magFilter; }

inline GLint Texture2D::minFilter() const
{ return m_minFilter; }

inline const std::string &Texture2D::name() const
{ return m_name; }

inline GLsizei Texture2D::pitch() const
{ return m_pitch; }

inline const GLubyte * Texture2D::pixels() const
{ return &m_pixels[0]; }

inline GLenum Texture2D::type() const
{ return m_type; }

inline GLuint Texture2D::textureObject() const
{ return m_texture; }

inline GLsizei Texture2D::width() const
{ return m_width; }

inline GLint Texture2D::wrapS() const
{ return m_wrapS; }

inline GLint Texture2D::wrapT() const
{ return m_wrapT; }

} // namespace dhpoware
#endif