#include "MeshLoader.h"


MeshLoader::MeshLoader()
{
	//DO NOTHING
}


MeshLoader::~MeshLoader()
{
	//DO NOTHING
}

void MeshLoader::startUp()
{
	FileSystem::get().startUp();
}

void MeshLoader::shutDown()
{
	FileSystem::get().shutDown();
}

MeshLoader & MeshLoader::get()
{
	static MeshLoader* instance = NULL;
	if (instance == NULL)
	{
		instance = new MeshLoader();
	}
	_ASSERT(instance);
	return *instance;
}

bool MeshLoader::loadMeshAsPoints(const char *meshPath, const char *texturePath, int textureWidth, int textureHeight, PointMesh &mesh)
{	
	//Open obj file
	std::ifstream file;
	FileSystem::get().syncOpenFile(meshPath, file);

	std::string line;
	char seperator = ' ';

	//Data to be filled by each line
	glm::vec3 pos;
	glm::vec3 normal;
	std::vector<glm::vec3> faceNormals;
	std::vector<Face> faces;
	float u,v;
	Colour colour;
	Face face;

	//Mesh data
	std::vector<glm::vec3> vertices;
	std::vector<glm::vec3> normals;
	std::vector<Colour> colours;
	std::vector<float> radii;
	std::vector<float> us;
	std::vector<float> vs;

	//Data for texture
	std::vector<unsigned char> image;
	unsigned width, height;

	//Load texture
	unsigned error = lodepng::decode(image, width, height, texturePath);

	if (error != 0)
	{
		printf("Error loading texture.\n");
		return false;
	}

	//Read data from obj
	while (std::getline(file, line))
	{
		//Case vertex
		if (line.substr(0, 2) == "v ")
		{
			line.erase(0, 2);

			pos.x = stof(line.substr(0, line.find(seperator)));

			line.erase(0, line.find(' ') + 1);
			pos.y = stof(line.substr(0, line.find(seperator)));

			line.erase(0, line.find(' ') + 1);
			pos.z = stof(line.substr(0, line.find(seperator)));

			vertices.push_back(pos);
			radii.push_back(0.0f);
		}
		//Case normal
		else if (line.substr(0, 2) == "vn")
		{
			line.erase(0, 3);

			normal.x = stof(line.substr(0, line.find(seperator)));

			line.erase(0, line.find(' ') + 1);
			normal.y = stof(line.substr(0, line.find(seperator)));

			line.erase(0, line.find(' ') + 1);
			normal.z = stof(line.substr(0, line.find(seperator)));

			faceNormals.push_back(normal);
		}
		//Case texture coords
		else if (line.substr(0, 2) == "vt")
		{
			line.erase(0, 3);

			u = abs(stof(line.substr(0, line.find(seperator))))*textureWidth;

			line.erase(0, line.find(' ') + 1);
			v = abs(textureHeight - stof(line.substr(0, line.find(seperator)))*textureHeight);

			//If texture coordinates are bigger than 1
			if (u > textureWidth-5) u = textureWidth-5;
			if (v > textureHeight-5) v = textureHeight-5;

			us.push_back(u);
			vs.push_back(v);
		}	
		//Case face
		else if (line.substr(0, 2) == "f ")
		{
			size_t backslashesNum = std::count(line.begin(), line.end(), '/');

			//Faces are not represented in the supported format
			if (backslashesNum == 6)
			{
				line.erase(0, 2);

				//Face 0
				face.v0_ = stof(line.substr(0, line.find('/'))) - 1;
				line.erase(0, line.find('/') + 1);

				face.vt0_ = stof(line.substr(0, line.find('/'))) - 1;
				line.erase(0, line.find('/') + 1);

				face.vn0_ = stof(line.substr(0, line.find(' '))) - 1;
				line.erase(0, line.find(' ') + 1);

				//Face 1
				face.v1_ = stof(line.substr(0, line.find('/'))) - 1;
				line.erase(0, line.find('/') + 1);

				face.vt1_ = stof(line.substr(0, line.find('/'))) - 1;
				line.erase(0, line.find('/') + 1);

				face.vn1_ = stof(line.substr(0, line.find(' '))) - 1;
				line.erase(0, line.find(' ') + 1);

				//Face 2
				face.v2_ = stof(line.substr(0, line.find('/'))) - 1;
				line.erase(0, line.find('/') + 1);

				face.vt2_ = stof(line.substr(0, line.find('/'))) - 1;
				line.erase(0, line.find('/') + 1);

				face.vn2_ = stof(line.substr(0, line.find(' '))) - 1;
				line.erase(0, line.find(' ') + 1);

				faces.push_back(face);
			}

			if (backslashesNum == 3)
			{
				line.erase(0, 2);

				//Face 0
				face.v0_ = stof(line.substr(0, line.find('/'))) - 1;
				line.erase(0, line.find('/') + 1);

				face.vt0_ = stof(line.substr(0, line.find(' '))) - 1;
				line.erase(0, line.find(' ') + 1);

				face.vn0_ = -1;

				//Face 1
				face.v1_ = stof(line.substr(0, line.find('/'))) - 1;
				line.erase(0, line.find('/') + 1);

				face.vt1_ = stof(line.substr(0, line.find(' '))) - 1;
				line.erase(0, line.find(' ') + 1); 

				face.vn1_ = -1;

				//Face 2
				face.v2_ = stof(line.substr(0, line.find('/'))) - 1;
				line.erase(0, line.find('/') + 1);

				face.vt2_ = stof(line.substr(0, line.find(' '))) - 1;
				line.erase(0, line.find(' ') + 1);

				face.vn2_ = -1;

				faces.push_back(face);
			}

			
		}
	}

	//Add the normals for each vertex from the faces
	normals.resize(vertices.size());
	colours.resize(vertices.size());

	for (int i = 0; i < faces.size(); i++)
	{
		if (faces[i].vn0_ == -1)
		{
			normals[faces[i].v0_] = faceNormals[faces[i].v0_];
			normals[faces[i].v1_] = faceNormals[faces[i].v1_];
			normals[faces[i].v2_] = faceNormals[faces[i].v2_];
		}
		else
		{
			//Sum up the normal values associated with each vertex
			normals[faces[i].v0_] += faceNormals[faces[i].vn0_];

			normals[faces[i].v1_] += faceNormals[faces[i].vn1_];

			normals[faces[i].v2_] += faceNormals[faces[i].vn2_];
		}



		//Compute distances between each vertex
		float distV0V1 = glm::distance(vertices[faces[i].v0_], vertices[faces[i].v1_]);
		float distV0V2 = glm::distance(vertices[faces[i].v0_], vertices[faces[i].v2_]);
		float distV1V2 = glm::distance(vertices[faces[i].v1_], vertices[faces[i].v2_]);

		//Save the maximum distance of each vertex
		if (distV0V1 > radii[faces[i].v0_])
			radii[faces[i].v0_] = distV0V1;

		if (distV0V2 > radii[faces[i].v0_])
			radii[faces[i].v0_] = distV0V2;

		if (distV0V1 > radii[faces[i].v1_])
			radii[faces[i].v1_] = distV0V1;

		if (distV1V2 > radii[faces[i].v1_])
			radii[faces[i].v1_] = distV1V2;

		if (distV0V2 > radii[faces[i].v2_])
			radii[faces[i].v2_] = distV0V2;

		if (distV1V2 > radii[faces[i].v2_])
			radii[faces[i].v2_] = distV1V2;


		if (glm::distance(vertices[faces[i].v0_], vertices[faces[i].v1_]) > radii[faces[i].v0_])
			radii[faces[i].v0_] = glm::distance(vertices[faces[i].v0_], vertices[faces[i].v1_]);


		//Use bilinear interpolation to compute the color from the texture

		//Vertex 0
		float u = us[faces[i].vt0_];
		float v = vs[faces[i].vt0_];

		float uInt;
		float uFract = modf(u, &uInt);

		float vInt;
		float vFract = modf(v, &vInt);

		
		colours[faces[i].v0_].x = Funcs::blerp(image[4 * textureWidth * (int)v + 4 *(int)u], image[4 * textureWidth * (int)v + 4 * (int)(u+1)], image[4 * textureWidth * (int)(v+1) + 4 * (int)u], image[4 * textureWidth * (int)(v+1) + 4 * (int)(u+1)], uFract, vFract);
		colours[faces[i].v0_].y = Funcs::blerp(image[4 * textureWidth * (int)v + 4 * (int)u + 1], image[4 * textureWidth * (int)v + 4 * (int)(u + 1) + 1], image[4 * textureWidth * (int)(v + 1) + 4 * (int)u + 1], image[4 * textureWidth * (int)(v + 1) + 4 * (int)(u + 1) + 1], uFract, vFract);
		colours[faces[i].v0_].z = Funcs::blerp(image[4 * textureWidth * (int)v + 4 * (int)u + 2], image[4 * textureWidth * (int)v + 4 * (int)(u + 1) + 2], image[4 * textureWidth * (int)(v + 1) + 4 * (int)u + 2], image[4 * textureWidth * (int)(v + 1) + 4 * (int)(u + 1) + 2], uFract, vFract);

		colours[faces[i].v0_] /= 255.0f;


		//Vertex 1
		u = us[faces[i].vt1_];
		v = vs[faces[i].vt1_];


		uFract = modf(u, &uInt); 
		vFract = modf(v, &vInt);
		
		colours[faces[i].v1_].x = Funcs::blerp(image[4 * textureWidth * (int)v + 4 * (int)u], image[4 * textureWidth * (int)v + 4 * (int)(u + 1)], image[4 * textureWidth * (int)(v + 1) + 4 * (int)u], image[4 * textureWidth * (int)(v + 1) + 4 * (int)(u + 1)], uFract, vFract);
		colours[faces[i].v1_].y = Funcs::blerp(image[4 * textureWidth * (int)v + 4 * (int)u + 1], image[4 * textureWidth * (int)v + 4 * (int)(u + 1) + 1], image[4 * textureWidth * (int)(v + 1) + 4 * (int)u + 1], image[4 * textureWidth * (int)(v + 1) + 4 * (int)(u + 1) + 1], uFract, vFract);
		colours[faces[i].v1_].z = Funcs::blerp(image[4 * textureWidth * (int)v + 4 * (int)u + 2], image[4 * textureWidth * (int)v + 4 * (int)(u + 1) + 2], image[4 * textureWidth * (int)(v + 1) + 4 * (int)u + 2], image[4 * textureWidth * (int)(v + 1) + 4 * (int)(u + 1) + 2], uFract, vFract);

		colours[faces[i].v1_] /= 255.0f;


		//Vertex 2
		u = us[faces[i].vt2_];
		v = vs[faces[i].vt2_];

		uFract = modf(u, &uInt);
		vFract = modf(v, &vInt);

		colours[faces[i].v2_].x = Funcs::blerp(image[4 * textureWidth * (int)v + 4 * (int)u], image[4 * textureWidth * (int)v + 4 * (int)(u + 1)], image[4 * textureWidth * (int)(v + 1) + 4 * (int)u], image[4 * textureWidth * (int)(v + 1) + 4 * (int)(u + 1)], uFract, vFract);
		colours[faces[i].v2_].y = Funcs::blerp(image[4 * textureWidth * (int)v + 4 * (int)u + 1], image[4 * textureWidth * (int)v + 4 * (int)(u + 1) + 1], image[4 * textureWidth * (int)(v + 1) + 4 * (int)u + 1], image[4 * textureWidth * (int)(v + 1) + 4 * (int)(u + 1) + 1], uFract, vFract);
		colours[faces[i].v2_].z = Funcs::blerp(image[4 * textureWidth * (int)v + 4 * (int)u + 2], image[4 * textureWidth * (int)v + 4 * (int)(u + 1) + 2], image[4 * textureWidth * (int)(v + 1) + 4 * (int)u + 2], image[4 * textureWidth * (int)(v + 1) + 4 * (int)(u + 1) + 2], uFract, vFract);


		colours[faces[i].v2_] /= 255.0f;
	}

	//Normalize the normals
	for (int i = 0; i < normals.size(); i++)
	{
		normals[i] = glm::normalize(normals[i]);
	}
	
	buildPointMesh(vertices, normals, colours, radii, mesh);

	return true;
}

