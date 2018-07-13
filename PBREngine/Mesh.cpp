#include "Mesh.h"



Mesh::Mesh()
{
}


Mesh::~Mesh()
{
}

void Mesh::render()
{

	//Build and update uniform matrices
	glm::mat4 model;

	model = glm::mat4(1.0f);
	model = glm::rotate(model, glm::radians((float)frame), glm::vec3(0.0f, 0.0f, 1.0f));

	GLint model_loc = glGetUniformLocation(shaderProgram, "model");

	glUniformMatrix4fv(model_loc, 1, GL_FALSE, &model[0][0]);

	glUseProgram(shaderProgram);
	glBindVertexArray(vao);
	// draw points 0-3 from the currently bound VAO with current in-use shader
	glDrawArrays(GL_POINTS,0,pointsNum);

	++frame;

}
