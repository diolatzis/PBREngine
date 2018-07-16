#include "PhysicsObject.h"

PhysicsObject::PhysicsObject()
{
	vel_ = glm::vec3(0, 0, 0);
	accel_ = glm::vec3(0, 0, 0);
}

PhysicsObject::~PhysicsObject()
{
}

void PhysicsObject::addForce(Force f)
{
	forces_.push_back(f);
}