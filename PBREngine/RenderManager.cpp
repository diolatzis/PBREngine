#include "RenderManager.h"

//Color targets during attribute pass
static const GLenum attributeBuffers[] =
{
	GL_COLOR_ATTACHMENT0,
	GL_COLOR_ATTACHMENT1
};

RenderManager::RenderManager()
{
}

RenderManager::~RenderManager()
{
}

RenderManager & RenderManager::get()
{
	static RenderManager* instance = NULL;
	if (instance == NULL)
	{
		instance = new RenderManager();
	}
	_ASSERT(instance);
	return *instance;
}

void RenderManager::updateUniformBuffers(GLuint &program, Camera &camera, GLint viewport[4], const Light &light, const glm::mat4 &model)
{
	//Build and update uniform matrices
	glm::mat4 view, projection, invProj;

	//Camera view and projection
	view = glm::lookAt(camera.pos_, camera.getTarget(), camera.up_);
	projection = glm::perspective(glm::radians(camera.fov_), (float)viewport[2] / (float)viewport[3], camera.nearZ_, camera.farZ_);

	invProj = glm::inverse(projection);

	glm::mat4 lightView, lightProj;

	//Light view and projection
	lightView = glm::lookAt(light.pos_, light.targetPos_, camera.up_);
	lightProj = glm::ortho(-10.0f, 10.0f, -10.0f, 10.0f, camera.nearZ_, camera.farZ_);

	//Get uniform variables location in shaders
	GLint modelLoc = glGetUniformLocation(program, "model");
	GLint viewLoc = glGetUniformLocation(program, "view");
	GLint projLoc = glGetUniformLocation(program, "proj");
	GLint viewportLoc = glGetUniformLocation(program, "viewport");
	GLint invProjLoc = glGetUniformLocation(program, "invProj");
	GLint zNearLoc = glGetUniformLocation(program, "zNear");
	GLint zFarLoc = glGetUniformLocation(program, "zFar");

	GLint lightPosLoc = glGetUniformLocation(program, "lightPos");
	GLint lightViewLoc = glGetUniformLocation(program, "lightView");
	GLint lightProjLoc = glGetUniformLocation(program, "lightProj");
	GLint ambientLoc = glGetUniformLocation(program, "ambient");
	GLint diffuseLoc = glGetUniformLocation(program, "diffuse");
	GLint specularLoc = glGetUniformLocation(program, "specular");
	GLint specularPowerLoc = glGetUniformLocation(program, "specularPower");

	//Pass the uniform variables values to the shaders
	glUniformMatrix4fv(modelLoc, 1, GL_FALSE, &model[0][0]);
	glUniformMatrix4fv(viewLoc, 1, GL_FALSE, &view[0][0]);
	glUniformMatrix4fv(projLoc, 1, GL_FALSE, &projection[0][0]);
	glUniform4f(viewportLoc, viewport[0], viewport[1], viewport[2], viewport[3]);
	glUniformMatrix4fv(invProjLoc, 1, GL_FALSE, &invProj[0][0]);
	glUniform1f(zNearLoc, camera.nearZ_);
	glUniform1f(zFarLoc, camera.farZ_);

	glUniform3f(lightPosLoc, light.pos_[0], light.pos_[1], light.pos_[2]);
	glUniformMatrix4fv(lightViewLoc, 1, GL_FALSE, &lightView[0][0]);
	glUniformMatrix4fv(lightProjLoc, 1, GL_FALSE, &lightProj[0][0]);
	glUniform3f(ambientLoc, light.ambient_[0], light.ambient_[1], light.ambient_[2]);
	glUniform3f(diffuseLoc, light.diffuse_[0], light.diffuse_[1], light.diffuse_[2]);
	glUniform3f(specularLoc, light.specular_[0], light.specular_[1], light.specular_[2]);
	glUniform1f(specularPowerLoc, light.specularPower_);
}

