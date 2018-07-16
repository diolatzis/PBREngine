#ifndef RENDERABLE_OBJECT
#define RENDERABLE_OBJECT

#include <GL\glew.h>
#include <string>
#include "Camera.h"

class RenderableObject		//Abstract class of renderable object
{
public:

	RenderableObject();

	~RenderableObject();
	
	//Update the uniform buffers for the shaders
	virtual void updateUniformBuffers(Camera camera, GLint viewport[4]) = 0;

	//Render the object
	virtual void render() = 0;
};

#endif

