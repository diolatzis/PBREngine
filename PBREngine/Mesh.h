#ifndef MESH_H
#define MESH_H

#include "RenderableObject.h"

class Mesh : public RenderableObject
{

public:

	//Types of meshes
	static const int MESH_TYPE_TRIANGULAR = 0, MESH_TYPE_POINT = 1;

	//Constructors/Destructors
	Mesh();
	~Mesh();
};

#endif