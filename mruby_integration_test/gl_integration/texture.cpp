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

#include <functional>
#include <algorithm>
#include <cstdlib>
#include <cstring>
#include <memory>
#include <string>
#include <sstream>
#include "texture.h"

// GL_EXT_texture_filter_anisotropic

#if !defined(GL_TEXTURE_MAX_ANISOTROPY_EXT)
#define GL_TEXTURE_MAX_ANISOTROPY_EXT 0x84FE
#endif

#if !defined(GL_MAX_TEXTURE_MAX_ANISOTROPY_EXT)
#define GL_MAX_TEXTURE_MAX_ANISOTROPY_EXT 0x84FF
#endif

namespace dhpoware {

int Texture2D::m_degreeOfAnisotropy;
int Texture2D::m_maxDegreeOfAnisotropy;

//-----------------------------------------------------------------------------
// Static methods
//-----------------------------------------------------------------------------

void Texture2D::preferAnisotropicTextureFiltering()
{
	m_degreeOfAnisotropy = BEST_DEGREE_OF_ANISOTROPY;
}

void Texture2D::preferAnisotropicTextureFiltering(int degreeOfAnisotrophy)
{
	m_degreeOfAnisotropy = degreeOfAnisotrophy;
}

//-----------------------------------------------------------------------------
// Public methods
//-----------------------------------------------------------------------------

Texture2D::Texture2D()
{
}

Texture2D::~Texture2D()
{
	destroy();
}

void Texture2D::create(const char *pszName, GLsizei width, GLsizei height, GLsizei pitch, GLenum format, GLenum type, GLint magFilter, GLint minFilter, GLint wrapS, GLint wrapT, const GLubyte *pPixels)
{
	m_name = pszName;
	m_width = width;
	m_height = height;
	m_pitch = pitch;
	m_format = format;
	m_type = type;
	m_magFilter = magFilter;
	m_minFilter = minFilter;
	m_wrapS = wrapS;
	m_wrapT = wrapT;

	if (pPixels)
	{
		m_pixels.resize(pitch * height);
		memcpy(&m_pixels[0], pPixels, pitch * height);
	}

	glGenTextures(1, &m_texture);
	glBindTexture(GL_TEXTURE_2D, m_texture);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, magFilter);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, minFilter);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, wrapS);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, wrapT);

	// Enable anisotropic texture filtering if supported.

	if (m_maxDegreeOfAnisotropy == 0)
	{
		// Lookup the maximum supported level of anisotropic texture filtering.
		// This must be performed after a valid rendering context is made active.
		// Otherwise the glGetIntegerv() call will report that the maximum degree
		// of anisotropic texture filtering is 1.

		if (gl::ExtensionSupported("GL_EXT_texture_filter_anisotropic"))
			glGetIntegerv(GL_MAX_TEXTURE_MAX_ANISOTROPY_EXT, &m_maxDegreeOfAnisotropy);
		else
			m_maxDegreeOfAnisotropy = 1;
	}

	if ((m_degreeOfAnisotropy > 1 || m_degreeOfAnisotropy == BEST_DEGREE_OF_ANISOTROPY) && m_maxDegreeOfAnisotropy > 1)
	{
		int anisotropy;

		if (m_degreeOfAnisotropy == BEST_DEGREE_OF_ANISOTROPY)
			anisotropy = m_maxDegreeOfAnisotropy;
		else
			anisotropy = min(m_degreeOfAnisotropy, m_maxDegreeOfAnisotropy);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAX_ANISOTROPY_EXT, anisotropy);
	}

	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, m_width, m_height, 0, m_format, m_type, &m_pixels[0]);

	if (minFilter == GL_LINEAR_MIPMAP_LINEAR)
	{
		// Generate the mipmaps. Don't use the GL_GENERATE_MIPMAP flag to the
		// glTexParameteri() function because that's deprecated in OpenGL 3.0.
		// Instead use the glGenerateMipmap() function originally introduced
		// in the GL_EXT_framebuffer_object extension and now part of core
		// OpenGL 3.0.

		glGenerateMipmap(GL_TEXTURE_2D);
	}

	glBindTexture(GL_TEXTURE_2D, 0);
}

void Texture2D::create(const char *pszName, GLsizei width, GLsizei height, GLsizei pitch, GLenum format, GLenum type, GLint magFilter, GLint minFilter, GLint wrapS, GLint wrapT)
{
	create(pszName, width, height, pitch, format, type, magFilter, minFilter, wrapS, wrapT, 0);
}

void Texture2D::create(const char *pszName, GLsizei width, GLsizei height, GLsizei pitch, GLenum format, GLenum type, const GLubyte *pPixels)
{
	create(pszName, width, height, pitch, format, type, GL_LINEAR, GL_LINEAR_MIPMAP_LINEAR, GL_REPEAT, GL_REPEAT, pPixels);
}

