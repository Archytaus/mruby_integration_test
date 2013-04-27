#pragma once

#include <SFML/Graphics.hpp>
#include <vector>
#include "Component.h"
#include "TransformComponent.h"
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

	System<TransformComponent> transformComponents;

public:	
	class RenderManager* renderManager;
	class ScreenManager* screenManager;
	class ScriptManager* scriptManager;

	Game(void);
	~Game(void);

	void run();
	void shutdown();
};

