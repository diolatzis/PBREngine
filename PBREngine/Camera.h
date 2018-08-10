#ifndef CAMERA
#define CAMERA

#include <glm.hpp>
#include <gtc\constants.hpp>

class Camera 
{
public:

	//Camera variables
	float fov_, nearZ_, farZ_;
	glm::vec3 pos_, targetPos_, up_;

	//Constructors/Destructors
	Camera();
	Camera(float fov, float nearZ, float farZ, glm::vec3 pos, glm::vec3 targetPos, glm::vec3 up);
	~Camera();

	//Function that returns the vector the camera is looking towards
	glm::vec3 getTarget();
};

#endif