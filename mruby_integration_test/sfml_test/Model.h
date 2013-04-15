#pragma once

#include <map>
#include <string>
#include <assimp\scene.h>

class Model
{
protected:
	const aiScene* scene;
	std::string path;
	std::map<std::string, int> textures;

public:
	Model(const aiScene* scene, std::string path);
	~Model(void);
};