void MeshLoader::buildPointMesh(const std::vector<glm::vec3>& vertices, std::vector<glm::vec3>& normals, std::vector<Colour>& colours, std::vector<float> radii, PointMesh & mesh)
{
	mesh.points_ = vertices.size();

	//Create VAO
	glGenVertexArrays(1, &mesh.vao_);

	//Enable VAO
	glBindVertexArray(mesh.vao_);

	//Generate VBO buffers
	glGenBuffers(PointMesh::VBOS_NUM, mesh.vbos_);

	//Positions
	glBindBuffer(GL_ARRAY_BUFFER, mesh.vbos_[PointMesh::VBID_POS]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices[0])*vertices.size(), vertices.data(), GL_STATIC_DRAW);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);

	//Normals
	glBindBuffer(GL_ARRAY_BUFFER, mesh.vbos_[PointMesh::VBID_NORMAL]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(normals[0])*normals.size(), normals.data(), GL_STATIC_DRAW);
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, 0);

	//Colours
	glBindBuffer(GL_ARRAY_BUFFER, mesh.vbos_[PointMesh::VBID_COLOUR]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(colours[0])*colours.size(), colours.data(), GL_STATIC_DRAW);
	glEnableVertexAttribArray(2);
	glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 0, 0);

	//Radii
	glBindBuffer(GL_ARRAY_BUFFER, mesh.vbos_[PointMesh::VBID_RADIUS]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(radii[0])*radii.size(), radii.data(), GL_STATIC_DRAW);
	glEnableVertexAttribArray(3);
	glVertexAttribPointer(3, 1, GL_FLOAT, GL_FALSE, 0, 0);

	//Disable VAO
	glBindVertexArray(0);
}

