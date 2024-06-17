#include "PhysicsEngine.h"
#include "Vector3.h"
#include "GameObject.h"
#include "Transform.h"

#include <vector>
#include <cmath>

namespace dod
{
	PhysicsEngine::PhysicsEngine()
	{

	}

	PhysicsEngine::~PhysicsEngine()
	{

	}

	void PhysicsEngine::Physics(double deltaTime)
	{
		Control();
		DetectCollision();
		//Acceleration(deltaTime);
		Move((float)deltaTime);

		// 컴포넌트 컨테이너 돌면서 충돌 처리, 물리 연산, 충돌시 콜백 함수 호출
		//for (int i = 0; i < componentContainer.size(); i++)
		//{	}
	}

	void PhysicsEngine::EnrollComponent(PhysicsComponent* physComponent)
	{
		componentContainer.insert(physComponent);
	}

	void PhysicsEngine::DisenrollComponent(PhysicsComponent* physComponent)
	{
		componentContainer.erase(physComponent);
	}

	void PhysicsEngine::Control()
	{
		// 키 입력에 따라 속도값 조정
	}

	void PhysicsEngine::DetectCollision()
	{
		if (componentContainer.size() < 2)
		{
			return;
		}
		auto iter1 = componentContainer.begin();
		int i = 0;
		for (iter1; iter1 != componentContainer.end(); iter1++)
		{
			i++;
			auto iter2 = componentContainer.begin();
			std::advance(iter2, i);
			for (iter2; iter2 != componentContainer.end(); iter2++)
			{
				if (((*iter1)->isTrigger == false) && ((*iter2)->isTrigger == false))
				{
					int typePhysCom1 = (*iter1)->_componentType;
					int typePhysCom2 = (*iter2)->_componentType;
					if ((typePhysCom1 == CircleType) && (typePhysCom2 == CircleType))
					{
						if (CircleCollision(*(Circle*)(*iter1), *(Circle*)(*iter2)) == true)
						{
							CollideAction(*iter1, *iter2, true);
						}
						else
						{
							CollideAction(*iter1, *iter2, false);
						}
					}
					else if ((typePhysCom1 == RectangleType) && (typePhysCom2 == RectangleType))
					{
						if (AABBCollision(*(Rectangle*)(*iter1), *(Rectangle*)(*iter2)) == true)
						{
							CollideAction(*iter1, *iter2, true);
						}
						else
						{
							CollideAction(*iter1, *iter2, false);
						}
						//AABBCollision(*(Rectangle*)(*iter1), *(Rectangle*)(*iter2));
					}
					else if ((typePhysCom1 == CircleType) && (typePhysCom2 == RectangleType))
					{
						if (ExtendedAABBCollision(*(Circle*)(*iter1), *(Rectangle*)(*iter2)) == true)
						{
							CollideAction(*iter1, *iter2, true);
						}
						else
						{
							CollideAction(*iter1, *iter2, false);
						}
					}
					else if ((typePhysCom1 == RectangleType) && (typePhysCom2 == CircleType))
					{
						if (ExtendedAABBCollision(*(Circle*)(*iter2), *(Rectangle*)(*iter1)) == true)
						{
							CollideAction(*iter1, *iter2, true);
						}
						else
						{
							CollideAction(*iter1, *iter2, false);
						}
					}
					else
					{
						CollideAction(*iter1, *iter2, false);
					}
				}
			}
		}
		return;
	}

	void PhysicsEngine::CollideAction(PhysicsComponent* physCom1, PhysicsComponent* physCom2, bool collision)
	{
		if (collision == true)	// 충돌을 했을 때
		{
			if ((physCom1->colliderContainer.find(physCom2) != physCom1->colliderContainer.end()))	// 검색해서 있으면
			{
				Assert(physCom2->colliderContainer.find(physCom1) != physCom2->colliderContainer.end(),
					"두 충돌 대상의 충돌정보가 한 쪽에만 들어 있습니다.");
				auto object1 = physCom1->GetObject();
				auto object2 = physCom2->GetObject();
				physCom1->onCollisionStay(object1, object2);
				physCom2->onCollisionStay(object2, object1);
			}
			else // 검색해서 없으면
			{
				auto object1 = physCom1->GetObject();
				auto object2 = physCom2->GetObject();
				physCom1->onCollisionEnter(object1, object2);
				physCom2->onCollisionEnter(object2, object1);

				physCom1->colliderContainer.insert(physCom2);
				physCom2->colliderContainer.insert(physCom1);
			}
		}
		else // 충돌을 안했을 때
		{
			if (physCom1->colliderContainer.find(physCom2) != physCom1->colliderContainer.end())	// 검색해서 있으면
			{
				auto object1 = physCom1->GetObject();
				auto object2 = physCom2->GetObject();
				physCom1->onCollisionExit(object1, object2);
				physCom2->onCollisionExit(object2, object1);

				physCom1->colliderContainer.erase(physCom2);
				physCom2->colliderContainer.erase(physCom1);
			}
		}
	}

