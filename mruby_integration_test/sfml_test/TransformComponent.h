#pragma once

#include <glm/gtc/matrix_transform.hpp>
#include <mruby.h>
#include <mruby\class.h>
#include <mruby\variable.h>

#include "Component.h"
#include "mrb_vec3.h"
#include "mrb_transform.h"

class TransformComponent 
	: public Component
{
public:
	glm::vec3 position, rotation, scale;
	mrb_value transformInstance;

	TransformComponent(EntityId id);

	glm::mat4 world();

	mrb_value init_mrb_variables(mrb_state* mrb);
};