#include "PhysicsManager.h"



PhysicsManager::PhysicsManager()
{
	//Do nothing
}

PhysicsManager::~PhysicsManager()
{
	//Do nothing
}

void PhysicsManager::startUp()
{
	//Any necessary initialization goes here
}

PhysicsManager & PhysicsManager::get()
{
	static PhysicsManager* instance = NULL;
	if (instance == NULL)
	{
		instance = new PhysicsManager();
	}
	_ASSERT(instance);
	return *instance;
}

void PhysicsManager::addGlobalForce(Force f)
{
	globalForces_.push_back(f);
}

void PhysicsManager::addPhysicsObj(PhysicsObject * physicsObj)
{
	physicsObjs_.push_back(physicsObj);
}

void PhysicsManager::simulate(const float timestep)
{
	for (int i = 0; i < physicsObjs_.size(); i++)
	{
		physicsObjs_.at(i)->simulate(globalForces_, timestep);	//Timestep the objects
	}
}

void PhysicsManager::handleCollisions(const float timestep)
{
	m_timestep = timestep;

	for (int i = 0; i < physicsObjs_.size(); i++)
	{
		PhysicsObject * obj1 = physicsObjs_.at(i);

		for (int j = i+1; j < physicsObjs_.size(); j++)	//For each object check collisions with every other
		{
			PhysicsObject * obj2 = physicsObjs_.at(j);

			if (obj1->getShape() == PhysicsObject::SHAPE_POINT)		//Object 1 -> sphere
			{
				if (obj2->getShape() == PhysicsObject::SHAPE_FLOOR)		//Object 2 -> floor
				{
					checkHandleCollisionPointFloor(obj1, obj2);
				}
				if (obj2->getShape() == PhysicsObject::SHAPE_SPHERE)	//Object 2 -> sphere
				{
					checkHandleCollisionPointSphere(obj1, obj2);
				}
			}
			else if (obj1->getShape() == PhysicsObject::SHAPE_FLOOR)	//Object 1 -> floor
			{
				if (obj2->getShape() == PhysicsObject::SHAPE_POINT)	//Object 2 -> sphere
				{
					checkHandleCollisionPointFloor(obj2, obj1);
				}
			}
			else if (obj1->getShape() == PhysicsObject::SHAPE_SPHERE)
			{
				if (obj2->getShape() == PhysicsObject::SHAPE_POINT)	//Object 2 -> sphere
				{
					checkHandleCollisionPointSphere(obj2, obj1);
				}
			}
		}
	}
}

void PhysicsManager::clear()
{
	physicsObjs_.clear();
}

void PhysicsManager::reset()
{
	for (int i = 0; i < physicsObjs_.size(); i++)
	{
		physicsObjs_.at(i)->reset();
	}
}

void PhysicsManager::updatePos(const float timestep)
{
	for (int i = 0; i < physicsObjs_.size(); i++)
	{
		physicsObjs_.at(i)->updatePos(timestep);
	}
}

void PhysicsManager::clearForces()
{
	for (int i = 0; i < physicsObjs_.size(); i++)
	{
		physicsObjs_.at(i)->forces_.clear();
	}
}

void PhysicsManager::checkHandleCollisionPointSphere(PhysicsObject * point, PhysicsObject * sphere)
{
	//Make sure objects are of the correct shape
	_ASSERT(point->getShape() == PhysicsObject::SHAPE_POINT);
	_ASSERT(sphere->getShape() == PhysicsObject::SHAPE_SPHERE);


	glm::vec3 * pointPos = point->getShapeVertices();
	glm::vec3 * spherePos = sphere->getShapeVertices();
	float radius = sphere->getShapeParameter();
	glm::vec3 collisionNormal = glm::normalize(pointPos[0] - spherePos[0]);

	if (glm::length(spherePos[0] - (pointPos[0] + *point->getVel()*m_timestep)) <= radius+0.03f)
	{
		point->getVel()[0] = point->getRestitution() * (point->getVel()[0] + collisionNormal * ((glm::dot(*point->getVel(), collisionNormal))*(-2)));	//Invert the sphere's velocity
		
		glm::vec3 rotNorm = glm::cross(*sphere->getRotVel(), collisionNormal);

		if (glm::length(rotNorm) == 0) return;
		
		rotNorm = glm::normalize(rotNorm);

		point->getVel()[0] = point->getRestitution() * (point->getVel()[0] + rotNorm * glm::length(*sphere->getRotVel()));

	}

}

void PhysicsManager::checkHandleCollisionPointFloor(PhysicsObject * point, PhysicsObject * floor)
{
	//Make sure objects are of the correct shape
	_ASSERT(point->getShape() == PhysicsObject::SHAPE_POINT);
	_ASSERT(floor->getShape() == PhysicsObject::SHAPE_FLOOR);

	glm::vec3 * pointPos = point->getShapeVertices();
	glm::vec3 * planeVec = floor->getShapeVertices();

	glm::vec3 planeNormal = glm::normalize(glm::cross((planeVec[1] - planeVec[0]), (planeVec[2] - planeVec[0])));


	if (glm::dot((planeVec[0] - (pointPos[0] + *point->getVel()*m_timestep)), planeNormal) > 0)
	{


		point->getVel()[0] = point->getRestitution() * (point->getVel()[0] + planeNormal * ((glm::dot(*point->getVel(), planeNormal))*(-2)));	//Invert the sphere's velocity
	}
}