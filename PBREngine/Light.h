#ifndef LIGHT_H
#define LIGHT_H

#include <glm.hpp>

class Light
{
public:
	Light();
	Light(glm::vec3 pos, glm::vec3 targetPos, glm::vec4 ambient, glm::vec4 diffuse, glm::vec4 specular, float specularPower);
	~Light();

	glm::vec3 pos_, targetPos_;
	glm::vec4 ambient_, diffuse_, specular_;
	float specularPower_;

};


#endif

