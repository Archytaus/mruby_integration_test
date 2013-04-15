#pragma once

#include <string>
#include "Component.h"
#include "WorldPositionComponent.h"
#include "RenderManager.h"
#include "ShaderProgram.h"

class RenderComponent
	: public Component
{
public:
	class RenderManager* renderManager;
	ShaderProgram* shader;

	GLuint vao, vbo;

	RenderComponent(EntityId id, class RenderManager* renderManager)
		: Component(id), renderManager(renderManager) {}

	void load(){

		shader = new ShaderProgram();
		shader->attachFromFile(GL_VERTEX_SHADER, "Assets\\Shaders\\test.vert");
		shader->attachFromFile(GL_FRAGMENT_SHADER, "Assets\\Shaders\\test.frag");
		shader->link();

		// make and bind the VAO
		glGenVertexArrays(1, &vao);
		glBindVertexArray(vao);

		// make and bind the VBO
		glGenBuffers(1, &vbo);
		glBindBuffer(GL_ARRAY_BUFFER, vbo);

		// Put the three triangle verticies into the VBO
		GLfloat vertexData[] = {
			//  X     Y     Z
			0.0f, 0.8f, 0.0f,
			-0.8f,-0.8f, 0.0f,
			0.8f,-0.8f, 0.0f,
		};
		glBufferData(GL_ARRAY_BUFFER, sizeof(vertexData), vertexData, GL_STATIC_DRAW);

		// connect the xyz to the "vert" attribute of the vertex shader
		glEnableVertexAttribArray(shader->get_attrib("vert"));
		glVertexAttribPointer(shader->get_attrib("vert"), 3, GL_FLOAT, GL_FALSE, 0, NULL);

		// unbind the VBO and VAO
		glBindBuffer(GL_ARRAY_BUFFER, 0);
		glBindVertexArray(0);
	}

	void render() 
	{
		// bind the program (the shaders)
		shader->use();

		// bind the VAO (the triangle)
		glBindVertexArray(vao);

		// draw the VAO
		glDrawArrays(GL_TRIANGLES, 0, 3);

		// unbind the VAO
		glBindVertexArray(0);

		// unbind the program
		glUseProgram(0);
	}
};