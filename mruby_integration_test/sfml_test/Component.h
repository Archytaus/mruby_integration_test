#pragma once

#include <SFML/Graphics.hpp>

#include "Entity.h"

typedef unsigned long EntityId;

template <typename C> class System {
public:
    std::map<EntityId, C *> components;
};

class Component
{
public:
	EntityId owner;
	class Entity* parent;

	Component(EntityId id) : owner(id) {}
};