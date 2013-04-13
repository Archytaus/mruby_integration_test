#pragma once

#include <SFML/Graphics.hpp>

class Game
{
protected:
	sf::Window* window;
	sf::Clock* clock;
	bool running;
	
public:
	Game(void);
	~Game(void);

	void run();
};

