#pragma once

#include <SFML/Graphics.hpp>

typedef unsigned long EntityId;

template <typename C> class System {
public:
    std::map<EntityId, C * > components;
};

class Component
{
public:
	EntityId owner;

	Component(EntityId id) : owner(id) {}
};