bool MeshLoader::loadMeshAsTriang(const char * meshPath, const char * texturePath, int textureWidth, int textureHeight, TriangMesh & mesh)
{
	//Open obj file
	std::ifstream file;
	FileSystem::get().syncOpenFile(meshPath, file);

	std::string line;
	char seperator = ' ';

	//Data to be filled by each line
	glm::vec3 pos;
	glm::vec3 normal;
	std::vector<glm::vec3> faceNormals;
	std::vector<glm::vec2> faceUVs;
	std::vector<Face> faces;
	float u, v;
	Colour colour;
	Face face;

	//Mesh data
	std::vector<glm::vec3> vertices;
	std::vector<glm::vec3> normals;
	std::vector<unsigned int> indices;
	std::vector<glm::vec2> uvs;

	//Data for texture
	std::vector<unsigned char> image;
	std::vector<glm::vec4> imageData;
	unsigned width, height;

	//Load texture
	unsigned error = lodepng::decode(image, width, height, texturePath);

	for (int i = 0; i < image.size(); i += 4)
	{
		imageData.push_back(glm::vec4(image[i]/255.0f, image[i + 1] / 255.0f, image[i + 2] / 255.0f, image[i + 3] / 255.0f));
	}

	if (error != 0)
	{
		printf("Error loading texture.\n");
		return false;
	}

	//Read data from obj
	while (std::getline(file, line))
	{
		//Case vertex
		if (line.substr(0, 2) == "v ")
		{
			line.erase(0, 2);

			pos.x = stof(line.substr(0, line.find(seperator)));

			line.erase(0, line.find(' ') + 1);
			pos.y = stof(line.substr(0, line.find(seperator)));

			line.erase(0, line.find(' ') + 1);
			pos.z = stof(line.substr(0, line.find(seperator)));

			vertices.push_back(pos);
		}
		//Case normal
		else if (line.substr(0, 2) == "vn")
		{
			line.erase(0, 3);

			normal.x = stof(line.substr(0, line.find(seperator)));

			line.erase(0, line.find(' ') + 1);
			normal.y = stof(line.substr(0, line.find(seperator)));

			line.erase(0, line.find(' ') + 1);
			normal.z = stof(line.substr(0, line.find(seperator)));

			faceNormals.push_back(normal);
		}
		//Case texture coords
		else if (line.substr(0, 2) == "vt")
		{
			line.erase(0, 3);

			u = abs(stof(line.substr(0, line.find(seperator))))*textureWidth;

			line.erase(0, line.find(' ') + 1);
			v = abs(textureHeight - stof(line.substr(0, line.find(seperator)))*textureHeight);

			//If texture coordinates are bigger than 1
			if (u > textureWidth - 5) u = textureWidth - 5;
			if (v > textureHeight - 5) v = textureHeight - 5;

			faceUVs.push_back(glm::vec2(u, v));
		}
		//Case face
		else if (line.substr(0, 2) == "f ")
		{
			size_t backslashesNum = std::count(line.begin(), line.end(), '/');

			//Faces are not represented in the supported format
			if (backslashesNum == 6)
			{
				line.erase(0, 2);

				//Face 0
				face.v0_ = stof(line.substr(0, line.find('/'))) - 1;
				line.erase(0, line.find('/') + 1);

				face.vt0_ = stof(line.substr(0, line.find('/'))) - 1;
				line.erase(0, line.find('/') + 1);

				face.vn0_ = stof(line.substr(0, line.find(' '))) - 1;
				line.erase(0, line.find(' ') + 1);

				//Face 1
				face.v1_ = stof(line.substr(0, line.find('/'))) - 1;
				line.erase(0, line.find('/') + 1);

				face.vt1_ = stof(line.substr(0, line.find('/'))) - 1;
				line.erase(0, line.find('/') + 1);

				face.vn1_ = stof(line.substr(0, line.find(' '))) - 1;
				line.erase(0, line.find(' ') + 1);

				//Face 2
				face.v2_ = stof(line.substr(0, line.find('/'))) - 1;
				line.erase(0, line.find('/') + 1);

				face.vt2_ = stof(line.substr(0, line.find('/'))) - 1;
				line.erase(0, line.find('/') + 1);

				face.vn2_ = stof(line.substr(0, line.find(' '))) - 1;
				line.erase(0, line.find(' ') + 1);

				faces.push_back(face);
			}

			if (backslashesNum == 3)
			{
				line.erase(0, 2);

				//Face 0
				face.v0_ = stof(line.substr(0, line.find('/'))) - 1;
				line.erase(0, line.find('/') + 1);

				face.vt0_ = stof(line.substr(0, line.find(' '))) - 1;
				line.erase(0, line.find(' ') + 1);

				face.vn0_ = -1;

				//Face 1
				face.v1_ = stof(line.substr(0, line.find('/'))) - 1;
				line.erase(0, line.find('/') + 1);

				face.vt1_ = stof(line.substr(0, line.find(' '))) - 1;
				line.erase(0, line.find(' ') + 1);

				face.vn1_ = -1;

				//Face 2
				face.v2_ = stof(line.substr(0, line.find('/'))) - 1;
				line.erase(0, line.find('/') + 1);

				face.vt2_ = stof(line.substr(0, line.find(' '))) - 1;
				line.erase(0, line.find(' ') + 1);

				face.vn2_ = -1;

				faces.push_back(face);
			}


		}
	}

	//Add the normals for each vertex from the faces
	normals.resize(vertices.size());
	uvs.resize(vertices.size());
	

	for (int i = 0; i < faces.size(); i++)
	{
		indices.push_back(faces[i].v0_);
		indices.push_back(faces[i].v1_);
		indices.push_back(faces[i].v2_);

		uvs[faces[i].v0_] = faceUVs[faces[i].vt0_];
		uvs[faces[i].v1_] = faceUVs[faces[i].vt1_];
		uvs[faces[i].v2_] = faceUVs[faces[i].vt2_];


		if (faces[i].vn0_ == -1)
		{
			normals[faces[i].v0_] = faceNormals[faces[i].v0_];
			normals[faces[i].v1_] = faceNormals[faces[i].v1_];
			normals[faces[i].v2_] = faceNormals[faces[i].v2_];
		}
		else
		{
			//Sum up the normal values associated with each vertex
			normals[faces[i].v0_] += faceNormals[faces[i].vn0_];

			normals[faces[i].v1_] += faceNormals[faces[i].vn1_];

			normals[faces[i].v2_] += faceNormals[faces[i].vn2_];
		}
	}

	//Normalize the normals
	for (int i = 0; i < normals.size(); i++)
	{
		normals[i] = glm::normalize(normals[i]);
	}

	buildTriangMesh(vertices, indices, normals, uvs, imageData, textureWidth, textureHeight, mesh);

	return true;
}

