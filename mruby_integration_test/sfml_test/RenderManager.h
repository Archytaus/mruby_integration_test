#pragma once

#include <assimp\Importer.hpp>

#include "Component.h"
#include "Model.h"

class RenderManager
{
public:
	RenderManager();
	~RenderManager();
	Assimp::Importer* importer;

	void render(EntityId entity, Model* model);
	void finalise();

	Model* loadModel(std::string path);
};