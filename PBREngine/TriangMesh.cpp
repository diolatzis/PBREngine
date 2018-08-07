#include "TriangMesh.h"



TriangMesh::TriangMesh()
{
}


TriangMesh::~TriangMesh()
{
}

void TriangMesh::render()
{
	glBindVertexArray(vao_);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, vbos_[VBID_INDEX]);
	glDrawElements(GL_TRIANGLES,triangs_*3, GL_UNSIGNED_INT, 0);
}

int TriangMesh::getMeshType()
{
	return Mesh::MESH_TYPE_TRIANGULAR;
}

GLuint* TriangMesh::getTexture()
{
	return &texture_;
}
