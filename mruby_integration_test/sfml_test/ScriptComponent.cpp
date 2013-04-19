#include "ScriptComponent.h"

ScriptComponent::ScriptComponent(EntityId id, class WorldPositionComponent* worldPositionComponent, std::string scriptClass, mrb_state* mrb) 
	: Component(id), mrb(mrb)
{
	_scriptInstance = mrb_class_new_instance(mrb, 0, ARGS_NONE(), mrb_class_get(mrb, scriptClass.c_str()));
	mrb_iv_set(mrb, _scriptInstance, mrb_intern_cstr(mrb, "@id"), mrb_fixnum_value(id)); 

	auto vec3Class = mrb_class_get(mrb, "Vec3");
	mrb_iv_set(mrb, _scriptInstance, mrb_intern_cstr(mrb, "@position"), mrb_vec3_wrap(mrb, vec3Class, new mrb_vec3(&worldPositionComponent->position)));
	mrb_iv_set(mrb, _scriptInstance, mrb_intern_cstr(mrb, "@rotation"), mrb_vec3_wrap(mrb, vec3Class, new mrb_vec3(&worldPositionComponent->rotation)));
	mrb_iv_set(mrb, _scriptInstance, mrb_intern_cstr(mrb, "@scale"), mrb_vec3_wrap(mrb, vec3Class, new mrb_vec3(&worldPositionComponent->scale)));

	onCreate();
}

ScriptComponent::~ScriptComponent()
{
	onDestroy();
}

void ScriptComponent::onCreate()
{
	mrb_funcall(mrb, _scriptInstance, "onCreate", 0);
}

void ScriptComponent::onDestroy()
{
	mrb_funcall(mrb, _scriptInstance, "onDestroy", 0);
}

void ScriptComponent::onUpdate(sf::Time elapsed)
{
	int ai = mrb_gc_arena_save(mrb);

	mrb_funcall(mrb, _scriptInstance, "update", 1, mrb_float_value(elapsed.asSeconds()));
	if(mrb->exc)
	{
		mrb_p(mrb, mrb_obj_value(mrb->exc));
	}

	mrb_gc_arena_restore(mrb, ai);
}