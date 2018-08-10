#ifndef RENDERABLE_OBJECT
#define RENDERABLE_OBJECT

#include <GL\glew.h>
#include <glm.hpp>
#include <string>
#include "Camera.h"

//Abstract class of renderable object
class RenderableObject
{
public:
	
	//Constructors/Destructors
	RenderableObject();
	~RenderableObject();

	//Virtual functions of RenderableObject
	virtual void render() = 0;
	virtual int getMeshType() = 0;
	virtual GLuint* getTexture() = 0;

	//Matrix containing the transformations of the model relative to the world
	glm::mat4 modelMatrix;
};

#endif

