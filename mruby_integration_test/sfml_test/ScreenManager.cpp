#include "ScreenManager.h"


ScreenManager::ScreenManager(Game* game)
	: game(game)
{
}


ScreenManager::~ScreenManager(void)
{
}

void ScreenManager::update(sf::Time elapsed)
{
	for (auto screen : activeScreens.components)
	{
		screen.second->update(elapsed);
	}
}

void ScreenManager::render()
{
	for (auto screen : activeScreens.components)
	{
		screen.second->render();
	}
}