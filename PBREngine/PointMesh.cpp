#include "PointMesh.h"



PointMesh::PointMesh()
{
	modelMatrix = glm::mat4(1.0f);
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
	return nullptr;
}

