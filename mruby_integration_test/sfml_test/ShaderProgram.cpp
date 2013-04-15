#include "ShaderProgram.h"

#include <glm/gtc/type_ptr.hpp>
#include <sstream>
#include <fstream>

ShaderProgram::ShaderProgram()
{
	m_program = glCreateProgram();
}

ShaderProgram::~ShaderProgram()
{
	glDeleteProgram(m_program);
}

void ShaderProgram::attachFromFile(GLuint type, const std::string& filePath)
{
	std::ifstream file;
    file.open(filePath.c_str());

    if (!file) {
      printf("in ShaderProgram::attachFromFile : error, couldn't find file!\n");
      exit(0);
    }

    std::stringstream stream;
    stream << file.rdbuf();
    file.close();

    attach(type, stream.str());
}

void ShaderProgram::attach(GLuint type, const std::string& src)
{
	// compile the shader
	const char *srcp = src.c_str();
	GLuint shader = glCreateShader(type);
	glShaderSource(shader, 1, &srcp, NULL);
	glCompileShader(shader);

	// check for errors
	GLint status;
	glGetShaderiv(shader, GL_COMPILE_STATUS, &status);
	if (!status) {
		int length;
		glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &length);
		char *buf = new char[length];
		glGetShaderInfoLog(shader, length, NULL, buf);
		std::string message(buf);
		delete[] buf;

		// delete the shader
		glDeleteShader(shader);

		// throw the exception
        throw std::runtime_error(std::string("Unable to attach shader: ") + src);
		return;
	}

	// attach the shader to the program and delete it afterwards
	glAttachShader(m_program, shader);
	glDeleteShader(shader);
}

void ShaderProgram::link()
{
	// link the program
	glLinkProgram(m_program);

	// check for errors
	GLint status;
	glGetProgramiv(m_program, GL_LINK_STATUS, &status);
	if (!status) {
		int length;
		glGetProgramiv(m_program, GL_INFO_LOG_LENGTH, &length);
		char *buf = new char[length];
		glGetProgramInfoLog(m_program, length, NULL, buf);
		std::string message(buf);
		delete[] buf;

		// throw the exception
		
        throw std::runtime_error(std::string("Unable to link program: ") + message);
		return;
	}
}

void ShaderProgram::use()
{
	glUseProgram(m_program);
}

void ShaderProgram::setup()
{
	use();
}

void ShaderProgram::bind_attribute(const std::string& name, GLuint attr)
{
	glBindAttribLocation(m_program, attr, name.c_str());
}

void ShaderProgram::bind_frag_data_location(const std::string& name, GLuint attr)
{
	glBindFragDataLocation(m_program, attr, name.c_str());
}

void ShaderProgram::bind_uniform(const std::string& name, int val)
{
	glUniform1i(get_uniform_location(name), val);
}

void ShaderProgram::bind_uniform(const std::string& name, float val)
{
	glUniform1f(get_uniform_location(name), val);
}

void ShaderProgram::bind_uniform(const std::string& name, const glm::vec2& val)
{
	glUniform2fv(get_uniform_location(name), 1, &val[0]);
}

void ShaderProgram::bind_uniform(const std::string& name, const glm::vec3& val)
{
	glUniform3fv(get_uniform_location(name), 1, &val[0]);
}

void ShaderProgram::bind_uniform(const std::string& name, const glm::vec4& val)
{
	glUniform4fv(get_uniform_location(name), 1, &val[0]);
}

void ShaderProgram::bind_uniform(const std::string& name, const glm::mat2& val)
{
	glUniformMatrix2fv(get_uniform_location(name), 1, GL_FALSE, glm::value_ptr(val));
}

void ShaderProgram::bind_uniform(const std::string& name, const glm::mat3& val)
{
	glUniformMatrix3fv(get_uniform_location(name), 1, GL_FALSE, glm::value_ptr(val));
}

void ShaderProgram::bind_uniform(const std::string& name, const glm::mat4& val)
{
	glUniformMatrix4fv(get_uniform_location(name), 1, GL_FALSE, glm::value_ptr(val));
}

GLint ShaderProgram::get_uniform_location(const std::string& name)
{
	GLint location = glGetUniformLocation(m_program, name.c_str());
	if (location == -1) {
		return -1;
		//throw invalid_shader_uniform(name);
	}
	return location;
}

GLint ShaderProgram::get_attrib(const std::string& attribName) {
	GLint attrib = glGetAttribLocation(m_program, attribName.c_str());
    if(attrib == -1)
        throw std::runtime_error(std::string("Program attribute not found: ") + attribName);
    
    return attrib;
}