void MeshLoader::buildTriangMesh(const std::vector<glm::vec3>& vertices, std::vector<unsigned int>& indices, std::vector<glm::vec3>& normals, std::vector<glm::vec2>& uvs, std::vector<glm::vec4> &texture, int textureWidth, int textureHeight, TriangMesh & mesh)
{
	mesh.points_ = vertices.size();
	mesh.triangs_ = indices.size();

	//Create VAO
	glGenVertexArrays(1, &mesh.vao_);

	//Enable VAO
	glBindVertexArray(mesh.vao_);

	//Generate VBO buffers
	glGenBuffers(TriangMesh::VBOS_NUM, mesh.vbos_);

	//Positions
	glBindBuffer(GL_ARRAY_BUFFER, mesh.vbos_[TriangMesh::VBID_POS]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices[0])*vertices.size(), vertices.data(), GL_STATIC_DRAW);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);

	//Indices
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mesh.vbos_[TriangMesh::VBID_INDEX]);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices[0])*indices.size(), indices.data(), GL_STATIC_DRAW);

	//Normals
	glBindBuffer(GL_ARRAY_BUFFER, mesh.vbos_[TriangMesh::VBID_NORMAL]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(normals[0])*normals.size(), normals.data(), GL_STATIC_DRAW);
	glEnableVertexAttribArray(2);
	glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 0, 0);

	//UVs
	glBindBuffer(GL_ARRAY_BUFFER, mesh.vbos_[TriangMesh::VBID_UV]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(uvs[0])*uvs.size(), uvs.data(), GL_STATIC_DRAW);
	glEnableVertexAttribArray(3);
	glVertexAttribPointer(3, 2, GL_FLOAT, GL_FALSE, 0, 0);

	//Texture
	glGenTextures(1, &mesh.texture_);
	glBindTexture(GL_TEXTURE_2D, mesh.texture_);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA32F, textureWidth, textureHeight, 0, GL_RGBA, GL_FLOAT, texture.data());	
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

	//Disable VAO
	glBindVertexArray(0);
}

