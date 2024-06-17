#pragma once
#include "PhysicsComponent.h"

namespace dod
{
	class Circle : public PhysicsComponent
	{
		friend class PhysicsEngine;
	public:
		Circle();
		Circle(float radi);
		~Circle();
		float GetRadius();
		void SetRadius(float rad);

	private:
		float _radius;
	};
}