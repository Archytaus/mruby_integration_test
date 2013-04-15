#pragma once

#include <assimp\Importer.hpp>

#include "Component.h"
#include "RenderComponent.h"

class RenderManager
{
public:
	System<class RenderComponent> renderables;

	Assimp::Importer* importer;

	RenderManager();
	~RenderManager();
	
	void render();

	class RenderComponent* createRenderComponent(EntityId id);
};