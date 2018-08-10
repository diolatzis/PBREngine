#include "Light.h"

Light::Light()
{
}

Light::Light(glm::vec3 pos, glm::vec3 targetPos, glm::vec4 ambient, glm::vec4 diffuse, glm::vec4 specular, float specularPower) : pos_(pos), targetPos_(targetPos), ambient_(ambient), 
diffuse_(diffuse), specular_(specular), specularPower_(specularPower)
{
}

Light::~Light()
{
}
