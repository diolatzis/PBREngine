#ifndef SHADER_LOADER_H
#define SHADER_LOADER_H

#define GLEW_STATIC

#include <GL\glew.h>
#include <string>
#include <vector>

#include "FileSystem.h"

class ShaderLoader
{
public:

	static const int RENDER_TYPE_CIRCLE_SPLAT = 0, RENDER_TYPE_SQUARE_SPLAT = 1;

	ShaderLoader();
	~ShaderLoader();


	void startUp();
	void shutDown();

	//Get the singleton instance
	static ShaderLoader& get();

	GLuint loadShader(const char *shaderPath, GLenum shaderType);

	void addShader(GLuint program, const char *shaderPath, GLenum shaderType);

	void setShaders(GLuint program, const int renderType);

};

#endif