void Texture2D::create(const char *pszName, GLsizei width, GLsizei height, GLsizei pitch, GLenum format, GLenum type)
{
	create(pszName, width, height, pitch, format, type, GL_LINEAR, GL_LINEAR_MIPMAP_LINEAR, GL_REPEAT, GL_REPEAT);
}

void Texture2D::destroy()
{
	if (m_texture != 0)
	{
		glDeleteTextures(1, &m_texture);
		m_texture = 0;

		m_width = 0;
		m_height = 0;
		m_pitch = 0;
		m_magFilter= 0;
		m_minFilter = 0;
		m_wrapS = 0;
		m_wrapT = 0;
		m_format = 0;
		m_type = 0;

		m_pixels.clear();
		m_name.clear();
	}
}

bool Texture2D::load(const char *pszFilename)
{
	return load(pszFilename, GL_LINEAR, GL_LINEAR_MIPMAP_LINEAR, GL_REPEAT, GL_REPEAT);
}

bool Texture2D::load(const char *pszFilename, GLint magFilter, GLint minFilter, GLint wrapS, GLint wrapT)
{
	// GDI+ requires unicode strings.
	// This trick only works for strings containing English ASCII text.
	std::string asciiFilename(pszFilename);
	std::wstring unicodeFilename(asciiFilename.length(), L' ');
	std::copy(asciiFilename.begin(), asciiFilename.end(), unicodeFilename.begin());

	std::tr1::shared_ptr<Gdiplus::Bitmap> pBitmap(Gdiplus::Bitmap::FromFile(unicodeFilename.c_str(), FALSE));

	return loadFromBitmap(pBitmap, magFilter, minFilter, wrapS, wrapT, pszFilename);
}

bool Texture2D::loadFromResource(int resourceId)
{
	return loadFromResource(resourceId, GL_LINEAR, GL_LINEAR_MIPMAP_LINEAR, GL_REPEAT, GL_REPEAT);
}

bool Texture2D::loadFromResource(int resourceId, GLint magFilter, GLint minFilter, GLint wrapS, GLint wrapT)
{
	bool loaded = false;
	HMODULE hModule = GetModuleHandle(0);
	HRSRC hResource = FindResource(hModule, MAKEINTRESOURCE(resourceId), RT_RCDATA);

	if (hResource)
	{
		if (DWORD dwSize = SizeofResource(hModule, hResource))
		{
			if (const void *pResourceData = LockResource(LoadResource(hModule, hResource)))
			{
				if (HGLOBAL hBuffer = GlobalAlloc(GMEM_MOVEABLE, dwSize))
				{
					if (void *pBuffer = GlobalLock(hBuffer))
					{
						CopyMemory(pBuffer, pResourceData, dwSize);

						IStream *pStream = 0;

						if (CreateStreamOnHGlobal(hBuffer, TRUE, &pStream) == S_OK)
						{
							std::tr1::shared_ptr<Gdiplus::Bitmap> pBitmap(Gdiplus::Bitmap::FromStream(pStream));

							pStream->Release();

							std::ostringstream os;
							os << "Resource ID " << resourceId;

							loaded = loadFromBitmap(pBitmap, magFilter, minFilter, wrapS, wrapT, os.str().c_str());
						}

						GlobalUnlock(hBuffer);
					}

					GlobalFree(hBuffer);
				}
			}
		}
	}

	return loaded;
}

bool Texture2D::save(const char *pszFileName)
{
	if (m_type != GL_UNSIGNED_BYTE)
		return false;

	if (!pszFileName)
		return false;

	Gdiplus::PixelFormat pixelformat = 0;

	switch (m_format)
	{
	case GL_BGRA:
		pixelformat = PixelFormat32bppARGB;
		break;

	case GL_BGR:
		pixelformat = PixelFormat24bppRGB;
		break;

	default:
		return false;
	}

	BYTE *pPixels = const_cast<BYTE *>(&m_pixels[0]);
	std::tr1::shared_ptr<Gdiplus::Bitmap> pBitmap(new Gdiplus::Bitmap(m_width, m_height, m_pitch, pixelformat, pPixels));

	if (pBitmap->GetLastStatus() != Gdiplus::Ok)
		return false;

	// GDI+ requires UNICODE strings. Convert ASCII path to UNICODE path.
	// HACK! Perform the conversion to UNICODE.
	// This will only work for strings containing English ASCII text.

	std::string asciiPath = getPngSaveFileName(pszFileName);
	std::wstring unicodePath(asciiPath.length(), L' ');
	std::copy(asciiPath.begin(), asciiPath.end(), unicodePath.begin());

	CLSID clsidEncoderPng;
	getPngEncoderClsid(&clsidEncoderPng);
	
	// GDI+ orients bitmap images top-bottom.
	// OpenGL expects bitmap images to be oriented bottom-top by default.
	pBitmap->RotateFlip(Gdiplus::RotateNoneFlipY);

	return pBitmap->Save(unicodePath.c_str(), &clsidEncoderPng, 0) == Gdiplus::Ok;
}

