#pragma once

#include <string>
#include <glm/gtc/matrix_transform.hpp>

#include "Component.h"
#include "WorldPositionComponent.h"
#include "RenderManager.h"
#include "ShaderProgram.h"
#include "Texture.h"

class RenderComponent
	: public Component
{
public:
	class RenderManager* renderManager;
	ShaderProgram* shader;
	Texture* diffuse;

	GLuint vao, vbo;
	GLfloat rotation;

	RenderComponent(EntityId id, class RenderManager* renderManager)
		: Component(id), renderManager(renderManager), rotation(0.0f) {}

	void load(){
		diffuse = new Texture();
		diffuse->load("Assets/Textures/texture.jpg");

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
			//  X     Y     Z       U     V
			// bottom
			-1.0f,-1.0f,-1.0f,   0.0f, 0.0f,
			1.0f,-1.0f,-1.0f,   1.0f, 0.0f,
			-1.0f,-1.0f, 1.0f,   0.0f, 1.0f,
			1.0f,-1.0f,-1.0f,   1.0f, 0.0f,
			1.0f,-1.0f, 1.0f,   1.0f, 1.0f,
			-1.0f,-1.0f, 1.0f,   0.0f, 1.0f,

			// top
			-1.0f, 1.0f,-1.0f,   0.0f, 0.0f,
			-1.0f, 1.0f, 1.0f,   0.0f, 1.0f,
			1.0f, 1.0f,-1.0f,   1.0f, 0.0f,
			1.0f, 1.0f,-1.0f,   1.0f, 0.0f,
			-1.0f, 1.0f, 1.0f,   0.0f, 1.0f,
			1.0f, 1.0f, 1.0f,   1.0f, 1.0f,

			// front
			-1.0f,-1.0f, 1.0f,   1.0f, 0.0f,
			1.0f,-1.0f, 1.0f,   0.0f, 0.0f,
			-1.0f, 1.0f, 1.0f,   1.0f, 1.0f,
			1.0f,-1.0f, 1.0f,   0.0f, 0.0f,
			1.0f, 1.0f, 1.0f,   0.0f, 1.0f,
			-1.0f, 1.0f, 1.0f,   1.0f, 1.0f,

			// back
			-1.0f,-1.0f,-1.0f,   0.0f, 0.0f,
			-1.0f, 1.0f,-1.0f,   0.0f, 1.0f,
			1.0f,-1.0f,-1.0f,   1.0f, 0.0f,
			1.0f,-1.0f,-1.0f,   1.0f, 0.0f,
			-1.0f, 1.0f,-1.0f,   0.0f, 1.0f,
			1.0f, 1.0f,-1.0f,   1.0f, 1.0f,

			// left
			-1.0f,-1.0f, 1.0f,   0.0f, 1.0f,
			-1.0f, 1.0f,-1.0f,   1.0f, 0.0f,
			-1.0f,-1.0f,-1.0f,   0.0f, 0.0f,
			-1.0f,-1.0f, 1.0f,   0.0f, 1.0f,
			-1.0f, 1.0f, 1.0f,   1.0f, 1.0f,
			-1.0f, 1.0f,-1.0f,   1.0f, 0.0f,

			// right
			1.0f,-1.0f, 1.0f,   1.0f, 1.0f,
			1.0f,-1.0f,-1.0f,   1.0f, 0.0f,
			1.0f, 1.0f,-1.0f,   0.0f, 0.0f,
			1.0f,-1.0f, 1.0f,   1.0f, 1.0f,
			1.0f, 1.0f,-1.0f,   0.0f, 0.0f,
			1.0f, 1.0f, 1.0f,   0.0f, 1.0f
		};

		glBufferData(GL_ARRAY_BUFFER, sizeof(vertexData), vertexData, GL_STATIC_DRAW);

		// connect the xyz to the "vert" attribute of the vertex shader
		glEnableVertexAttribArray(shader->get_attrib("vert"));
		glVertexAttribPointer(shader->get_attrib("vert"), 3, GL_FLOAT, GL_FALSE, 5*sizeof(GLfloat), NULL);

		// connect the uv coords to the "vertTexCoord" attribute of the vertex shader
		glEnableVertexAttribArray(shader->get_attrib("vertTexCoord"));
		glVertexAttribPointer(shader->get_attrib("vertTexCoord"), 2, GL_FLOAT, GL_TRUE,  5*sizeof(GLfloat), (const GLvoid*)(3 * sizeof(GLfloat)));

		// unbind the VBO and VAO
		glBindBuffer(GL_ARRAY_BUFFER, 0);
		glBindVertexArray(0);
	}

	void render() 
	{
		// bind the program (the shaders)
		shader->use();
		
		glm::mat4 camera = glm::lookAt(glm::vec3(3,3,3), glm::vec3(0,0,0), glm::vec3(0,1,0));
		shader->bind_uniform("camera", camera);
	
		glm::mat4 projection = glm::perspective<float>(50.0, 800.0f/600.0f, 0.1, 10.0);
		shader->bind_uniform("projection", projection);
		
		rotation += 1.0f;
		while(rotation > 360.0f) rotation -= 360.0f;

		shader->bind_uniform("model", glm::rotate(glm::mat4(), rotation, glm::vec3(0,1,0)));

		glActiveTexture(GL_TEXTURE0);
		diffuse->bind();
		shader->bind_uniform("tex", 0);

		// bind the VAO (the triangle)
		glBindVertexArray(vao);

		// draw the VAO
		glDrawArrays(GL_TRIANGLES, 0, 6*2*3);

		// unbind the VAO
		glBindVertexArray(0);

		// unbind the program
		glUseProgram(0);
	}
};