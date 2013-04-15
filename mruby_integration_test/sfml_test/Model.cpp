#include "Model.h"

#include <SFML\Graphics.hpp>

#include "Material.h"

Model::Model(const aiScene* scene, std::string path)
	: scene(scene), path(path) 
{
	loadTextures();
	loadBuffers();
}

Model::~Model(void)
{
}

void Model::loadTextures()
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

void Model::loadBuffers()
{
	GLuint buffer = 0;
	struct Mesh newMesh;
	struct Material newMaterial;
	
	GLuint vertexLoc = 0, normalLoc = 0, texCoordLoc = 0;

	// For each mesh
	for (unsigned int n = 0; n < scene->mNumMeshes; ++n)
	{
		const struct aiMesh* mesh = scene->mMeshes[n];

		// create array with faces
		// have to convert from Assimp format to array
		unsigned int *faceArray;
		faceArray = (unsigned int *)malloc(sizeof(unsigned int) * mesh->mNumFaces * 3);
		unsigned int faceIndex = 0;

		for (unsigned int t = 0; t < mesh->mNumFaces; ++t) {
			const struct aiFace* face = &mesh->mFaces[t];

			memcpy(&faceArray[faceIndex], face->mIndices,3 * sizeof(float));
			faceIndex += 3;
		}
		newMesh.numFaces = scene->mMeshes[n]->mNumFaces;

		// generate Vertex Array for mesh
		glGenVertexArrays(1,&newMesh.vertexArray);
		glBindVertexArray(newMesh.vertexArray);

		// buffer for faces
		glGenBuffers(1, &buffer);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, buffer);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(unsigned int) * mesh->mNumFaces * 3, faceArray, GL_STATIC_DRAW);

		// buffer for vertex positions
		if (mesh->HasPositions()) {
			glGenBuffers(1, &buffer);
			glBindBuffer(GL_ARRAY_BUFFER, buffer);
			glBufferData(GL_ARRAY_BUFFER, sizeof(float)*3*mesh->mNumVertices, mesh->mVertices, GL_STATIC_DRAW);
			glEnableVertexAttribArray(vertexLoc);
			glVertexAttribPointer(vertexLoc, 3, GL_FLOAT, 0, 0, 0);
		}

		// buffer for vertex normals
		if (mesh->HasNormals()) {
			glGenBuffers(1, &buffer);
			glBindBuffer(GL_ARRAY_BUFFER, buffer);
			glBufferData(GL_ARRAY_BUFFER, sizeof(float)*3*mesh->mNumVertices, mesh->mNormals, GL_STATIC_DRAW);
			glEnableVertexAttribArray(normalLoc);
			glVertexAttribPointer(normalLoc, 3, GL_FLOAT, 0, 0, 0);
		}

		// buffer for vertex texture coordinates
		if (mesh->HasTextureCoords(0)) {
			float *texCoords = (float *)malloc(sizeof(float)*2*mesh->mNumVertices);
			for (unsigned int k = 0; k < mesh->mNumVertices; ++k) {

				texCoords[k*2]   = mesh->mTextureCoords[0][k].x;
				texCoords[k*2+1] = mesh->mTextureCoords[0][k].y; 

			}
			glGenBuffers(1, &buffer);
			glBindBuffer(GL_ARRAY_BUFFER, buffer);
			glBufferData(GL_ARRAY_BUFFER, sizeof(float)*2*mesh->mNumVertices, texCoords, GL_STATIC_DRAW);
			glEnableVertexAttribArray(texCoordLoc);
			glVertexAttribPointer(texCoordLoc, 2, GL_FLOAT, 0, 0, 0);
		}

		// unbind buffers
		glBindVertexArray(0);
		glBindBuffer(GL_ARRAY_BUFFER,0);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,0);

		// create material uniform buffer
		struct aiMaterial *mtl = scene->mMaterials[mesh->mMaterialIndex];

		aiString texPath;   //contains filename of texture
		if(AI_SUCCESS == mtl->GetTexture(aiTextureType_DIFFUSE, 0, &texPath))
		{
			//bind texture
			unsigned int texId = textures[texPath.data];
			newMesh.texIndex = texId;
			newMaterial.texCount = 1;
		}
		else
		{
			newMaterial.texCount = 0;
		}
		
		aiColor4D diffuse = aiColor4D(0.8f, 0.8f, 0.8f, 1.0f);
        aiGetMaterialColor(mtl, AI_MATKEY_COLOR_DIFFUSE, &diffuse);
		newMaterial.diffuse = diffuse;
 
		aiColor4D ambient = aiColor4D(0.2f, 0.2f, 0.2f, 1.0f);
        aiGetMaterialColor(mtl, AI_MATKEY_COLOR_AMBIENT, &ambient);
		newMaterial.ambient = ambient;

		aiColor4D specular = aiColor4D(0.0f, 0.0f, 0.0f, 1.0f);
        aiGetMaterialColor(mtl, AI_MATKEY_COLOR_SPECULAR, &specular);
		newMaterial.specular = specular;
 
		aiColor4D emission = aiColor4D(0.0f, 0.0f, 0.0f, 1.0f);
        aiGetMaterialColor(mtl, AI_MATKEY_COLOR_EMISSIVE, &emission);
		newMaterial.emission = emission;
 
        float shininess = 0.0;
        unsigned int max;
        aiGetMaterialFloatArray(mtl, AI_MATKEY_SHININESS, &shininess, &max);
        newMaterial.shininess = shininess;

		glGenBuffers(1,&(newMesh.uniformBlockIndex));
        glBindBuffer(GL_UNIFORM_BUFFER,newMesh.uniformBlockIndex);
        glBufferData(GL_UNIFORM_BUFFER, sizeof(newMaterial), (void *)(&newMaterial), GL_STATIC_DRAW);
 
        meshes.push_back(newMesh);
	}
}

void Model::render()
{
	renderNode(scene->mRootNode);
}

void Model::renderNode(const struct aiNode* nd)
{
	GLuint materialUniLoc = 0;

	// Get node transformation matrix
    aiMatrix4x4 m = nd->mTransformation;
	
    // OpenGL matrices are column major
    m.Transpose();
	
    // save model matrix and apply node transformation
	glPushMatrix();
	
    // draw all meshes assigned to this node
    for (unsigned int n=0; n < nd->mNumMeshes; ++n){
        // bind material uniform
        glBindBufferRange(GL_UNIFORM_BUFFER, materialUniLoc, meshes[nd->mMeshes[n]].uniformBlockIndex, 0, sizeof(struct Material));
        
		// bind texture
        glBindTexture(GL_TEXTURE_2D, meshes[nd->mMeshes[n]].texIndex);

        // bind VAO
		glBindVertexArray(meshes[nd->mMeshes[n]].vertexArray);

        // draw
        glDrawElements(GL_TRIANGLES,meshes[nd->mMeshes[n]].numFaces*3,GL_UNSIGNED_INT,0);
    }
	
    // draw all children
    for (unsigned int n=0; n < nd->mNumChildren; ++n){
		renderNode(nd->mChildren[n]);
    }

    glPopMatrix();
}