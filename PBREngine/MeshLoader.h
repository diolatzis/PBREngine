#ifndef MESH_LOADER_H
#define MESH_LOADER_H

#define GLEW_STATIC

#include <GL\glew.h>
#include <fstream>
#include <string>
#include <vector>

#include "FileSystem.h"
#include "Mesh.h"
#include "lodepng.h"
#include "Face.h"
#include "Funcs.h"


class MeshLoader
{

public:
	MeshLoader();
	~MeshLoader();


	void startUp();
	void shutDown();

	//Get the singleton instance
	static MeshLoader& get();

	//Load mesh from .obj
	bool loadMesh(const char *meshPath, const char *texturePath, int textureWidth, int textureHeight, Mesh &mesh);

	void buildMesh(const std::vector<glm::vec3> &vertices, std::vector<glm::vec3> &normals, std::vector<Colour> &colours, Mesh &mesh);
	
};

#endif

