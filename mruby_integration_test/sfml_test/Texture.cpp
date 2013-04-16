#include "Texture.h"

#include  <io.h>

Texture::Texture(GLint minMagFiler, GLint wrapMode)
	: _minMagFiler(minMagFiler), _wrapMode(wrapMode)
{
}

Texture::~Texture(void)
{
	glDeleteTextures(1, &_id);
}

void Texture::load(const std::string& fileName)
{
	sf::Image image;
	if (::_access(fileName.c_str(), 04) == -1 || !image.loadFromFile(fileName))
	{
		throw std::runtime_error(std::string("Unable to load image from file: ") + fileName);
	}

	width = image.getSize().x;
	height = image.getSize().y;

	glGenTextures(1, &_id);
	glBindTexture(GL_TEXTURE_2D, _id);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, _minMagFiler);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, _minMagFiler);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, _wrapMode);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, _wrapMode);

	glTexImage2D(GL_TEXTURE_2D,
		0, 
		GL_RGBA,
		(GLsizei)width, 
		(GLsizei)height,
		0,
		GL_RGBA, 
		GL_UNSIGNED_BYTE, 
		image.getPixelsPtr());

	glBindTexture(GL_TEXTURE_2D, 0);
}

void Texture::bind()
{
	glBindTexture(GL_TEXTURE_2D, _id);
}