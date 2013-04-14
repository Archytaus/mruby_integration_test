#pragma once

#include "Component.h"
#include "Model.h"

class RenderManager
{
public:
	RenderManager();
	~RenderManager();

	void render(EntityId entity, Model* model);
	void finalise();

	Model* loadModel(std::string path);
};