bool Texture2D::save(const char *pszSaveDirectory, const char *pszSaveFileName)
{
	// When no save directory is provided use the current directory.

	std::string asciiSaveDirectory;

	if (!pszSaveDirectory)
	{
		char szCurrentDirectory[MAX_PATH] = {'\0'};

		GetCurrentDirectory(MAX_PATH, szCurrentDirectory);
		asciiSaveDirectory = szCurrentDirectory;
	}
	else
	{
		asciiSaveDirectory = pszSaveDirectory;
	}

	// Make sure there's a directory path separator at the end.

	if (asciiSaveDirectory[asciiSaveDirectory.size() - 1] != '\\')
		asciiSaveDirectory += '\\';

	std::string asciiSaveFileName = getPngSaveFileName(pszSaveFileName);
	std::string asciiPath = asciiSaveDirectory + asciiSaveFileName;

	return save(asciiPath.c_str());
}

//-----------------------------------------------------------------------------
// Private methods
//-----------------------------------------------------------------------------

bool Texture2D::getPngEncoderClsid(CLSID *pClsid)
{
	const wchar_t *pszFormat = L"image/png";
	UINT num = 0;
	UINT size = 0;

	Gdiplus::GetImageEncodersSize(&num, &size);

	if (!size)
		return false;

	Gdiplus::ImageCodecInfo *pImageCodecInfo = static_cast<Gdiplus::ImageCodecInfo *>(malloc(size));

	if (!pImageCodecInfo)
		return false;

	GetImageEncoders(num, size, pImageCodecInfo);

	for (UINT i = 0; i < num; ++i)
	{
		if (wcscmp(pImageCodecInfo[i].MimeType, pszFormat) == 0)
		{
			memcpy(pClsid, &pImageCodecInfo[i].Clsid, sizeof(CLSID));
			free(pImageCodecInfo);
			return true;
		}
	}

	free(pImageCodecInfo);
	return false;
}

std::string Texture2D::getPngSaveFileName(const char *pszFilename) const
{
	std::string filename(pszFilename);

	// Verify that the save file name contains a valid file extension.
	
	std::transform(filename.begin(), filename.end(), filename.begin(), std::ptr_fun(tolower));

	if (filename.rfind(".png") == std::string::npos)
	{
		filename = pszFilename;
		filename += ".png";
	}
	else
	{
		filename = pszFilename;
	}

	return filename;
}

bool Texture2D::loadFromBitmap(std::tr1::shared_ptr<Gdiplus::Bitmap> &pBitmap, GLint magFilter, GLint minFilter, GLint wrapS, GLint wrapT, const char *pszName)
{
	if (pBitmap.get() == 0)
		return false;

	if (pBitmap->GetLastStatus() != Gdiplus::Ok)
		return false;

	// GDI+ orients bitmap images top-bottom.
	// OpenGL expects bitmap images to be oriented bottom-top by default.
	pBitmap->RotateFlip(Gdiplus::RotateNoneFlipY);

	int width = pBitmap->GetWidth();
	int height = pBitmap->GetHeight();
	int pitch = ((width * 32 + 31) & ~31) >> 3;
	GLenum format = GL_BGRA;
	GLenum type = GL_UNSIGNED_BYTE;

	std::vector<GLubyte> pixels;
	pixels.resize(pitch * height);

	Gdiplus::BitmapData data;
	Gdiplus::Rect rect(0, 0, width, height);

	// Convert to 32-bit BGRA pixel format and fetch the pixel data.

	if (pBitmap->LockBits(&rect, Gdiplus::ImageLockModeRead, PixelFormat32bppARGB, &data) != Gdiplus::Ok)
		return 0;

	if (data.Stride == pitch)
	{
		memcpy(&pixels[0], data.Scan0, pitch * height);
	}
	else
	{
		GLubyte *pSrcPixels = static_cast<GLubyte *>(data.Scan0);

		for (int i = 0; i < height; ++i)
			memcpy(&pixels[i * pitch], &pSrcPixels[i * data.Stride], pitch);
	}

	pBitmap->UnlockBits(&data);

	// Create the texture object with the loaded pixel data.
	create(pszName, width, height, pitch, format, type, magFilter, minFilter, wrapS, wrapT, &pixels[0]);

	return true;
}

} // namespace dhpoware