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

	mesh.shaderProgram = glCreateProgram();

	ShaderLoader::get().addShader(mesh.shaderProgram, "../shaders/shader.vert", GL_VERTEX_SHADER);
	ShaderLoader::get().addShader(mesh.shaderProgram, "../shaders/shader.frag", GL_FRAGMENT_SHADER);

	MeshLoader::get().loadMesh("../meshes/helios.obj", "../textures/helios.png", 8192, 8192, mesh);

	RenderManager::get().addRenderableObj(&mesh);

	return true;
}

void PBREngine::initializeGL()
{
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_POINT_SPRITE);

	glPointSize(4);
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

	//Build and update uniform matrices
	glm::mat4 view, projection;

	view = glm::lookAt(camera.pos, camera.targetPos, camera.up);
	projection = glm::perspective(glm::radians(camera.fov), 600.0f / 400.0f, camera.nearZ, camera.farZ);

	//GLint model_loc = glGetUniformLocation(shader_programme, "model");
	GLint view_loc = glGetUniformLocation(mesh.shaderProgram, "view");
	GLint proj_loc = glGetUniformLocation(mesh.shaderProgram, "proj");

	//glUniformMatrix4fv(model_loc, 1, GL_FALSE, &model[0][0]);
	glUniformMatrix4fv(view_loc, 1, GL_FALSE, &view[0][0]);
	glUniformMatrix4fv(proj_loc, 1, GL_FALSE, &projection[0][0]);

	//Clear color and depth
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glClearColor(0.15f, 0.15f, 0.15f, 1.0f);

	RenderManager::get().render();

	//glUseProgram(shader_programme);
	//glBindVertexArray(mesh.vao);
	//// draw points 0-3 from the currently bound VAO with current in-use shader
	//glDrawArrays(GL_POINTS,0,mesh.pointsNum);
	// update other events like input handling 
	glfwPollEvents();

	glfwSwapBuffers(p_window);
}
