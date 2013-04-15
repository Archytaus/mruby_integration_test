#pragma once

#include <vector>
#include "ScreenSpriteComponent.h"

class Screen
	: public Component
{
protected:
	System<ScreenSpriteComponent> positionComponents;

public:
	Screen(EntityId id);
	~Screen(void);

	void update(sf::Time elapsed);
	void render();
};

