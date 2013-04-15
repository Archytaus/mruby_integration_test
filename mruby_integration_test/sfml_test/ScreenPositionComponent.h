#pragma once

#include "Component.h"
#include <glm\glm.hpp>

class ScreenPositionComponent
	: public Component
{
public:
	glm::ivec2 pos;

	ScreenPositionComponent(EntityId id) 
		: Component(id) 
	{
	}
	
	~ScreenPositionComponent(void)
	{
	}
};