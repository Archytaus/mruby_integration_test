#include "RenderManager.h"


RenderManager::RenderManager(void)
{
}


RenderManager::~RenderManager(void)
{
}

void RenderManager::render(EntityId entity, Model* model)
{
}

void RenderManager::finalise()
{

}

Model* RenderManager::loadModel(std::string path)
{
	return new Model(path);
}