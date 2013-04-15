#pragma once

#include "Component.h"
#include "Screen.h"
#include "Game.h"

class ScreenManager
{
protected:
	System<Screen> activeScreens;
	class Game* game;

public:
	ScreenManager(class Game* game);
	~ScreenManager(void);

	void update(sf::Time elapsed);
	void render();
};

