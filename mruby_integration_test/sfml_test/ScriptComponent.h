#pragma once

#include "Component.h"
#include "WorldPositionComponent.h"

class ScriptComponent 
	: public Component
{
public:
	ScriptComponent(EntityId id) 
		: Component(id)
	{
		onCreate();
	}

	~ScriptComponent()
	{
		onDestroy();
	}

	void onCreate()
	{
	}

	void onDestroy()
	{
	}

	void onUpdate(sf::Time elapsed)
	{
	}
};