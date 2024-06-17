#pragma once

#include "PhysicsComponent.h"

namespace dod
{
	class IPhysics
	{
	public:
		IPhysics();
		~IPhysics();
		virtual void Physics(double deltaTime);
		virtual void EnrollComponent(PhysicsComponent* physComponent);						// 컴포넌트를 등록
		virtual void DisenrollComponent(PhysicsComponent* physComponent);					// 등록한 컴포넌트를 해제	
	};
}