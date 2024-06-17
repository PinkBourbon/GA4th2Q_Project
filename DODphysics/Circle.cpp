#include "Circle.h"

namespace dod
{
	Circle::Circle()
		: PhysicsComponent(ePhysicsComponentType::CircleType), _radius(0)
	{

	}

	Circle::Circle(float radi)
		: PhysicsComponent(ePhysicsComponentType::CircleType), _radius(radi)
	{

	}

	Circle::~Circle()
	{

	}

	float Circle::GetRadius()
	{
		return _radius;
	}

	void Circle::SetRadius(float rad)
	{
		_radius = rad;
	}

}