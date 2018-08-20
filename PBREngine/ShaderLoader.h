#ifndef SHADER_LOADER_H
#define SHADER_LOADER_H

#define GLEW_STATIC

#include <GL\glew.h>
#include <string>
#include <vector>

#include "FileSystem.h"

class ShaderLoader
{
private:

	static ShaderLoader *instance;

	//Constructors/Destructors
	ShaderLoader();
	~ShaderLoader();

public:
	
	//Start up and shut down functions of the subsystem
	void startUp();
	void shutDown();

	//Get the singleton instance
	static ShaderLoader& get();

	//Load a shader from a given path
	GLuint loadShader(const char *shaderPath, GLenum shaderType);

	//Add a shader to an existing program
	void addShader(GLuint program, const char *shaderPath, GLenum shaderType);

	//Load a vertex and fragment shader and add them to a program
	void setShader(GLuint &program, const std::string &shaderPath);

};

#endif

