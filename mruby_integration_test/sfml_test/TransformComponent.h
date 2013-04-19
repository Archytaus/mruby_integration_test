#pragma once

#include "Component.h"
#include <glm/gtc/matrix_transform.hpp>

class TransformComponent 
	: public Component
{
public:
	glm::vec3 position, rotation, scale;

    TransformComponent(EntityId id) 
		: Component(id), scale(1.0f)
	{}

	glm::mat4 world()
	{
		glm::mat4 world;
		world *= glm::scale(glm::mat4(), scale);

		world *= glm::rotate(glm::mat4(), rotation.x, glm::vec3(1, 0, 0));
		world *= glm::rotate(glm::mat4(), rotation.y, glm::vec3(0, 1, 0));
		world *= glm::rotate(glm::mat4(), rotation.z, glm::vec3(0, 0, 1));

		world *= glm::translate(glm::mat4(), position);

		return world;
	}
};