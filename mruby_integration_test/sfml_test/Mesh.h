#pragma once

struct Mesh 
{
	unsigned int numFaces;
	GLuint vertexArray;
	int texIndex;
	GLuint uniformBlockIndex;

	Mesh()
	{
		vertexArray = 0;
		uniformBlockIndex = 0;
		texIndex = 0;
		numFaces = 0;
	}
};