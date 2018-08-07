#ifndef MESH_LOADER_H
#define MESH_LOADER_H

#define GLEW_STATIC

#include <GL\glew.h>
#include <fstream>
#include <string>
#include <vector>
#include <iostream>
#include <sstream>
#include <iterator>
#include <algorithm>

#include "FileSystem.h"
#include "PointMesh.h"
#include "TriangMesh.h"
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
	bool loadMeshAsPoints(const char *meshPath, const char *texturePath, int textureWidth, int textureHeight, PointMesh &mesh);

	void buildPointMesh(const std::vector<glm::vec3> &vertices, std::vector<glm::vec3> &normals, std::vector<Colour> &colours, std::vector<float> radii, PointMesh &mesh);

	bool loadMeshAsTriang(const char *meshPath, const char *texturePath, int textureWidth, int textureHeight, TriangMesh &mesh);

	void buildTriangMesh(const std::vector<glm::vec3> &vertices, std::vector<unsigned int> &indices, std::vector<glm::vec3> &normals, std::vector<glm::vec2> &uvs, std::vector<glm::vec4> &image, int textureWidth, int textureHeight, TriangMesh &mesh);

};

#endif

