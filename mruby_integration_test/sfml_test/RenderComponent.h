#pragma once

#include <string>
#include <glm/gtc/matrix_transform.hpp>

#include "Component.h"
#include "TransformComponent.h"
#include "RenderManager.h"
#include "ShaderProgram.h"
#include "Texture.h"

class RenderComponent
	: public Component
{
public:
	class TransformComponent* transformComponent;
	class RenderManager* renderManager;
	ShaderProgram* shader;
	Texture* diffuse;

	GLuint vao, vbo;

	RenderComponent(EntityId id, class RenderManager* renderManager, class TransformComponent* transformComponent)
		: Component(id), renderManager(renderManager), transformComponent(transformComponent) 
	{
	}

	void load();
	void render();
};