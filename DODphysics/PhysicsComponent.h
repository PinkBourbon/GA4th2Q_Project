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
		int collisionLayerNumber;		// 충돌 레이어 번호. 0번은 충돌감지x
		bool isTrigger;					// 충돌 연산 여부, false일때 충돌
		bool collisionFlag;
		bool isCollide;
		int _componentType;

		std::unordered_set<PhysicsComponent*> colliderContainer;		// 콜라이더 컨테이너

		std::function<void(GameObject* otherObject, GameObject* thisObject)> onCollisionEnter;	// 충돌 처리 함수를 콜백하는 functor
		std::function<void(GameObject* otherObject, GameObject* thisObject)> onCollisionStay;
		std::function<void(GameObject* otherObject, GameObject* thisObject)> onCollisionExit;

	protected:
		Vector3 _force;					// 벡터표현 힘. 3번째 요소는 0.
		Vector3 _acceleration;			// 벡터표현 가속도. 3번째 요소는 0.
		Vector3 _velocity;				// 벡터표현 속도. 3번째 요소는 0.
		float _mass;
		int _componentContainerIndex;
		bool _isStopped;
	};
}