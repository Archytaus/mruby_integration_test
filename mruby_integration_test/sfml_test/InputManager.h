#pragma once

#include "IGameComponent.h"

class InputManager : public IGameComponent
{
public:
	InputManager(void);
	~InputManager(void);

	virtual void init();
	virtual void shutdown();
	virtual void update(sf::Time elapsed);
};

