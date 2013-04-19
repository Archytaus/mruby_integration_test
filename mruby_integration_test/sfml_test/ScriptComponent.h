#pragma once

#include "Component.h"
#include "WorldPositionComponent.h"

#include <mruby.h>
#include <mruby/proc.h>
#include <mruby\variable.h>

#include "mrb_vec3.h"

class ScriptComponent 
	: public Component
{
protected:
	mrb_state* mrb;
	mrb_value _scriptInstance;

public:
	ScriptComponent(EntityId id, class WorldPositionComponent* worldPositionComponent, std::string scriptClass, mrb_state* mrb) 
		: Component(id), mrb(mrb)
	{
		auto mrbScriptClass = mrb_class_get(mrb, scriptClass.c_str());
		_scriptInstance = mrb_class_new_instance(mrb, 0, ARGS_NONE(), mrbScriptClass);
		
		auto instancePtr = mrb_obj_ptr(_scriptInstance);
		mrb_iv_set(mrb, _scriptInstance, mrb_intern_cstr(mrb, "@id"), mrb_fixnum_value(id)); 
		auto vec3Class = mrb_class_get(mrb, "Vec3");
		auto wrappedVec3 = mrb_vec3_wrap(mrb, vec3Class, new mrb_vec3(&worldPositionComponent->rotation));
		mrb_iv_set(mrb, _scriptInstance, mrb_intern_cstr(mrb, "@rotation"), wrappedVec3);
		auto rotationValue = mrb_iv_get(mrb, _scriptInstance, mrb_intern_cstr(mrb, "@rotation"));
		
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
		int ai = mrb_gc_arena_save(mrb);
  
		mrb_funcall(mrb, _scriptInstance, "update", 1, mrb_float_value(elapsed.asSeconds()));
		if(mrb->exc)
		{
			mrb_p(mrb, mrb_obj_value(mrb->exc));
		}
		
		mrb_gc_arena_restore(mrb, ai);
	}
};