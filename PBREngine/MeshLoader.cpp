#include "MeshLoader.h"


MeshLoader::MeshLoader()
{
}


MeshLoader::~MeshLoader()
{
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

bool MeshLoader::loadMesh(const char *meshPath, const char *texturePath, int textureWidth, int textureHeight, Mesh &mesh)
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
	std::vector<float> us;
	std::vector<float> vs;

	//Data for texture
	std::vector<unsigned char> image;
	unsigned width, height;

	//Load texture
	unsigned error = lodepng::decode(image, width, height, texturePath);

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

			u = stof(line.substr(0, line.find(seperator)))*textureWidth;

			line.erase(0, line.find(' ') + 1);
			v = textureHeight - stof(line.substr(0, line.find(seperator)))*textureHeight;

			us.push_back(u);
			vs.push_back(v);

			//float uInt;
			//float uFract = modf(u, &uInt);

			//float vInt;
			//float vFract = modf(v, &vInt);

			///*colour.x = Funcs::blerp(image[4 * textureWidth * (int)vInt + 4 * (int)uInt],
			//	image[4 * textureWidth * (int)vInt + 4 * (int)(uInt + 1)],
			//	image[4 * textureWidth * (int)(vInt + 1) + 4 * (int)uInt], 
			//	image[4 * textureWidth * (int)(vInt + 1) + 4 * (int)(uInt + 1)],
			//	uFract, vFract);

			//colour.y = Funcs::blerp(image[4 * textureWidth * (int)vInt + 4 * (int)uInt +1],
			//	image[4 * textureWidth * (int)vInt + 4 * (int)(uInt + 1) + 1],
			//	image[4 * textureWidth * (int)(vInt + 1) + 4 * (int)uInt + 1],
			//	image[4 * textureWidth * (int)(vInt + 1) + 4 * (int)(uInt + 1) + 1],
			//	uFract, vFract);

			//colour.z = Funcs::blerp(image[4 * textureWidth * (int)vInt + 4 * (int)uInt +2],
			//	image[4 * textureWidth * (int)vInt + 4 * (int)(uInt + 1) + 2],
			//	image[4 * textureWidth * (int)(vInt + 1) + 4 * (int)uInt +2],
			//	image[4 * textureWidth * (int)(vInt + 1) + 4 * (int)(uInt + 1) +2],
			//	uFract, vFract);*/

			//colour.x = image[4 * textureWidth * (int)vInt + 4 *(int)uInt];
			//colour.y = image[4 * textureWidth * (int)vInt + 4 *(int)uInt + 1];
			//colour.z = image[4 * textureWidth * (int)vInt + 4 *(int)uInt + 2];

			//colour /= 255.0f;

			//colours.push_back(colour);
		}	
		//Case face
		else if (line.substr(0, 2) == "f ")
		{
			line.erase(0, 2);
			
			face.v0 = stof(line.substr(0, line.find('/'))) - 1;
			line.erase(0, line.find('/') + 1);

			face.vt0 = stof(line.substr(0, line.find('/'))) - 1;
			line.erase(0, line.find('/') + 1);

			face.vn0 = stof(line.substr(0, line.find(' '))) - 1;
			line.erase(0, line.find(' ') + 1);

			face.v1 = stof(line.substr(0, line.find('/'))) - 1;
			line.erase(0, line.find('/') + 1);

			face.vt1 = stof(line.substr(0, line.find('/'))) - 1;
			line.erase(0, line.find('/') + 1);

			face.vn1 = stof(line.substr(0, line.find(' '))) - 1;
			line.erase(0, line.find(' ') + 1);

			face.v2 = stof(line.substr(0, line.find('/'))) - 1;
			line.erase(0, line.find('/') + 1);

			face.vt2 = stof(line.substr(0, line.find('/'))) - 1;
			line.erase(0, line.find('/') + 1);

			face.vn2 = stof(line.substr(0, line.find(' '))) - 1;
			line.erase(0, line.find(' ') + 1);

			faces.push_back(face);
		}
	}

	//Add the normals for each vertex from the faces
	normals.resize(vertices.size());
	colours.resize(vertices.size());

	for (int i = 0; i < faces.size(); i++)
	{
		normals[faces[i].v0] += faceNormals[faces[i].vn0];

		normals[faces[i].v1] += faceNormals[faces[i].vn1];

		normals[faces[i].v2] += faceNormals[faces[i].vn2];

		float u = us[faces[i].vt0];
		float v = vs[faces[i].vt0];

		colours[faces[i].v0].x = image[4 * textureWidth * (int)v + 4 *(int)u];
		colours[faces[i].v0].y = image[4 * textureWidth * (int)v + 4 *(int)u + 1];
		colours[faces[i].v0].z = image[4 * textureWidth * (int)v + 4 *(int)u + 2];


		colours[faces[i].v0] /= 255.0f;

		u = us[faces[i].vt1];
		v = vs[faces[i].vt1];

		colours[faces[i].v1].x = image[4 * textureWidth * (int)v + 4 * (int)u];
		colours[faces[i].v1].y = image[4 * textureWidth * (int)v + 4 * (int)u + 1];
		colours[faces[i].v1].z = image[4 * textureWidth * (int)v + 4 * (int)u + 2];



		colours[faces[i].v1] /= 255.0f;

		u = us[faces[i].vt2];
		v = vs[faces[i].vt2];

		colours[faces[i].v2].x = image[4 * textureWidth * (int)v + 4 * (int)u];
		colours[faces[i].v2].y = image[4 * textureWidth * (int)v + 4 * (int)u + 1];
		colours[faces[i].v2].z = image[4 * textureWidth * (int)v + 4 * (int)u + 2];



		colours[faces[i].v2] /= 255.0f;




	}

	//Normalize
	for (int i = 0; i < normals.size(); i++)
	{
		normals[i] = glm::normalize(normals[i]);
	}
	
	buildMesh(vertices, normals, colours, mesh);

	return true;
}

void MeshLoader::buildMesh(const std::vector<glm::vec3>& vertices, std::vector<glm::vec3>& normals, std::vector<Colour>& colours, Mesh & mesh)
{
	mesh.pointsNum = vertices.size();

	//Create VAO
	glGenVertexArrays(1, &mesh.vao);

	//Enable VAO
	glBindVertexArray(mesh.vao);

	//Generate VBO buffers
	glGenBuffers(Mesh::VBOS_NUM, mesh.vbos);

	//Positions
	glBindBuffer(GL_ARRAY_BUFFER, mesh.vbos[Mesh::VBID_POS]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices[0])*vertices.size(), vertices.data(), GL_STATIC_DRAW);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);

	//Normals
	glBindBuffer(GL_ARRAY_BUFFER, mesh.vbos[Mesh::VBID_NORMAL]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(normals[0])*normals.size(), normals.data(), GL_STATIC_DRAW);
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, 0);

	//Colours
	glBindBuffer(GL_ARRAY_BUFFER, mesh.vbos[Mesh::VBID_COLOUR]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(colours[0])*colours.size(), colours.data(), GL_STATIC_DRAW);
	glEnableVertexAttribArray(2);
	glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 0, 0);

	//Disable VAO
	glBindVertexArray(0);
}
