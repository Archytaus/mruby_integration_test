#include "TransformComponent.h"

TransformComponent::TransformComponent(EntityId id) 
	: Component(id), scale(1.0f)
{}

glm::mat4 TransformComponent::world()
{
	glm::mat4 world;
	
	world *= glm::translate(glm::mat4(), position);

	world *= glm::rotate(glm::mat4(), rotation.x, glm::vec3(1, 0, 0));
	world *= glm::rotate(glm::mat4(), rotation.y, glm::vec3(0, 1, 0));
	world *= glm::rotate(glm::mat4(), rotation.z, glm::vec3(0, 0, 1));

	world *= glm::scale(glm::mat4(), scale);

	return world;
}

mrb_value TransformComponent::init_mrb_variables(mrb_state* mrb)
{
	transformInstance = mrb_transform_wrap(mrb, mrb_class_get(mrb, "TransformComponent"), new mrb_transform(this));

	auto vec3Class = mrb_class_get(mrb, "Vec3");
	mrb_iv_set(mrb, transformInstance, mrb_intern_cstr(mrb, "@position"), mrb_vec3_wrap(mrb, vec3Class, new mrb_vec3(&position)));
	mrb_iv_set(mrb, transformInstance, mrb_intern_cstr(mrb, "@rotation"), mrb_vec3_wrap(mrb, vec3Class, new mrb_vec3(&rotation)));
	mrb_iv_set(mrb, transformInstance, mrb_intern_cstr(mrb, "@scale"), mrb_vec3_wrap(mrb, vec3Class, new mrb_vec3(&scale)));
	
	return transformInstance;
}