// PBREngine.cpp : Defines the entry point for the console application.
//

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
	MeshLoader::get().startUp();
	RenderManager::get().startUp();
	initialize();
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
	p_window = glfwCreateWindow(WINDOW_WIDTH, WINDOW_HEIGHT, WINDOW_NAME.c_str(), NULL, NULL);
	
	if (!p_window)
	{
		return false;
	}

	glfwMakeContextCurrent(p_window);

	//Set callbacks
	glfwSetErrorCallback(&handleError);
	glfwSetWindowSizeCallback(p_window, &resize);
	
	//Initialize glew
	glewExperimental = GL_TRUE;

	if (glewInit() != GLEW_OK)
	{
		return false;
	}

	initializeGL();

	mesh.shaderProgram_ = glCreateProgram();

	ShaderLoader::get().addShader(mesh.shaderProgram_, "../shaders/shader.vert", GL_VERTEX_SHADER);
	ShaderLoader::get().addShader(mesh.shaderProgram_, "../shaders/shader.frag", GL_FRAGMENT_SHADER);

	MeshLoader::get().loadMesh("../meshes/hypnos.obj", "../textures/hypnos.png", 8192, 8192, mesh);

	RenderManager::get().addRenderableObj(&mesh);

	return true;
}

void PBREngine::initializeGL()
{
	glEnable(GL_DEPTH_TEST);
	//glEnable(GL_POINT_SPRITE);

	glPointSize(13);
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

int PBREngine::run()
{
	//Initialize time variables
	nextGameTick = glfwGetTime();
	startTime = glfwGetTime();

	while (!glfwWindowShouldClose(p_window))
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

	nextGameTick += skipTicks;
	double sleepTime = nextGameTick - glfwGetTime();

	//One second has passed update the fps
	if (glfwGetTime() - startTime >= 1.0f)
	{
		fps = frames;
		frames = 0;
		startTime = glfwGetTime();
		std::cout << fps << std::endl;
	}

	//We are drawing more frames than target
	if (sleepTime > 0)
	{
		std::this_thread::sleep_for(std::chrono::milliseconds((int)(sleepTime*1000)));
		glfwPollEvents();
	}

	return 0;
}

void PBREngine::update()
{
}

void PBREngine::render()
{
	++frames;

	GLint viewport[4];

	glGetIntegerv(GL_VIEWPORT, viewport);

	//Clear color and depth
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glClearColor(0.15f, 0.15f, 0.15f, 1.0f);

	RenderManager::get().render(camera, viewport);

	glfwPollEvents();

	glfwSwapBuffers(p_window);
}
