#include "InputManager.h"

void InputManager::init()
{
}

void InputManager::shutdown()
{
}

void InputManager::update(sf::Time elapsed)
{
	if(sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
	{
		game->shutdown();
	}
}