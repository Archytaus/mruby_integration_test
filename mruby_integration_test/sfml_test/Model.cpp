#include "Model.h"

#include <SFML\Graphics.hpp>
#include <SFML\OpenGL.hpp>

Model::Model(const aiScene* scene, std::string path)
		: scene(scene), path(path) 
{
	/* scan scene's materials for textures */
	for (unsigned int m=0; m < scene->mNumMaterials; ++m)
    {
        int texIndex = 0;
        aiString path;  // filename
 
        aiReturn texFound = scene->mMaterials[m]->GetTexture(aiTextureType_DIFFUSE, texIndex, &path);
        while (texFound == AI_SUCCESS) {
            //fill map with textures, OpenGL image ids set to 0
			textures[path.data] = 0;
            // more textures?
            texIndex++;
            texFound = scene->mMaterials[m]->GetTexture(aiTextureType_DIFFUSE, texIndex, &path);
        }
    }
	
    int numTextures = textures.size();

	/* create and fill array with GL texture ids */
    GLuint* textureIds = new GLuint[numTextures];
    glGenTextures(numTextures, textureIds); /* Texture name generation */
	
	int i = 0;
	for(auto kvp : textures)
	{
		std::string filename = kvp.first;
		kvp.second = textureIds[i];

		sf::Image image;
		bool success = image.loadFromFile(filename);
		if(success)
		{
			glBindTexture(GL_TEXTURE_2D, textureIds[i]);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, image.getSize().x,
                image.getSize().y, 0, GL_RGBA, GL_UNSIGNED_BYTE,
				image.getPixelsPtr());
        }
        else
		{
            printf("Couldn't load Image: %s\n", filename.c_str());
		}
		
		i++;
	}

	delete [] textureIds;
}

Model::~Model(void)
{
}
