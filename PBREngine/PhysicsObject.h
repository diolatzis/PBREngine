#ifndef PHYSICS_OBJECT_H
#define PHYSICS_OBJECT_H

#include <vector>
#include <glm.hpp>

class PhysicsObject		//Abstract class of physics objects
{
protected:

	typedef glm::vec3 Force;

	

	//Physics variables
	glm::vec3 m_vel, m_accel;
	glm::vec3 m_rotVel;
	glm::vec3 m_iniVel;

	float m_mass;
	float m_restitution;

	//Shape of the collision pollygon
	int m_shape;

	//Forces switches
	bool m_enableWind = false;
	bool m_enableGravity = true;

public:

	//Forces applied to this object
	std::vector<Force> m_forces;

	//If the object is immovable
	bool isFixed = false;

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
	void setWind(bool enableWind) { m_enableWind = enableWind; }
	void setGravity(bool enableGravity) { m_enableGravity = enableGravity; }

	//Getters
	int getShape() { return m_shape; }
	float getRestitution() { return m_restitution; }
	glm::vec3 * getVel() { return &m_vel; }
	float getMass() { return m_mass; }
	glm::vec3 * getRotVel() { return &m_rotVel; }
};

#endif

