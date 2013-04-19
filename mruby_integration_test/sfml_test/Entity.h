#pragma once

#include <vector>

#include "Component.h"

typedef unsigned long EntityId;

class Entity
{
protected:
	EntityId _id;
	std::vector<class Component*> _components;

public:
	Entity(EntityId id)
		: _id(id)
	{
	}

	class Component* addComponent(class Component* component);
};