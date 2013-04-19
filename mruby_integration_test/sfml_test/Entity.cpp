#include "Entity.h"

class Component* Entity::addComponent(Component* component)
{
	component->parent = this;
	_components.push_back(component);

	return component;
}