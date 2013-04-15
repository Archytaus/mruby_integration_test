#pragma once

#include <string>
#include <glew.h>
#include <SFML\OpenGL.hpp>
#include <glm\glm.hpp>

class ShaderProgram
{
public:
	ShaderProgram(void);
	~ShaderProgram(void);

	// attach shader and link
	void attach(GLuint type, const std::string& src);
	void attachFromFile(GLuint type, const std::string& filePath);
	void link();

	// use it
	virtual void use();
	virtual void setup();

	void bind_frag_data_location(const std::string& name, GLuint attr);

	// bind attrib
	virtual void bind_attribute(const std::string& name, GLuint attr);

	// bind uniforms
	virtual void bind_uniform(const std::string& name, int val);
	virtual void bind_uniform(const std::string& name, float val);
	virtual void bind_uniform(const std::string& name, const glm::vec2& val);
	virtual void bind_uniform(const std::string& name, const glm::vec3& val);
	virtual void bind_uniform(const std::string& name, const glm::vec4& val);
	virtual void bind_uniform(const std::string& name, const glm::mat2& val);
	virtual void bind_uniform(const std::string& name, const glm::mat3& val);
	virtual void bind_uniform(const std::string& name, const glm::mat4& val);

	// get uniform location
	GLint get_uniform_location(const std::string& name);
	
	GLint get_attrib(const std::string& attribName);

protected:
	// shader program and attrib list
	GLuint m_program;
};

