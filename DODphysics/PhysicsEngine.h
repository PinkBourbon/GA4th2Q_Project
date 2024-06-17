#pragma once

#include "IPhysics.h"
#include "Circle.h"
#include "Rectangle.h"
#include <unordered_set>

namespace dod
{
	class GameObject;
	class PhysicsComponent;
	class Circle;
	struct Transform;

	class PhysicsEngine : public IPhysics
	{
	public:
		PhysicsEngine();
		~PhysicsEngine();
		void Physics(double deltaTime)override;		// IPhysics ���� ȣ�� ��, ��� �������� �����ϴ� �Լ�
		void EnrollComponent(PhysicsComponent* physComponent)override;				// ���������� ����� �Ǵ� GameObject���� �ּҸ� componentContainer�� ���
		void DisenrollComponent(PhysicsComponent* physComponent)override;			// ���̻� ����� �ƴ� ���� ��� ����

	protected:
		std::unordered_set<PhysicsComponent*> componentContainer;		// ������Ʈ �����̳�
		void Control();						// �ܺο��� �޾ƿ� Ű �Է¿� ���� � ������ ���� �����Ѵ�
		void DetectCollision();	// ������Ʈ �� �浹�� �����Ѵ�
		void CollideAction(PhysicsComponent* physCom1, PhysicsComponent* physCom2, bool collision);
		void Collide(PhysicsComponent& physCom1, PhysicsComponent& physCom2, Transform* tr1, Transform* tr2, int caseNum);	// �浹�� ������ �����Ѵ�
		void Acceleration(float deltaTime);
		void Move(float deltaTime);						// ������Ʈ�� �̵��� �����Ѵ�
		void Stop(PhysicsComponent* physCom);			// ��������
		bool CircleCollision(Circle& circle1, Circle& circle2);
		bool ExtendedAABBCollision(Circle& circle, Rectangle& rect);
		bool AABBCollision(Rectangle& rect1, Rectangle& rect2);
	};
}
