#include "RenderManager.h"


RenderManager::RenderManager(Game* game)
	: game(game)
{
	camera = new Camera();
	camera->setPosition(glm::vec3(0, 0, 4));
	camera->setViewportAspectRatio(800.0f/600.0f);

	importer = new Assimp::Importer();
}

RenderManager::~RenderManager(void)
{
}

RenderComponent* RenderManager::createRenderComponent(EntityId id, class TransformComponent* transformComponent)
{
	return renderables.components[id] = new RenderComponent(id, this, transformComponent);
}

void RenderManager::render()
{
	for(auto kvp : renderables.components)
	{
		kvp.second->render();
	}
}