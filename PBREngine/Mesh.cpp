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
	glm::mat4 model_;

	model_ = glm::mat4(1.0f);
	model_ = glm::rotate(model_, glm::radians((float)frame), glm::vec3(0.0f, 0.0f, 1.0f));

	GLint model_loc = glGetUniformLocation(shaderProgram_, "model");

	glUniformMatrix4fv(model_loc, 1, GL_FALSE, &model_[0][0]);

	glUseProgram(shaderProgram_);
	glBindVertexArray(vao_);

	glDrawArrays(GL_POINTS,0,points_);

	++frame;

}

void Mesh::updateUniformBuffers(Camera camera, GLint viewport[4])
{
	//Build and update uniform matrices
	glm::mat4 view, projection, model_;

	view = glm::lookAt(camera.pos_, camera.targetPos_, camera.up_);
	projection = glm::perspective(glm::radians(camera.fov_), (float)viewport[2]/ (float)viewport[3], camera.nearZ_, camera.farZ_);

	//GLint model_loc = glGetUniformLocation(shader_programme, "model_");
	GLint view_loc = glGetUniformLocation(shaderProgram_, "view");
	GLint proj_loc = glGetUniformLocation(shaderProgram_, "proj");

	GLint viewport_loc = glGetUniformLocation(shaderProgram_, "viewport");
	GLint invProj_loc = glGetUniformLocation(shaderProgram_, "invProj");

	glUniform4f(viewport_loc, (float)viewport[0], (float)viewport[1], (float)viewport[2], (float)viewport[3]);
	glm::mat4 invProj = glm::inverse(projection);
	glUniformMatrix4fv(invProj_loc, 1, GL_FALSE, &invProj[0][0]);

	//glUniformMatrix4fv(model_loc, 1, GL_FALSE, &model_[0][0]);
	glUniformMatrix4fv(view_loc, 1, GL_FALSE, &view[0][0]);
	glUniformMatrix4fv(proj_loc, 1, GL_FALSE, &projection[0][0]);
}
