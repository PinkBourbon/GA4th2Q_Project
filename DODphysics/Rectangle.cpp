#include "Rectangle.h"

namespace dod
{
	Rectangle::Rectangle()
		: PhysicsComponent(ePhysicsComponentType::RectangleType)
		, _halfWidth(20), _halfHeight(20), _vertex()
	{

	}

	Rectangle::Rectangle(float hW, float hH)
		:PhysicsComponent(ePhysicsComponentType::RectangleType)
		,_halfWidth(hW), _halfHeight(hH), _vertex()
	{
		
	}

	Rectangle::~Rectangle()
	{

	}

	float Rectangle::GetHalfWidth()
	{
		return _halfWidth;
	}

	float Rectangle::GetHalfHeight()
	{
		return _halfHeight;
	}

	void Rectangle::SetHalfWidth(float width)
	{
		_halfWidth = width;
	}

	void Rectangle::SetHalfHeight(float height)
	{
		_halfHeight = height;
	}

}