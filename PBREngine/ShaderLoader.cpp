#include "ShaderLoader.h"



ShaderLoader::ShaderLoader()
{
}


ShaderLoader::~ShaderLoader()
{
}

void ShaderLoader::startUp()
{
}

void ShaderLoader::shutDown()
{
}

ShaderLoader &ShaderLoader::get()
{
	static ShaderLoader *instance = NULL;
	if (instance == NULL)
	{
		instance = new ShaderLoader();
	}
	_ASSERT(instance);
	return *instance;
}

GLuint ShaderLoader::loadShader(const char * shaderPath, GLenum shaderType)
{
	GLuint shader = glCreateShader(shaderType);

	GLint success;
	GLchar log[512];

	std::string shaderStr = FileSystem::get().syncStrReadFile(shaderPath);

	const GLchar *shaderData = shaderStr.c_str();

	glShaderSource(shader, 1, &shaderData, NULL);
	glCompileShader(shader);

	// Check status of shader compilation
	glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		// Write out errors
		glGetShaderInfoLog(shader, 512, nullptr, log);
		std::cout << "Failed to compile shader" << std::endl << log << std::endl;
	}


	return shader;
}

void ShaderLoader::addShader(GLuint program, const char * shaderPath, GLenum shaderType)
{
	GLuint shader = loadShader(shaderPath, shaderType);
	glAttachShader(program, shader);
	glLinkProgram(program);
	glDeleteShader(shader);
}

void ShaderLoader::setShaders(GLuint program, const int renderType)
{
	switch (renderType)
	{
	case RENDER_TYPE_SQUARE_SPLAT:
		ShaderLoader::get().addShader(program, "../shaders/square_splatting.vert", GL_VERTEX_SHADER);
		ShaderLoader::get().addShader(program, "../shaders/square_splatting.frag", GL_FRAGMENT_SHADER);
		break;
	case RENDER_TYPE_CIRCLE_SPLAT:
		ShaderLoader::get().addShader(program, "../shaders/circle_splatting.vert", GL_VERTEX_SHADER);
		ShaderLoader::get().addShader(program, "../shaders/circle_splatting.frag", GL_FRAGMENT_SHADER);
		break;

	}
}
