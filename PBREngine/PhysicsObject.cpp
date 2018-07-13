#include "PhysicsObject.h"

PhysicsObject::PhysicsObject()
{
	m_vel = glm::vec3(0, 0, 0);
	m_accel = glm::vec3(0, 0, 0);
}

PhysicsObject::~PhysicsObject()
{
}

void PhysicsObject::addForce(Force f)
{
	m_forces.push_back(f);
}