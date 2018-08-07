#ifndef MESH_H
#define MESH_H

#include "RenderableObject.h"

class Mesh : public RenderableObject
{

public:

	static const int MESH_TYPE_TRIANGULAR = 0, MESH_TYPE_POINT = 1;

	Mesh();
	~Mesh();
};

#endif