void RenderManager::startUp(const int windowWidth, const int windowHeight)
{
	//Initialize visibility frame buffer object
	glGenFramebuffers(1, &visibilityFBO_);
	glBindFramebuffer(GL_FRAMEBUFFER, visibilityFBO_);

	//Initialize depth map texture
	glGenTextures(1, &depthMap_);
	glBindTexture(GL_TEXTURE_2D, depthMap_);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH_COMPONENT32, windowWidth, windowHeight, 0, GL_DEPTH_COMPONENT, GL_FLOAT, 0);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

	//Connect depth map with the depth attachment of the framebuffer
	glFramebufferTexture(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, depthMap_, 0);
	glDrawBuffer(GL_NONE);

	//Reset the frame buffer
	glBindFramebuffer(GL_FRAMEBUFFER, 0);

	//Initialize shadow map frame buffer object
	glGenFramebuffers(1, &shadowMapFBO_);
	glBindFramebuffer(GL_FRAMEBUFFER, shadowMapFBO_);

	//Initialize shadow map texture
	glGenTextures(1, &shadowMap_);
	glBindTexture(GL_TEXTURE_2D, shadowMap_);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH_COMPONENT32, windowWidth, windowHeight, 0, GL_DEPTH_COMPONENT, GL_FLOAT, 0);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

	//Connect shadow map with the depth attachment of the framebuffer
	glFramebufferTexture(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, shadowMap_, 0);
	glDrawBuffer(GL_NONE);

	//Reset the frame buffer
	glBindFramebuffer(GL_FRAMEBUFFER, 0);


	//Initialize attribute frame buffer object
	glGenFramebuffers(1, &attributeFBO_);
	glBindFramebuffer(GL_FRAMEBUFFER, attributeFBO_);

	//Initialize color texture
	glGenTextures(1, &colorTex_);
	glBindTexture(GL_TEXTURE_2D, colorTex_);	
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA32F, windowWidth, windowHeight, 0, GL_RGBA, GL_FLOAT, 0);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glFramebufferTexture(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, colorTex_, 0);

	//Initialize normal texture
	glGenTextures(1, &normalTex_);
	glBindTexture(GL_TEXTURE_2D, normalTex_);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA32F, windowWidth, windowHeight, 0, GL_RGBA, GL_FLOAT, 0);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glFramebufferTexture(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT1, normalTex_, 0);

	//Reset the color attachments
	glDrawBuffer(GL_NONE);

	//Reset the frame buffer
	glBindFramebuffer(GL_FRAMEBUFFER, 0);

	//Initialize 1D gauss texture
	glGenTextures(1, &gaussTex_);
	glBindTexture(GL_TEXTURE_1D, gaussTex_);
	glTexImage1D(GL_TEXTURE_1D, 0, GL_R32F, 40, 0, GL_RED, GL_FLOAT, Gauss1D::values);
	glTexParameteri(GL_TEXTURE_1D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_1D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_1D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_1D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

	//Load the shaders
	ShaderLoader::get().setShader(visibilityProgram_, "../shaders/visibility");
	ShaderLoader::get().setShader(squareSplatProgram_, "../shaders/square_splatting");
	ShaderLoader::get().setShader(circleSplatProgram_, "../shaders/circle_splatting");
	ShaderLoader::get().setShader(shadingProgram_, "../shaders/shading");
	ShaderLoader::get().setShader(shadowProgram_, "../shaders/shadow");
	ShaderLoader::get().setShader(attributeTriangProgram_, "../shaders/attribute_triang");

}

void RenderManager::shutDown()
{
}

