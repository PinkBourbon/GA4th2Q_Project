#pragma once
#include "PhysicsComponent.h"

namespace dod
{
	class Rectangle : public PhysicsComponent
	{
	public:
		Rectangle();
		Rectangle(float hW, float hH);
		~Rectangle();

		float GetHalfWidth();
		float GetHalfHeight();
		void SetHalfWidth(float width);
		void SetHalfHeight(float height);

	private:
		float _halfWidth;
		float _halfHeight;
		float _vertex[4];
	};
}
