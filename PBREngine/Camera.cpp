#include "Camera.h"

Camera::Camera()
{
}

Camera::Camera(float fov, float nearZ, float farZ, glm::vec3 pos, glm::vec3 targetPos, glm::vec3 up) : fov_(fov), nearZ_(nearZ), farZ_(farZ), pos_(pos), targetPos_(targetPos), up_(up)
{
}

Camera::~Camera()
{
}

glm::vec3 Camera::getTarget()
{
	return pos_ + targetPos_;
}
