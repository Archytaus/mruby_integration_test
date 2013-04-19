#pragma once

#include <assimp\Importer.hpp>

#include "Component.h"
#include "RenderComponent.h"
#include "TransformComponent.h"
#include "Game.h"
#include "Camera.h"

class RenderManager
{
public:
	System<class RenderComponent> renderables;
	
	class Game* game;
	Camera* camera;

	Assimp::Importer* importer;

	RenderManager(class Game* game);
	~RenderManager();
	
	void render();

	class RenderComponent* createRenderComponent(EntityId id, class TransformComponent* transformComponent);
};