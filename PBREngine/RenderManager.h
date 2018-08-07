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
	std::vector<RenderableObject *> m_renderableObjs;

public:

	static const int RENDER_TYPE_CIRCLE_SPLAT = 0, RENDER_TYPE_SQUARE_SPLAT = 1, RENDER_TYPE_DEPTH = 2;

	GLuint visibilityFBO_;
	GLuint depthMap_;
	GLuint shadowMap_;
	GLuint shadowMapFBO_;
	GLuint attributeFBO_;
	GLuint colorTex_;
	GLuint normalTex_;
	GLuint gaussTex_;
	GLuint visibilityProgram_, renderProgram_, squareSplatProgram_, circleSplatProgram_, depthProgram_, shadingProgram_, shadowProgram_;
	GLuint visibilityTriangProgram_, attributeTriangProgram_;


	RenderManager();
	~RenderManager();

	//Initialization of manager
	void startUp(const int windowWidth, const int windowHeight);

	//Termination of manager
	void shutDown();

	//Get the singleton instance
	static RenderManager& get();

	void updateUniformBuffers(GLuint &program, const Camera &camera, GLint viewport[4], const Light &light, const glm::mat4 &model);

	void updateModelMatrix(GLuint &program, RenderableObject *obj);

	//Render the objects
	void render(Camera camera, GLint viewport[4], const Light &light, const int renderType);

	void renderSubpass(Camera camera, GLint viewport[4]);

	//Add a renderable object
	void addRenderableObj(RenderableObject * renderableObj);

	//Remove all renderable objects
	void clear();
};

#endif
