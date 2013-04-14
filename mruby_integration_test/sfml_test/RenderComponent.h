#pragma once

#include <string>
#include "Component.h"
#include "WorldPositionComponent.h"
#include "RenderManager.h"
#include "Model.h"

class RenderComponent
	: public Component
{
public:
	RenderManager* renderManager;
	Model* model;

	RenderComponent(EntityId id, RenderManager* renderManager, Model* model)
		: Component(id), renderManager(renderManager), model(model) {}

	void load(std::string path){
		model = new Model(path);
	}

	void render() {
		renderManager->render(this->owner, model);
	}
};