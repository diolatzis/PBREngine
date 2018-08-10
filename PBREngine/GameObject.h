#ifndef GAME_OBJECT_H
#define GAME_OBJECT_H

#include <glm.hpp>

#include "RenderableObject.h"
#include "PointMesh.h"
#include "MeshLoader.h"
#include "Mesh.h"

class GameObject : public RenderableObject
{
	//Point/Triangular mesh
	Mesh *mesh_;

public:

	//Matrix that contains the transformations of the model relative to the world
	glm::mat4 model_;

	//Constructors/Destructors
	GameObject();
	GameObject(glm::vec3 pos);
	~GameObject();

	//Create a point mesh from an obj file and texture
	void setPointMesh(const char *meshPath, const char *texturePath, int textureWidth, int textureHeight);

	//Create a triangular mesh from an obj file and texture
	void setTriangMesh(const char *meshPath, const char *texturePath, int textureWidth, int textureHeight);

	//Implementations of RenderableObject
	void render();
	int getMeshType();	//Either triangular or point

	//Get the mesh texture
	GLuint* getTexture();
};

#endif
