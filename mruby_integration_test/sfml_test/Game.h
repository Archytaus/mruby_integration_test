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
	sf::Clock* clock;
	bool running;
	bool _hasFocus;

	System<TransformComponent> transformComponents;

public:	
	sf::Window* window;

	class RenderManager* renderManager;
	class ScreenManager* screenManager;
	class ScriptManager* scriptManager;

	Game(void);
	~Game(void);

	void run();
	void shutdown();

	bool hasFocus();
};

