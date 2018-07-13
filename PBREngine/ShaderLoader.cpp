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
