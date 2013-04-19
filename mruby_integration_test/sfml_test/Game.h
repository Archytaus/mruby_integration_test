#pragma once

#include <SFML/Graphics.hpp>
#include <vector>
#include "Component.h"
#include "WorldPositionComponent.h"
#include "RenderComponent.h"
#include "RenderManager.h"
#include "ScreenManager.h"
#include "ScriptManager.h"
#include "Camera.h"

class Game
{
protected:
	sf::Window* window;
	sf::Clock* clock;
	bool running;

	class RenderManager* renderManager;
	class ScreenManager* screenManager;
	class ScriptManager* scriptManager;

	System<WorldPositionComponent> worldPositionComponents;

public:
	Game(void);
	~Game(void);

	void run();
	void shutdown();
};

