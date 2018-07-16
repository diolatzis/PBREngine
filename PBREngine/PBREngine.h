#ifndef PBR_ENGINE_H
#define PBR_ENGINE_H

#define GLEW_STATIC

#include <GL\glew.h>
#include <GLFW\glfw3.h>
#include <glm.hpp>
#include <gtc\matrix_transform.hpp>
#include <gtc\constants.hpp>
#include <string>
#include <iostream>
#include <ctime>
#include <thread>

#include "ShaderLoader.h"
#include "MeshLoader.h"
#include "RenderManager.h"
#include "Mesh.h"
#include "Camera.h"

class PBREngine
{
public:

	const unsigned int WINDOW_WIDTH = 1200;
	const unsigned int WINDOW_HEIGHT = 800;
	const std::string WINDOW_NAME = "PBREngine";

	GLFWwindow *p_window;

	//FPS handling
	float fps = 0;
	float frames = 0;
	int fpsTarget = 1000;
	double skipTicks = 1.0f / fpsTarget;
	double nextGameTick = glfwGetTime();
	double startTime = glfwGetTime();
	
	// Lighting information
	GLfloat ambient[4] = { 0.2f, 0.2f, 0.2f, 1.0f };
	GLfloat lightPos[4] = { 0.0f, 10.0f, 5.0f, 0.0f };

	Camera camera;

	PBREngine();
	~PBREngine();

	void startUp();
	void shutDown();

	bool initialize();
	void initializeGL();

	static void handleError(int error, const char *description);
	static void resize(GLFWwindow *window, int width, int height);

	int run();
	int mainLoop();
	void update();
	void render();

	Mesh mesh;
};

#endif