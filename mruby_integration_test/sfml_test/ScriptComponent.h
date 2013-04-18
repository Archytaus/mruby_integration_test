#pragma once

#include "Component.h"
#include "WorldPositionComponent.h"

#include <mruby.h>
#include <mruby/proc.h>

class ScriptComponent 
	: public Component
{
protected:
	mrb_state* mrb;
	mrb_value _scriptInstance;
	
public:
	ScriptComponent(EntityId id, std::string scriptClass, mrb_state* mrb) 
		: Component(id), mrb(mrb)
	{
		_scriptInstance = mrb_class_new_instance(mrb, 0, ARGS_NONE(), mrb_class_get(mrb, scriptClass.c_str()));
		
		onCreate();
	}

	~ScriptComponent()
	{
		onDestroy();
	}

	void onCreate()
	{
		mrb_funcall(mrb, _scriptInstance, "onCreate", 0);
	}

	void onDestroy()
	{
		mrb_funcall(mrb, _scriptInstance, "onDestroy", 0);
	}

	void onUpdate(sf::Time elapsed)
	{
		mrb_funcall(mrb, _scriptInstance, "onUpdate", 1, mrb_float_value(elapsed.asSeconds()));
	}
};