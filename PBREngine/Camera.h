#ifndef CAMERA
#define CAMERA

#include <glm.hpp>
#include <gtc\constants.hpp>

class Camera
{
public:

	//Camera variables
	float fov_ = 40.0, nearZ_ = 0.1, farZ_ = 1000, theta_ = 0, phi_ = 135, radius_ = 25;
	glm::vec3 pos_ = { radius_*cosf(phi_*glm::pi<float>() / 180.0f)*sinf(theta_*glm::pi<float>() / 180.0f) ,radius_*sinf(phi_*glm::pi<float>() / 180.0f) ,radius_*cosf(phi_*glm::pi<float>() / 180.0f)*cosf(theta_*glm::pi<float>() / 180.0f) };	//Using spherical coords
	glm::vec3 targetPos_ = { 0, 5, 2 };
	glm::vec3 up_ = { 0,1,0 };

	Camera();
	~Camera();
};

#endif