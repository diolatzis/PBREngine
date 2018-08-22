#include "ShaderLoader.h"

ShaderLoader* ShaderLoader::instance = NULL;


ShaderLoader::ShaderLoader()
{
	//Do nothing
}


ShaderLoader::~ShaderLoader()
{
	//Do nothing
}

void ShaderLoader::startUp()
{
	//Initialization of necessary systems goes here
}

void ShaderLoader::shutDown()
{
	//Termination of necessary systems goes here
	delete instance;
}

ShaderLoader &ShaderLoader::get()
{
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

void ShaderLoader::setShader(GLuint & program, const std::string & shaderPath)
{
	program = glCreateProgram();

	ShaderLoader::get().addShader(program, (shaderPath + ".vert").c_str(), GL_VERTEX_SHADER);
	ShaderLoader::get().addShader(program, (shaderPath + ".frag").c_str(), GL_FRAGMENT_SHADER);
}