void RenderManager::render(Camera camera, GLint viewport[4], const Light &light, const int renderType)
{
	//------------------ VISIBILITY PASS ------------------//
	
	//No blending during this pass
	glDisable(GL_BLEND);

	//Enable the depth test and depth write
	glEnable(GL_DEPTH_TEST);
	glDepthMask(GL_TRUE);

	glBindFramebuffer(GL_FRAMEBUFFER, visibilityFBO_);

	glClear(GL_DEPTH_BUFFER_BIT);
	 
	for (RenderableObject *obj : m_renderableObjs)
	{
		glUseProgram(visibilityProgram_);

		updateUniformBuffers(visibilityProgram_, camera, viewport, light, obj->modelMatrix);

		obj->render();
	}

	//------------------ SHADOW MAP PASS ------------------//

	glBindFramebuffer(GL_FRAMEBUFFER, shadowMapFBO_);

	glClear(GL_DEPTH_BUFFER_BIT);

	for (RenderableObject *obj : m_renderableObjs)
	{
		glUseProgram(shadowProgram_);

		updateUniformBuffers(shadowProgram_, camera, viewport, light, obj->modelMatrix);

		obj->render();
	}

	//------------------ ATTRIBUTE PASS ------------------//


	glBindFramebuffer(GL_FRAMEBUFFER, attributeFBO_);

	glClearTexImage(colorTex_, 0, GL_RGBA, GL_FLOAT, 0);
	glClearTexImage(normalTex_, 0, GL_RGBA, GL_FLOAT, 0);
	glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);
	glClearColor(0.2f, 0.2f, 0.4f, 1.0f);

	GLuint currentProgram;

	//Enable alpha blending during this pass
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	
	//Disable depth testing during this pass since we use the depth map
	glDisable(GL_DEPTH_TEST);
	glDepthMask(GL_FALSE);
	glDrawBuffers(2, attributeBuffers);

	for (RenderableObject *obj : m_renderableObjs)
	{
		//Use the appropriate shader depending on the type of mesh and render method in the case of points
		switch (obj->getMeshType())
		{
		case Mesh::MESH_TYPE_POINT:
			if (renderType == RENDER_TYPE_SQUARE_SPLAT)
				currentProgram = squareSplatProgram_;
			if (renderType == RENDER_TYPE_CIRCLE_SPLAT)
				currentProgram = circleSplatProgram_;
			break;
		case Mesh::MESH_TYPE_TRIANGULAR:
			currentProgram = attributeTriangProgram_;
			break;
		}

		glUseProgram(currentProgram);
		updateUniformBuffers(currentProgram, camera, viewport, light, obj->modelMatrix);

		//Pass the necessary textures
		GLuint depthLoc = glGetUniformLocation(currentProgram, "depthMap");
		GLuint gaussLoc = glGetUniformLocation(currentProgram, "gauss");
		GLuint textureLoc = glGetUniformLocation(currentProgram, "texture");

		glUniform1i(depthLoc, 0);
		glUniform1i(gaussLoc, 1);
		glUniform1i(textureLoc, 2);

		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, depthMap_);

		glActiveTexture(GL_TEXTURE1);
		glBindTexture(GL_TEXTURE_1D, gaussTex_);
		
		//Mesh texture necessary only in triangular meshes
		if (obj->getTexture())
		{
			glActiveTexture(GL_TEXTURE2);
			glBindTexture(GL_TEXTURE_2D, *obj->getTexture());
		}

		obj->render();
	}

	//------------------ SHADING PASS ------------------//

	//Draw to the default frame buffer
	glDrawBuffer(GL_NONE);
	glBindFramebuffer(GL_FRAMEBUFFER, 0);

	glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);
	glClearColor(0.2f, 0.2f, 0.4f, 1.0f);

	for (RenderableObject *obj : m_renderableObjs)
	{
		glUseProgram(shadingProgram_);

		updateUniformBuffers(shadingProgram_, camera, viewport, light, obj->modelMatrix);

		//Pass the necessary textures
		GLuint colorLoc = glGetUniformLocation(shadingProgram_, "colorTex");
		GLuint normalLoc = glGetUniformLocation(shadingProgram_, "normalTex");
		GLuint depthLoc = glGetUniformLocation(shadingProgram_, "depthMap");
		GLuint shadowLoc = glGetUniformLocation(shadingProgram_, "shadowMap");

		glUniform1i(colorLoc, 0);
		glUniform1i(normalLoc, 1);
		glUniform1i(depthLoc, 2);
		glUniform1i(shadowLoc, 3);

		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, colorTex_);

		glActiveTexture(GL_TEXTURE1);
		glBindTexture(GL_TEXTURE_2D, normalTex_);

		glActiveTexture(GL_TEXTURE2);
		glBindTexture(GL_TEXTURE_2D, depthMap_);

		glActiveTexture(GL_TEXTURE3);
		glBindTexture(GL_TEXTURE_2D, shadowMap_);

		obj->render();
	}

	glBindTexture(GL_TEXTURE_2D, 0);
	glUseProgram(GL_NONE);
}

void RenderManager::addRenderableObj(RenderableObject * renderableObj)
{
	m_renderableObjs.push_back(renderableObj);
}

void RenderManager::clear()
{
	m_renderableObjs.clear();
}

