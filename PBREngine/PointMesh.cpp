#include "PointMesh.h"

PointMesh::PointMesh()
{
}

PointMesh::~PointMesh()
{
}

void PointMesh::render()
{	
	glBindVertexArray(vao_);

	glDrawArrays(GL_POINTS,0,points_);
}

int PointMesh::getMeshType()
{
	return Mesh::MESH_TYPE_POINT;
}

GLuint* PointMesh::getTexture()
{
	//Point meshes don't use textures
	return nullptr;
}

