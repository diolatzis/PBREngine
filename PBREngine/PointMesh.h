#ifndef POINT_MESH_H
#define POINT_MESH_H

#define GLEW_STATIC

#include <GL\glew.h>
#include <vector>
#include <glm.hpp>
#include <gtc\matrix_transform.hpp>

#include "RenderableObject.h"
#include "Face.h"
#include "Mesh.h"

class PointMesh : public Mesh
{
public:
	PointMesh();
	~PointMesh();	

	float splatRadius_;

	//Vertex Buffers
	static const int VBID_POS = 0, VBID_NORMAL = 1, VBID_COLOUR = 2, VBID_RADIUS = 3;
	//Number of VBOs
	static const int VBOS_NUM = 4;	

	GLuint vao_;
	GLuint vbos_[4];
	int points_;
	glm::mat4 model_;

	void render();

	int getMeshType();

	GLuint* getTexture();

};


#endif

