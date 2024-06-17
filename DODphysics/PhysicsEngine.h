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
		void Physics(double deltaTime)override;		// IPhysics 통해 호출 될, 모든 물리연산 수행하는 함수
		void EnrollComponent(PhysicsComponent* physComponent)override;				// 물리연산의 대상이 되는 GameObject들의 주소를 componentContainer에 등록
		void DisenrollComponent(PhysicsComponent* physComponent)override;			// 더이상 대상이 아닌 것을 등록 해제

	protected:
		std::unordered_set<PhysicsComponent*> componentContainer;		// 컴포넌트 컨테이너
		void Control();						// 외부에서 받아온 키 입력에 따라 어떤 연산을 할지 지정한다
		void DetectCollision();	// 오브젝트 간 충돌을 감지한다
		void CollideAction(PhysicsComponent* physCom1, PhysicsComponent* physCom2, bool collision);
		void Collide(PhysicsComponent& physCom1, PhysicsComponent& physCom2, Transform* tr1, Transform* tr2, int caseNum);	// 충돌시 연산을 수행한다
		void Acceleration(float deltaTime);
		void Move(float deltaTime);						// 오브젝트의 이동을 연산한다
		void Stop(PhysicsComponent* physCom);			// 정지정지
		bool CircleCollision(Circle& circle1, Circle& circle2);
		bool ExtendedAABBCollision(Circle& circle, Rectangle& rect);
		bool AABBCollision(Rectangle& rect1, Rectangle& rect2);
	};
}
