#include "RenderManager.h"


RenderManager::RenderManager(void)
{
	importer = new Assimp::Importer();
}


RenderManager::~RenderManager(void)
{
}

RenderComponent* RenderManager::createRenderComponent(EntityId id, class WorldPositionComponent* worldPositionComponent)
{
	return renderables.components[id] = new RenderComponent(id, this, worldPositionComponent);
}

void RenderManager::render()
{
	for(auto kvp : renderables.components)
	{
		kvp.second->render();
	}
}