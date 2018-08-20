#ifndef RENDER_MANAGER_H
#define RENDER_MANAGER_H

#include <GL\glew.h>
#include <glm.hpp>
#include <gtc\matrix_transform.hpp>
#include <iostream>
#include <vector>
#include <algorithm>
#include "RenderableObject.h"
#include "ShaderLoader.h"
#include "Gauss1D.h"
#include "Light.h"
#include "Mesh.h"


class RenderManager
{
private:

	static RenderManager *instance;

	//Constructors/Destructors
	RenderManager();
	~RenderManager();

	//Array with objects to be rendered
	std::vector<RenderableObject*> m_renderableObjs;

public:

	//Two different types of rendering splats
	static const int RENDER_TYPE_CIRCLE_SPLAT = 0, RENDER_TYPE_SQUARE_SPLAT = 1;

	//Frame buffer objects
	GLuint visibilityFBO_;
	GLuint shadowMapFBO_;
	GLuint attributeFBO_;

	//Different textures used during the multipass rendering
	GLuint depthMap_;
	GLuint shadowMap_;
	GLuint colorTex_;
	GLuint normalTex_;
	GLuint gaussTex_;

	//Point mesh rendering shaders
	GLuint visibilityProgram_, renderProgram_, squareSplatProgram_, circleSplatProgram_, depthProgram_, shadingProgram_, shadowProgram_;
	//Triangular mesh rendering shaders
	GLuint attributeTriangProgram_;


	//Start up and shut down functions of the subsystem
	void startUp(const int windowWidth, const int windowHeight);
	void shutDown();

	//Get the singleton instance
	static RenderManager& get();

	//Update the uniform buffers of a given shader
	void updateUniformBuffers(GLuint &program, Camera &camera, GLint viewport[4], const Light &light, const glm::mat4 &model);

	//Render the objects
	void render(Camera camera, GLint viewport[4], const Light &light, const int renderType);

	//Add a renderable object
	void addRenderableObj(RenderableObject * renderableObj);

	//Remove all renderable objects
	void clear();
};

#endif
