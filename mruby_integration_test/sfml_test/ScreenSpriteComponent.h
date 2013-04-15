#pragma once

#include "Component.h"

class ScreenSpriteComponent
	: public Component
{
public:
	sf::Sprite* sprite;

	ScreenSpriteComponent(EntityId id) 
		: Component(id) 
	{
		sprite = new sf::Sprite();
	}
	
	~ScreenSpriteComponent(void)
	{
	}
};