#pragma once

#include <SFML/Graphics.hpp>
#include <vector>
#include "Component.h"
#include "WorldPositionComponent.h"
#include "RenderComponent.h"
#include "RenderManager.h"
#include "ScreenManager.h"
#include "ScriptComponent.h"

class Game
{
protected:
	sf::Window* window;
	sf::Clock* clock;
	bool running;

	RenderManager* renderManager;
	class ScreenManager* screenManager;
	System<WorldPositionComponent> worldPositionComponents;
	System<ScriptComponent> scriptComponents;

public:
	Game(void);
	~Game(void);

	void run();
	void shutdown();
};

