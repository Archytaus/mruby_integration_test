#pragma once

#include <glew.h>
#include <SFML\Graphics.hpp>
#include <SFML\OpenGL.hpp>
#include <string>

class Texture
{
protected:
	GLuint _id;
	GLint _minMagFiler, _wrapMode;

public:
	GLfloat width, height;

	Texture(GLint minMagFiler = GL_LINEAR,
                GLint wrapMode = GL_CLAMP_TO_EDGE);
	~Texture(void);

	void load(const std::string& fileName);
	void bind();
};

