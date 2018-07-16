#ifndef PHYSICS_MANAGER_H
#define PHYSICS_MANAGER_H

#include <iostream>
#include <vector>
#include "Types.h"
#include "PhysicsObject.h"

class PhysicsManager
{

	std::vector<Force> globalForces_;			//Global forces vector
	std::vector<PhysicsObject*> physicsObjs_;	//Physics objects vector

	float m_timestep;	//Simulation timestep

public:

	PhysicsManager();
	~PhysicsManager();

	//Initialization of manager
	void startUp();		

	//Get the singleton instance
	static PhysicsManager& get();

	//Add a global force to all objects
	void addGlobalForce(Force f);

	//Add a physicsObject
	void addPhysicsObj(PhysicsObject * physicsObj);

	//Simulate the objects
	void simulate(const float timestep);

	//Check and handle the collisions
	void handleCollisions(float timestep);

	//Remove all objects
	void clear();	

	//Reset objects to initial positions
	void reset();

	//Update position
	void updatePos(const float timestep);

	//Clear vector forces
	void clearForces();

protected:

	//Internal function that checks and resolves collisions between sphere floor
	void checkHandleCollisionPointFloor(PhysicsObject * point, PhysicsObject * floor);
	void checkHandleCollisionPointSphere(PhysicsObject * point, PhysicsObject * sphere);


};

#endif