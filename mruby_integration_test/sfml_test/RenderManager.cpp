#include "RenderManager.h"


RenderManager::RenderManager(void)
{
	importer = new Assimp::Importer();
}


RenderManager::~RenderManager(void)
{
}

void RenderManager::render(EntityId entity, Model* model)
{
	model->render();
}

void RenderManager::finalise()
{

}

Model* RenderManager::loadModel(std::string path)
{
	const aiScene* node = importer->ReadFile(path, 0);
	
	if(!node)
	{
		return nullptr;
	}

	return new Model(node, path);
}