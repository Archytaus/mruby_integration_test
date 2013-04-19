#pragma once

#include <string>
#include <glm/gtc/matrix_transform.hpp>

#include "Component.h"
#include "WorldPositionComponent.h"
#include "RenderManager.h"
#include "ShaderProgram.h"
#include "Texture.h"
#include "WorldPositionComponent.h"

class RenderComponent
	: public Component
{
public:
	class WorldPositionComponent* worldPositionComponent;
	class RenderManager* renderManager;
	ShaderProgram* shader;
	Texture* diffuse;

	GLuint vao, vbo;

	RenderComponent(EntityId id, class RenderManager* renderManager, class WorldPositionComponent* worldPositionComponent)
		: Component(id), renderManager(renderManager), worldPositionComponent(worldPositionComponent) 
	{
	}

	void load();
	void render();
};