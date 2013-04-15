#include "RenderManager.h"


RenderManager::RenderManager(void)
{
	importer = new Assimp::Importer();
}


RenderManager::~RenderManager(void)
{
}

RenderComponent* RenderManager::createRenderComponent(EntityId id)
{
	return renderables.components[id] = new RenderComponent(id, this);
}

void RenderManager::render()
{
	for(auto kvp : renderables.components)
	{
		kvp.second->render();
	}
}