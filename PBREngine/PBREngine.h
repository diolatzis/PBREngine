#ifndef PBR_ENGINE_H
#define PBR_ENGINE_H

#define GLEW_STATIC
#define GLM_ENABLE_EXPERIMENTAL

#include <GL\glew.h>
#include <GLFW\glfw3.h>
#include <glm.hpp>
#include <gtx\vector_angle.hpp>
#include <gtc\matrix_transform.hpp>
#include <gtc\constants.hpp>
#include <string>
#include <iostream>
#include <ctime>
#include <thread>

#include "ShaderLoader.h"
#include "MeshLoader.h"
#include "RenderManager.h"
#include "PointMesh.h"
#include "Camera.h"
#include "Light.h"
#include "GameObject.h"

class PBREngine
{
public:

	//Window parameters
	const unsigned int WINDOW_WIDTH = 1500;
	const unsigned int WINDOW_HEIGHT = 1000;
	const std::string WINDOW_NAME = "PBREngine";
	GLFWwindow *window_;

	//FPS handling
	float fps_ = 0;
	float frames_ = 0;
	int fpsTarget_ = 1000;
	double skipTicks_ = 1.0f / fpsTarget_;
	double nextGameTick_ = glfwGetTime();
	double startTime_ = glfwGetTime();
	
	//Array with game objects
	std::vector<GameObject> gameObjects_;

	//Mouse last position values used in fps camera movement
	double lastX_ = WINDOW_WIDTH/2.0, lastY_ = WINDOW_HEIGHT/2.0;

	//Scene light and camera
	Light light_;
	Camera camera_;

	//Constructors/Destructors
	PBREngine();
	~PBREngine();

	//Start up and shut down functions of the subsystem
	void startUp();
	void shutDown();

	//Initialize engine and libraries
	bool initialize();
	//Initialize openGL parameters
	void initializeGL();
	//Function to add renderable game object
	void addRenderableGameObject(glm::vec3 pos,int meshType, const char * meshPath, const char * texturePath, int textureWidth, int textureHeight);
	//Functions to set light and camera
	void setLight(glm::vec3 pos, glm::vec3 targetPos, glm::vec4 ambient, glm::vec4 diffuse, glm::vec4 specular, float specularPower);
	void setCamera(float fov, float nearZ, float farZ, glm::vec3 pos, glm::vec3 targetPos, glm::vec3 up);
	//Function to add game objects as renderable
	void initializeScene();

	//Functions that handle glfw callbacks
	static void handleError(int error, const char *description);
	static void resize(GLFWwindow *window, int width, int height);
	static void handleKeyPress(GLFWwindow* window, int key, int scancode, int action, int mods);
	static void handleMouseMovement(GLFWwindow* window, double xpos, double ypos);

	//Main run function
	int run();
	//Main function that is called in every loop
	int mainLoop();

	//Keyboard input handling
	void handleInput(int key, int action);
	//Mouse input handling
	void handleMouseInput(double x, double y);
	
	//Update game objects function
	void update();
	//Render game objects function
	void render();
};

#endif