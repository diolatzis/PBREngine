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
	initialize();
	MeshLoader::get().startUp();
	RenderManager::get().startUp(WINDOW_WIDTH, WINDOW_HEIGHT);
	
}

void PBREngine::shutDown()
{
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
	
	//Initialize glew
	glewExperimental = GL_TRUE;

	glfwSetWindowUserPointer(window_, this);

	if (glewInit() != GLEW_OK)
	{
		return false;
	}

	//Initialize openGL
	initializeGL();

	//Initialize the game scene
	initializeScene();

	return true;
}

void PBREngine::initializeGL()
{
	//Set openGL to expect the point size from the shaders
	glEnable(GL_PROGRAM_POINT_SIZE);
}

void PBREngine::initializeScene()
{
	light_ = Light(glm::vec3(2.0f, 0.0f, 8.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec4(0.05f, 0.05f, 0.05f, 1.0f), glm::vec4(0.8f, 0.8f, 0.8f, 1.0f), glm::vec4(0.75f, 0.75f, 0.57f, 1.0f), 256.0f);

	camera_ = Camera(40.0f, 0.1f, 200.0f, glm::vec3(0.0f, 0.0f, 8.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f));

	GameObject hypnos, helios, t;
	
	hypnos.setTriangMesh("../meshes/pony.obj", "../textures/checkerboard.png", 1920, 1920);
	hypnos.modelMatrix = glm::translate(helios.modelMatrix, glm::vec3(-1, 0, 0));
	t.setTriangMesh("../meshes/hypnos2.obj", "../textures/hypnos.png", 8192, 8192);
	t.modelMatrix = glm::translate(helios.modelMatrix, glm::vec3(-2, 0, 0));
	//hypnos.setPointMesh("../meshes/model.obj", "../textures/marble2.png", 2972, 2000);
	helios.modelMatrix = glm::translate(helios.modelMatrix, glm::vec3(1, 0, 0));
	helios.setTriangMesh("../meshes/hypnos2.obj", "../textures/hypnos.png", 8192, 8192);

	gameObjects_.push_back(hypnos);

	RenderManager::get().addRenderableObj(&gameObjects_[0]);

	//RenderManager::get().addRenderableObj(&gameObjects_[1]);

	//RenderManager::get().addRenderableObj(&gameObjects_[2]);

	renderType_ = RenderManager::RENDER_TYPE_CIRCLE_SPLAT;
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
	PBREngine *instance = reinterpret_cast<PBREngine*>(glfwGetWindowUserPointer(window));
	instance->handleInput(key, action);
}

int PBREngine::run()
{
	//Initialize time variables
	nextGameTick_ = glfwGetTime();
	startTime_ = glfwGetTime();

	while (!glfwWindowShouldClose(window_))
	{
		mainLoop();
	}

	return 0;
}

int PBREngine::mainLoop()
{
	update();	
	render();	
	glfwPollEvents();

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
	if (key == GLFW_KEY_W && (action == GLFW_PRESS || action == GLFW_REPEAT))
	{
		camera_.pos_ += glm::vec3(0.0f, 0.0f, -0.2f);
		
	}

	if (key == GLFW_KEY_A && (action == GLFW_PRESS || action == GLFW_REPEAT))
	{
		camera_.pos_ += glm::vec3(-0.2f, 0.0f, 0.0f);

	}

	if (key == GLFW_KEY_S && (action == GLFW_PRESS || action == GLFW_REPEAT))
	{
		camera_.pos_ += glm::vec3(0.0f, 0.0f, 0.2f);

	}

	if (key == GLFW_KEY_D && (action == GLFW_PRESS || action == GLFW_REPEAT))
	{
		camera_.pos_ += glm::vec3(0.2f, 0.0f, 0.0f);

	}

	if (key == GLFW_KEY_1 && action == GLFW_PRESS)
	{
		renderType_ = RenderManager::RENDER_TYPE_SQUARE_SPLAT;
	}

	if (key == GLFW_KEY_2 && action == GLFW_PRESS)
	{
		renderType_ = RenderManager::RENDER_TYPE_CIRCLE_SPLAT;
	}

}

void PBREngine::update()
{
}

void PBREngine::render()
{
	++frames_;

	GLint viewport[4];

	glGetIntegerv(GL_VIEWPORT, viewport);

	RenderManager::get().render(camera_, viewport, light_, renderType_);

	glfwPollEvents();
	glfwSwapBuffers(window_);
}
