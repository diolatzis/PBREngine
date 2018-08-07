#ifndef GAME_OBJECT_H
#define GAME_OBJECT_H

#include <glm.hpp>

#include "RenderableObject.h"
#include "PointMesh.h"
#include "MeshLoader.h"
#include "Mesh.h"

class GameObject : public RenderableObject
{
	Mesh *mesh_;

public:

	glm::mat4 model_;

	GameObject();
	~GameObject();

	void setPointMesh(const char *meshPath, const char *texturePath, int textureWidth, int textureHeight);

	void setTriangMesh(const char *meshPath, const char *texturePath, int textureWidth, int textureHeight);

	void render();

	int getMeshType();

	GLuint* getTexture();
};

#endif
