#pragma once

#include "IGameComponent.h"
#include "Game.h"

class InputManager 
	: public IGameComponent
{
protected:
	Game* game;

public:
	InputManager(Game* game) 
		: game(game)
	{

	}

	virtual void init();
	virtual void shutdown();
	virtual void update(sf::Time elapsed);
};

