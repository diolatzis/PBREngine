#ifndef PHYSICS_OBJECT_H
#define PHYSICS_OBJECT_H

#include <vector>
#include <glm.hpp>
#include "Types.h"

class PhysicsObject		//Abstract class of physics objects
{
protected:

	//Physics variables
	glm::vec3 vel_, accel_;
	glm::vec3 rotVel_;
	glm::vec3 iniVel_;

	float mass_;
	float restitution_;

	//Shape of the collision pollygon
	int shape_;

	//Forces switches
	bool enableWind_ = false;
	bool enableGravity_ = true;

public:

	//Forces applied to this object
	std::vector<Force> forces_;

	//If the object is immovable
	bool isFixed_ = false;

	//Shapes supproted
	static const int SHAPE_SPHERE = 0;
	static const int SHAPE_FLOOR = 1;
	static const int SHAPE_POINT = 2;

	PhysicsObject();
	~PhysicsObject();

	//Virtual functions
	virtual void simulate(const std::vector<Force> & globalForces, const float timestep) = 0;
	virtual void reset() = 0;
	virtual glm::vec3 * getShapeVertices() = 0;
	virtual float getShapeParameter()=0; 
	virtual void updatePos(const float timestep) = 0;

	//Add a force to this object
	void addForce(Force f);
	void setWind(bool enableWind) { enableWind_ = enableWind; }
	void setGravity(bool enableGravity) { enableGravity_ = enableGravity; }

	//Getters
	int getShape() { return shape_; }
	float getRestitution() { return restitution_; }
	glm::vec3 * getVel() { return &vel_; }
	float getMass() { return mass_; }
	glm::vec3 * getRotVel() { return &rotVel_; }
};

#endif

