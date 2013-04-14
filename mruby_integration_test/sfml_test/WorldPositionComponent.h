#pragma once

#include "Component.h"

class WorldPositionComponent 
	: public Component 
{
public:
    float x, y, z;

    WorldPositionComponent(EntityId id) 
		: Component(id) 
	{}
};