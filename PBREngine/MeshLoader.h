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

private:

	//Singleton instance
	static MeshLoader *instance;

	//Constructors/Destructors
	MeshLoader();
	~MeshLoader();

public:


	//Start up and shut down functions of the subsystem
	void startUp();
	void shutDown();

	//Get the singleton instance
	static MeshLoader& get();

	//Load mesh as points from mesh
	bool loadMeshAsPoints(const char *meshPath, const char *texturePath, int textureWidth, int textureHeight, PointMesh &mesh);

	//Build the data representation of the point mesh
	void buildPointMesh(const std::vector<glm::vec3> &vertices, std::vector<glm::vec3> &normals, std::vector<Colour> &colours, std::vector<float> radii, PointMesh &mesh);

	//Load mesh as triangular mesh
	bool loadMeshAsTriang(const char *meshPath, const char *texturePath, int textureWidth, int textureHeight, TriangMesh &mesh);

	//Build the data representation of the triangular mesh
	void buildTriangMesh(const std::vector<glm::vec3> &vertices, std::vector<unsigned int> &indices, std::vector<glm::vec3> &normals, std::vector<glm::vec2> &uvs, std::vector<glm::vec4> &image, int textureWidth, int textureHeight, TriangMesh &mesh);

};

#endif