	void PhysicsEngine::Collide(PhysicsComponent& physCom1, PhysicsComponent& physCom2, Transform* tr1, Transform* tr2, int caseNum)
	{
		switch (caseNum)
		{
			case (CircleType):
			{
				Vector3 collisionVector
				{
					tr2->position.x - tr1->position.x,
					tr2->position.y - tr1->position.y,
					0
				};

				float length = collisionVector.GetLength();

				collisionVector.x /= length;	// normalization
				collisionVector.y /= length;

				float magnitude1 = collisionVector.x * physCom1._velocity.x
					+ collisionVector.y * physCom1._velocity.y;

				Vector3 c1velocityVertical
				{
					 collisionVector.x * magnitude1,
					 collisionVector.y * magnitude1,
					 0
				};

				collisionVector.x = -collisionVector.x;
				collisionVector.y = -collisionVector.y;

				float magnitude2 = collisionVector.x * physCom2._velocity.x
					+ collisionVector.y * physCom2._velocity.y;

				Vector3 c2velocityVertical
				{
					 collisionVector.x * magnitude2,
					 collisionVector.y * magnitude2,
					 0
				};

				physCom1.SetVelocity(physCom1._velocity.x - c1velocityVertical.x + c2velocityVertical.x,
					physCom1._velocity.y - c1velocityVertical.y + c2velocityVertical.y);
				physCom2.SetVelocity(physCom2._velocity.x - c2velocityVertical.x + c1velocityVertical.x,
					physCom2._velocity.y - c2velocityVertical.y + c1velocityVertical.y);
			}
			case(RectangleType):
			{

			}
			default:
			{

			}
		}
	}

	void PhysicsEngine::Acceleration(float deltaTime)
	{
		if (componentContainer.size() < 3)
		{
			return;
		}
		for (auto& element : componentContainer)
		{
			if (element == nullptr)
			{
				continue;
			}
			//if ((int)(element->GetObject()->GetComponent<Transform>()->position.y) >= 300.0f)
			//{
			//	Stop(element);
			//}
			//else if ((int)(element->GetObject()->GetComponent<Transform>()->position.y) < 300)
			//{
			//	element->_force.y = element->_force.y + 0.001f;
			//}	// 임시 중력 구현
			element->_acceleration.x = element->_acceleration.x + (element->_force.x / element->_mass);
			element->_acceleration.y = element->_acceleration.y + (element->_force.y / element->_mass);
			element->_velocity.x = element->_velocity.x + element->_acceleration.x;
			element->_velocity.y = element->_velocity.y + element->_acceleration.y;
			if ((element->_force.x) * (element->_velocity.x) > 0)
			{
				element->_force.x = element->_force.x * 0.01f;
			}
			if ((element->_force.y) * (element->_velocity.y) > 0)
			{
				element->_force.y = element->_force.y * 0.01f;
			}
			//if (element->_force.x == 0.0f)
			//{
			//	element->_velocity.x = 0.0f;
			//}
			//if (element->_force.y == 0.0f)
			//{
			//	element->_velocity.y = 0.0f;
			//}
		}
	}

	void PhysicsEngine::Move(float deltaTime)
	{
		// 읽어온 Transform을 변경해준다
		// unordered set의 시작부터 끝까지, 스스로의 Transform-position에 속도를 더해준다.
		//Acceleration(deltaTime);
		for (auto& element : componentContainer)
		{
			Assert(element != nullptr, "Move를 수행할 컴포넌트가 존재하지 않음");
			Transform* pTr = element->GetObject()->GetComponent<Transform>();
			pTr->position.x += element->_velocity.x;
			pTr->position.y += element->_velocity.y;
			//if (element->_force.x == 0)
			//{
			//	element->_velocity.x = 0;
			//}
			//if (element->_force.y == 0)
			//{
			//	element->_velocity.y = 0;
			//}
		}
	}

	void PhysicsEngine::Stop(PhysicsComponent* physCom)
	{
		if (physCom->_isStopped == false)
		{
			physCom->_velocity.x = 0;
			physCom->_velocity.y = 0;
			physCom->_force.x = 0;
			physCom->_force.y = 0;
			physCom->_isStopped = true;
		}
		else
		{
			physCom->_isStopped = false;
		}

	}

