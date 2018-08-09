#include "PBREngine.h"

#include <glm.hpp>

int main()
{
	PBREngine engine;

	engine.startUp();
	engine.setLight(glm::vec3(0.1f, 4.0f, 5.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec4(0.08f, 0.08f, 0.08f, 1.0f), glm::vec4(0.8f, 0.8f, 0.8f, 1.0f), glm::vec4(0.75f, 0.6f, 0.57f, 1.0f), 256.0f);
	engine.setCamera(50.0f, 0.1f, 30.0f, glm::vec3(0.0f, 2.0f, 0.0f), glm::vec3(0.0f, 0.0f, -1.0f), glm::vec3(0.0f, 1.0f, 0.0f));
	engine.addRenderableGameObject(glm::vec3(-7.0f, 2.5f, -7.0f), Mesh::MESH_TYPE_POINT, "../meshes/hypnos.obj", "../textures/marble.png", 894, 894);
	engine.addRenderableGameObject(glm::vec3(0.0f, 0.0f, 0.0f), Mesh::MESH_TYPE_TRIANGULAR, "../meshes/plane.obj", "../textures/floor.png", 236, 236);
	engine.addRenderableGameObject(glm::vec3(-7.0f, -0.2f, -7.1f), Mesh::MESH_TYPE_TRIANGULAR, "../meshes/base.obj", "../textures/marble.png", 894, 894);
	engine.addRenderableGameObject(glm::vec3(0.0f, -0.2f, -7.1f), Mesh::MESH_TYPE_TRIANGULAR, "../meshes/base.obj", "../textures/marble.png", 894, 894);
	engine.addRenderableGameObject(glm::vec3(0.2f, 2.2f, -7.0f), Mesh::MESH_TYPE_POINT, "../meshes/grace.obj", "../textures/marble.png", 894, 894);
	engine.addRenderableGameObject(glm::vec3(7.0f, -0.2f, -7.1f), Mesh::MESH_TYPE_TRIANGULAR, "../meshes/base.obj", "../textures/marble.png", 894, 894);
	engine.addRenderableGameObject(glm::vec3(7.0f, 2.0f, -7.0f), Mesh::MESH_TYPE_POINT, "../meshes/helios.obj", "../textures/marble.png", 894, 894);
	engine.initializeScene();
	
	engine.run();
}