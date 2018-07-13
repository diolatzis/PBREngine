#ifndef MESH_H
#define MESH_H

#define GLEW_STATIC

#include <GL\glew.h>
#include <vector>
#include <glm.hpp>
#include <gtc\matrix_transform.hpp>

#include "RenderableObject.h"
#include "Face.h"

class Mesh : public RenderableObject
{
public:
	Mesh();
	~Mesh();	

	//Vertex Buffers
	static const int VBID_POS = 0, VBID_NORMAL = 1, VBID_COLOUR = 2;
	//Number of VBOs
	static const int VBOS_NUM = 3;	

	int frame = 0;
		
	GLuint shaderProgram;
	GLuint vao;
	GLuint vbos[3];
	int pointsNum;
	glm::mat4 modelMatrix;

	void render();
	
};


#endif

