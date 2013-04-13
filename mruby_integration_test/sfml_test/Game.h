#pragma once

#include <SFML/Graphics.hpp>
#include <vector>
#include "IGameComponent.h"

class Game
{
protected:
	sf::Window* window;
	sf::Clock* clock;
	bool running;
	std::vector<IGameComponent*> components;

public:
	Game(void);
	~Game(void);

	void run();
	void shutdown();
};

