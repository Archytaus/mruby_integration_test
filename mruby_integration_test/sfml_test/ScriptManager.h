#pragma once

#include "Component.h"
#include "ScriptComponent.h"
#include "Game.h"
#include "ScriptPart.h"

#include <vector>

#include <mruby.h>
#include <mruby\compile.h>
#include <mruby\class.h>
#include <mruby\variable.h>

class ScriptManager
{
protected:
	mrb_state* mrb;	
	struct RClass *scriptComponentClass;
	class Game* game;
	std::vector<ScriptPart*> singletonComponents;

public:
	System<class ScriptComponent> scriptComponents;

	ScriptManager(class Game* game);
	~ScriptManager(void);

	void update(sf::Time elapsed);
	
	class ScriptComponent* createScriptComponent(EntityId id, std::string className);
};

