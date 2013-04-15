#pragma once
#include <SFML\Graphics\Color.hpp>

struct Material 
{
	int texCount;
	aiColor4D diffuse, ambient, specular, emission;
	float shininess;

	Material()
	{
		texCount = 0;
	}
};