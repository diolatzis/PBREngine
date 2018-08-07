#ifndef RENDERABLE_OBJECT
#define RENDERABLE_OBJECT

#include <GL\glew.h>
#include <glm.hpp>
#include <string>
#include "Camera.h"

class RenderableObject		//Abstract class of renderable object
{
public:

	RenderableObject();

	~RenderableObject();

	//Render the object
	virtual void render() = 0;

	virtual int getMeshType() = 0;

	virtual GLuint* getTexture() = 0;

	glm::mat4 modelMatrix;
};

#endif

