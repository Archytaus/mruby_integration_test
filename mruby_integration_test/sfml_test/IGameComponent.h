#pragma once

#include <SFML/Graphics.hpp>

class IGameComponent
{
public:
	virtual void init() = 0;
	virtual void shutdown() = 0;

	virtual void update(sf::Time elapsed) = 0;
};