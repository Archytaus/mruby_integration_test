#pragma once

#include "Component.h"
#include "ScriptComponent.h"

#include <mruby.h>
#include <mruby\compile.h>
#include <mruby\class.h>
#include <mruby\variable.h>

class ScriptManager
{
protected:
	mrb_state* mrb;	
	struct RClass *scriptComponentClass;

public:
	System<class ScriptComponent> scriptComponents;

	ScriptManager(void);
	~ScriptManager(void);

	void update(sf::Time elapsed);
	
	class ScriptComponent* createScriptComponent(EntityId id, class TransformComponent* transformComponent, std::string className);
};

