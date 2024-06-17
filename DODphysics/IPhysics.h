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
		virtual void EnrollComponent(PhysicsComponent* physComponent);						// ������Ʈ�� ���
		virtual void DisenrollComponent(PhysicsComponent* physComponent);					// ����� ������Ʈ�� ����	
	};
}