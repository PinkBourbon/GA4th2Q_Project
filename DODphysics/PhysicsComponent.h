#pragma once
#include <functional>
#include <unordered_set>
#include "Vector3.h"
#include "IComponent.h"

namespace dod
{
	enum ePhysicsComponentType
	{
		None,
		CircleType,
		RectangleType,
		Etc
	};

	class GameObject;

	class PhysicsComponent: public IComponent
	{
		friend class PhysicsEngine;

	public:
		PhysicsComponent(ePhysicsComponentType ePType);
		virtual ~PhysicsComponent() = 0;
		void SetVelocity(float velX, float velY);
		void AddForce(Vector3 force);
		void ResetForce();
		void ResetVelocity();
		Vector3 GetVelocity();
		void SetMass(float mass);

	public:
		int collisionLayerNumber;		// �浹 ���̾� ��ȣ. 0���� �浹����x
		bool isTrigger;					// �浹 ���� ����, false�϶� �浹
		bool collisionFlag;
		bool isCollide;
		int _componentType;

		std::unordered_set<PhysicsComponent*> colliderContainer;		// �ݶ��̴� �����̳�

		std::function<void(GameObject* otherObject, GameObject* thisObject)> onCollisionEnter;	// �浹 ó�� �Լ��� �ݹ��ϴ� functor
		std::function<void(GameObject* otherObject, GameObject* thisObject)> onCollisionStay;
		std::function<void(GameObject* otherObject, GameObject* thisObject)> onCollisionExit;

	protected:
		Vector3 _force;					// ����ǥ�� ��. 3��° ��Ҵ� 0.
		Vector3 _acceleration;			// ����ǥ�� ���ӵ�. 3��° ��Ҵ� 0.
		Vector3 _velocity;				// ����ǥ�� �ӵ�. 3��° ��Ҵ� 0.
		float _mass;
		int _componentContainerIndex;
		bool _isStopped;
	};
}