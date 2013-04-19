#include "ScriptComponent.h"

ScriptComponent::ScriptComponent(EntityId id, class TransformComponent* transformComponent, std::string scriptClass, mrb_state* mrb) 
	: Component(id), mrb(mrb)
{
	_scriptInstance = mrb_class_new_instance(mrb, 0, ARGS_NONE(), mrb_class_get(mrb, scriptClass.c_str()));
	mrb_iv_set(mrb, _scriptInstance, mrb_intern_cstr(mrb, "@id"), mrb_fixnum_value(id)); 

	mrb_iv_set(mrb, _scriptInstance, mrb_intern_cstr(mrb, "@transform"), transformComponent->init_mrb_variables(mrb)); 
	
	onCreate();
}

ScriptComponent::~ScriptComponent()
{
	onDestroy();
}

void ScriptComponent::onCreate()
{	
	int ai = mrb_gc_arena_save(mrb);

	if(mrb_respond_to(mrb, _scriptInstance, mrb_intern_cstr(mrb, "onCreate")) == TRUE)
	{
		mrb_funcall(mrb, _scriptInstance, "onCreate", 0);
		if(mrb->exc)
		{
			mrb_p(mrb, mrb_obj_value(mrb->exc));
		}
	}
	mrb_gc_arena_restore(mrb, ai);
}

void ScriptComponent::onDestroy()
{
	int ai = mrb_gc_arena_save(mrb);

	if(mrb_respond_to(mrb, _scriptInstance, mrb_intern_cstr(mrb, "onDestroy")) == TRUE)
	{
		mrb_funcall(mrb, _scriptInstance, "onDestroy", 0);
		if(mrb->exc)
		{
			mrb_p(mrb, mrb_obj_value(mrb->exc));
		}
	}

	mrb_gc_arena_restore(mrb, ai);
}

void ScriptComponent::onUpdate(sf::Time elapsed)
{
	int ai = mrb_gc_arena_save(mrb);

	if(mrb_respond_to(mrb, _scriptInstance, mrb_intern_cstr(mrb, "update")) == TRUE)
	{
		mrb_funcall(mrb, _scriptInstance, "update", 1, mrb_float_value(elapsed.asSeconds()));
		if(mrb->exc)
		{
			mrb_p(mrb, mrb_obj_value(mrb->exc));
		}
	}

	mrb_gc_arena_restore(mrb, ai);
}