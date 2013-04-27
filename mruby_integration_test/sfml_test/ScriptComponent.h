#pragma once

#include "Component.h"
#include "TransformComponent.h"

#include <mruby.h>
#include <mruby/proc.h>
#include <mruby\variable.h>

#include "Camera.h"
#include "mrb_vec3.h"

class ScriptComponent 
	: public Component
{
protected:
	mrb_state* mrb;
	mrb_value _scriptInstance;

public:
	ScriptComponent(EntityId id, std::string scriptClass, mrb_state* mrb);
	~ScriptComponent();
	
	void onCreate();
	void onDestroy();
	void onUpdate(sf::Time elapsed);

	ScriptComponent* withTransformComponent(class TransformComponent* transformComponent);
	ScriptComponent* withCameraComponent(class Camera* camera);
};