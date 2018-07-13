#ifndef CAMERA
#define CAMERA

#include <glm.hpp>
#include <gtc\constants.hpp>

class Camera
{
public:

	//Camera variables
	float fov = 40.0, nearZ = 0.1, farZ = 1000, theta = 0, phi = 135, radius = 25;
	glm::vec3 pos = { radius*cosf(phi*glm::pi<float>() / 180.0f)*sinf(theta*glm::pi<float>() / 180.0f) ,radius*sinf(phi*glm::pi<float>() / 180.0f) ,radius*cosf(phi*glm::pi<float>() / 180.0f)*cosf(theta*glm::pi<float>() / 180.0f) };	//Using spherical coords
	glm::vec3 targetPos = { 0, 5, 2 };
	glm::vec3 up = { 0,1,0 };

	Camera();
	~Camera();
};

#endif