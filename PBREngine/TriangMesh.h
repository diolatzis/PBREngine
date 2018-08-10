#ifndef TRIANG_MESH_H
#define TRIANG_MESH_H

#define GLEW_STATIC

#include <GL\glew.h>
#include <vector>
#include <glm.hpp>
#include <gtc\matrix_transform.hpp>

#include "RenderableObject.h"
#include "Mesh.h"
#include "Face.h"

class TriangMesh : public Mesh
{
public:
	//Constructors/Destructors
	TriangMesh();
	~TriangMesh();

	//Vertex Buffers
	static const int VBID_POS = 0, VBID_INDEX = 1, VBID_NORMAL = 2, VBID_UV = 3;
	//Number of VBOs
	static const int VBOS_NUM = 4;

	//Vertex array object and vertex buffer objects
	GLuint vao_;
	GLuint vbos_[4];

	//Texture of the buffer
	GLuint texture_;
	
	//Total number of points and triangles
	int points_, triangs_;

	//Mesh implementations
	void render();
	int getMeshType();
	GLuint* getTexture();
};

#endif
