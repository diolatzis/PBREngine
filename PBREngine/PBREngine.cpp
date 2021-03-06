// PBREngine.cpp : Defines the entry point for the console application.
//

int renderType_;

#include "stdafx.h"
#include "PBREngine.h"

PBREngine::PBREngine()
{
	//Do nothing
}


PBREngine::~PBREngine()
{
	//Do nothing
}

void PBREngine::startUp()
{
	//Initialization of necessary systems goes here
	initialize();
	MeshLoader::get().startUp();
	RenderManager::get().startUp(WINDOW_WIDTH, WINDOW_HEIGHT);	
}

void PBREngine::shutDown()
{
	//Termination of necessary systems goes here
	glfwTerminate();
	RenderManager::get().shutDown();
	MeshLoader::get().shutDown();
}

bool PBREngine::initialize()
{
	//Initialize glfw
	if (!glfwInit())
	{
		return false;
	}

	//Initiaize window
	glfwWindowHint(GLFW_RESIZABLE, GLFW_TRUE);
	window_ = glfwCreateWindow(WINDOW_WIDTH, WINDOW_HEIGHT, WINDOW_NAME.c_str(), NULL, NULL);
	
	if (!window_)
	{
		return false;
	}

	glfwMakeContextCurrent(window_);

	//Set callbacks
	glfwSetErrorCallback(&handleError);
	glfwSetWindowSizeCallback(window_, &resize);
	glfwSetKeyCallback(window_, &handleKeyPress);
	glfwSetCursorPosCallback(window_, &handleMouseMovement);
	
	//Initialize glew
	glewExperimental = GL_TRUE;

	glfwSetWindowUserPointer(window_, this);

	if (glewInit() != GLEW_OK)
	{
		return false;
	}

	//Initialize openGL
	initializeGL();

	//Render type is circular by default
	renderType_ = RenderManager::RENDER_TYPE_CIRCLE_SPLAT;

	return true;
}

void PBREngine::initializeGL()
{
	//Set openGL to expect the point size from the shaders
	glEnable(GL_PROGRAM_POINT_SIZE);
}

void PBREngine::addRenderableGameObject(glm::vec3 pos, int meshType, const char * meshPath, const char * texturePath, int textureWidth, int textureHeight)
{
	GameObject gameObject(pos);

	//Set the mesh data 
	switch (meshType)
	{
	case Mesh::MESH_TYPE_POINT:
		gameObject.setPointMesh(meshPath, texturePath, textureWidth, textureHeight);		
		break;
	case Mesh::MESH_TYPE_TRIANGULAR:
		gameObject.setTriangMesh(meshPath, texturePath, textureWidth, textureHeight);
		break;
	}

	//Add the game object
	gameObjects_.push_back(gameObject);
}

void PBREngine::setLight(glm::vec3 pos, glm::vec3 targetPos, glm::vec4 ambient, glm::vec4 diffuse, glm::vec4 specular, float specularPower)
{
	light_ = Light(pos, targetPos, ambient, diffuse, specular, specularPower);
}

void PBREngine::setCamera(float fov, float nearZ, float farZ, glm::vec3 pos, glm::vec3 targetPos, glm::vec3 up)
{
	camera_ = Camera(fov, nearZ, farZ, pos, targetPos, up);
}

void PBREngine::initializeScene()
{
	//Set the game objects as renderable
	for (int i = 0; i < gameObjects_.size(); i++)
	{
		RenderManager::get().addRenderableObj(&gameObjects_[i]);
	}
}

void PBREngine::handleError(int error, const char * description)
{
	std::cout << description << std::endl;
}

void PBREngine::resize(GLFWwindow * window, int width, int height)
{
	float ratio = width / (float)height;
	glViewport(0, 0, width, height);
}

void PBREngine::handleKeyPress(GLFWwindow * window, int key, int scancode, int action, int mods)
{	
	//Pass the keyboard input event to the function to be handled
	PBREngine *instance = reinterpret_cast<PBREngine*>(glfwGetWindowUserPointer(window));
	instance->handleInput(key, action);
}

void PBREngine::handleMouseMovement(GLFWwindow * window, double xpos, double ypos)
{
	//Pass the mouse input event to the function to be handled
	PBREngine *instance = reinterpret_cast<PBREngine*>(glfwGetWindowUserPointer(window));
	instance->handleMouseInput(xpos, ypos);
}

int PBREngine::run()
{
	//Initialize time variables
	nextGameTick_ = glfwGetTime();
	startTime_ = glfwGetTime();

	//Run the main loop
	while (!glfwWindowShouldClose(window_))
	{
		mainLoop();
	}

	return 0;
}

int PBREngine::mainLoop()
{
	//Main functions
	update();	
	render();	
	glfwPollEvents();

	//Update time variables
	nextGameTick_ += skipTicks_;
	double sleepTime = nextGameTick_ - glfwGetTime();

	//One second has passed update the fps
	if (glfwGetTime() - startTime_ >= 1.0f)
	{
		fps_ = frames_;
		frames_ = 0;
		startTime_ = glfwGetTime();
		std::cout << fps_ << std::endl;
	}

	//We are drawing more frames than target
	if (sleepTime > 0)
	{
		std::this_thread::sleep_for(std::chrono::milliseconds((int)(sleepTime*1000)));
		glfwPollEvents();
	}

	return 0;
}

void PBREngine::handleInput(int key, int action)
{
	//Implementation of wasd keyboard movement
	if (key == GLFW_KEY_W && (action == GLFW_PRESS || action == GLFW_REPEAT))
	{
		camera_.pos_ += (camera_.targetPos_*0.15f);
		
	}

	if (key == GLFW_KEY_A && (action == GLFW_PRESS || action == GLFW_REPEAT))
	{
		//Strafing is implemented by calculating the perpendicular movement to the current
		//direction that the camera is facing and the y axis
		glm::vec3 dir = glm::cross(camera_.targetPos_, glm::vec3(0.0f, 1.0f, 0.0f));
		camera_.pos_ -= (dir*0.1f);

	}

	if (key == GLFW_KEY_S && (action == GLFW_PRESS || action == GLFW_REPEAT))
	{
		camera_.pos_ -= (camera_.targetPos_*0.15f);

	}

	if (key == GLFW_KEY_D && (action == GLFW_PRESS || action == GLFW_REPEAT))
	{
		glm::vec3 dir = glm::cross(camera_.targetPos_, glm::vec3(0.0f, 1.0f, 0.0f));
		camera_.pos_ += (dir*0.1f);
	}

	//Option to change in real time to square or circular splatting
	if (key == GLFW_KEY_1 && action == GLFW_PRESS)
	{
		renderType_ = RenderManager::RENDER_TYPE_SQUARE_SPLAT;
	}

	if (key == GLFW_KEY_2 && action == GLFW_PRESS)
	{
		renderType_ = RenderManager::RENDER_TYPE_CIRCLE_SPLAT;
	}

}

void PBREngine::handleMouseInput(double x, double y)
{
	//Implementation of first person camera movement

	float deltaX = x - lastX_;
	float deltaY = y - lastY_;

	lastX_ = x;
	lastY_ = y;

	camera_.targetPos_ = glm::rotateY(camera_.targetPos_, -glm::radians(deltaX/3.0f));
}

void PBREngine::update()
{
	//Update the game object if necessary in a more complex game
}

void PBREngine::render()
{
	//Render the frame

	++frames_;

	GLint viewport[4];

	glGetIntegerv(GL_VIEWPORT, viewport);

	RenderManager::get().render(camera_, viewport, light_, renderType_);

	glfwPollEvents();
	glfwSwapBuffers(window_);
}