	bool PhysicsEngine::CircleCollision(Circle& circle1, Circle& circle2)
	{
		float radiusSum = circle1._radius + circle2._radius;
		Transform* tr1 = circle1.GetObject()->GetComponent<Transform>();
		Transform* tr2 = circle2.GetObject()->GetComponent<Transform>();
		double distBetweenCenter = sqrt(pow((tr1->position.x - tr2->position.x), 2) + pow((tr1->position.y - tr2->position.y), 2));
		// radius 값 읽어오기

		if (radiusSum >= distBetweenCenter)
		{
			circle1.isCollide = true;
			circle2.isCollide = true;
			return true;
		}
		else
		{
			circle1.isCollide = false;
			circle2.isCollide = false;
			if ((circle1.collisionFlag == true) && (circle2.collisionFlag == true))
			{
				auto object1 = circle1.GetObject();
				auto object2 = circle2.GetObject();
				circle1.onCollisionExit(object1, object2);
				circle2.onCollisionExit(object2, object1);
				circle1.collisionFlag = false;
				circle2.collisionFlag = false;
				return false;
			}
		}
		return false;
	}

	bool PhysicsEngine::ExtendedAABBCollision(Circle& circle, Rectangle& rect)	// 일단 플레이어-보스팔or가시 충돌만 고려
	{
		// object1을 circle, object2가 rect로 두고 진행
		Transform* tr1 = circle.GetObject()->GetComponent<Transform>();
		Transform* tr2 = rect.GetObject()->GetComponent<Transform>();

		Vector3 vectBetweenCenter(tr1->position.x - tr2->GetTranformMatrix().matrix[2][0],
			tr1->position.y - tr2->GetTranformMatrix().matrix[2][1], 0);
		float angle = tr2->rotation;
		Vector3 temp(cos(angle), sin(angle), 0);
		Vector3 vectHorizontal(vectBetweenCenter.x * temp.x * temp.x,
			vectBetweenCenter.y * temp.y * temp.y, 0);
		Vector3 vectVertical(vectBetweenCenter.x - vectHorizontal.x,
			vectBetweenCenter.y - vectHorizontal.y, 0);

		bool isCollideHorizontal = false;
		bool isCollideHVertical = false;
		if (vectHorizontal.GetLength() <= circle._radius + rect.GetHalfWidth())
		{
			isCollideHorizontal = true;
		}
		else
		{
			isCollideHorizontal = false;
		}
		if (vectVertical.GetLength() <= circle._radius + 2*rect.GetHalfHeight())
		{
			isCollideHVertical = true;
		}
		else
		{
			isCollideHVertical = false;
		}

		if ((isCollideHorizontal == true) && (isCollideHVertical == true))
		{
			circle.isCollide = true;
			rect.isCollide = true;

			if ((circle.collisionFlag == false) && (rect.collisionFlag == false))
			{
				auto object1 = circle.GetObject();
				auto object2 = rect.GetObject();
				circle.onCollisionEnter(object1, object2);
				rect.onCollisionEnter(object2, object1);
				circle.collisionFlag = true;
				rect.collisionFlag = true;
				return true;
			}
		}
		else
		{
			circle.isCollide = false;
			rect.isCollide = false;
			if ((circle.collisionFlag == true) && (rect.collisionFlag == true))
			{
				auto object1 = circle.GetObject();
				auto object2 = rect.GetObject();
				circle.onCollisionExit(object1, object2);
				rect.onCollisionExit(object2, object1);
				circle.collisionFlag = false;
				rect.collisionFlag = false;
				return false;
			}
		}
		return false;
	}

	bool PhysicsEngine::AABBCollision(Rectangle& rect1, Rectangle& rect2)
	{
		Transform* tr1 = rect1.GetObject()->GetComponent<Transform>();
		Transform* tr2 = rect2.GetObject()->GetComponent<Transform>();

		float rect1X = tr1->GetTranformMatrix().matrix[2][0];
		float rect1Y = tr1->GetTranformMatrix().matrix[2][1];

		float rect1L = rect1X - rect1.GetHalfWidth();
		float rect1R = rect1X + rect1.GetHalfWidth();
		float rect1U = rect1Y - rect1.GetHalfHeight();
		float rect1D = rect1Y + rect1.GetHalfHeight();

		float rect2X = tr2->GetTranformMatrix().matrix[2][0];
		float rect2Y = tr2->GetTranformMatrix().matrix[2][1];

		float rect2L = rect2X - rect2.GetHalfWidth();
		float rect2R = rect2X + rect2.GetHalfWidth();
		float rect2U = rect2Y - rect2.GetHalfHeight();
		float rect2D = rect2Y + rect2.GetHalfHeight();

		if (rect1L > rect2R || rect1R < rect2L)
		{
			return false;
		}

		if (rect1U > rect2D || rect1D < rect2U)
		{
			return false;
		}

		return true;
	}
}