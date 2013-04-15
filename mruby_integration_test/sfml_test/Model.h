#pragma once

#include <vector>
#include <map>
#include <string>
#include <assimp\scene.h>

#include <glew.h>
#include <SFML\OpenGL.hpp>

#include "Mesh.h"

class Model
{
protected:
	const aiScene* scene;
	std::string path;
	std::map<std::string, int> textures;
	std::vector<Mesh> meshes;

	void renderNode(const struct aiNode* nd);

public:
	Model(const aiScene* scene, std::string path);
	~Model(void);

	void loadTextures();
	void loadBuffers();

	void render();
};

