#include "GameObject.h"

GameObject::GameObject()
{
	//No transformations applied
	modelMatrix = glm::mat4(1.0f);
}

GameObject::GameObject(glm::vec3 pos)
{
	//Apply translation to the matrix to the desired position
	modelMatrix = glm::mat4(1.0f);
	modelMatrix = glm::translate(modelMatrix, pos);
}

GameObject::~GameObject()
{
	//delete mesh_;
}

void GameObject::setPointMesh(const char * meshPath, const char * texturePath, int textureWidth, int textureHeight)
{
	mesh_ = new PointMesh();
	MeshLoader::get().loadMeshAsPoints(meshPath, texturePath, textureWidth, textureHeight, *((PointMesh *)mesh_));
}

void GameObject::setTriangMesh(const char * meshPath, const char * texturePath, int textureWidth, int textureHeight)
{
	mesh_ = new TriangMesh();
	MeshLoader::get().loadMeshAsTriang(meshPath, texturePath, textureWidth, textureHeight, *((TriangMesh *)mesh_));
}

void GameObject::render()
{
	mesh_->render();
}

int GameObject::getMeshType()
{
	return mesh_->getMeshType();
}

GLuint* GameObject::getTexture()
{
	return mesh_->getTexture();
}
