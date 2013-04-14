#pragma once

#include <SFML/Graphics.hpp>
#include <vector>
#include "Component.h"
#include "WorldPositionComponent.h"
#include "RenderComponent.h"
#include "RenderManager.h"

class Game
{
protected:
	sf::Window* window;
	sf::Clock* clock;
	bool running;

	System<WorldPositionComponent> wpSys;
    System<RenderComponent> rSys;

	RenderManager* renderManager;

public:
	Game(void);
	~Game(void);

	void run();
	void shutdown();
};

