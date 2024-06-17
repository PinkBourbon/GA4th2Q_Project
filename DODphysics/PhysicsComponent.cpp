#include "PhysicsComponent.h"
#include <iostream>
#include "Macro.h"

namespace dod
{
	PhysicsComponent::PhysicsComponent(ePhysicsComponentType ePType)
		: IComponent(eComponentType::Physics)
		, isTrigger(false), isCollide(false), _force(), _acceleration(), _velocity(), _mass(50.0f)
		, _componentContainerIndex(0)
		, _isStopped(false)
		, _componentType(ePType)
		, collisionLayerNumber(1)
		, collisionFlag(false)
		, onCollisionEnter([](GameObject*, GameObject*) {})
		, onCollisionStay([](GameObject*, GameObject*) {})
		, onCollisionExit([](GameObject*, GameObject*) {})
	{

	}

	PhysicsComponent::~PhysicsComponent() = default;

	void PhysicsComponent::SetVelocity(float velX, float velY)
	{
		_velocity.x = velX;
		_velocity.y = velY;
	}

	void PhysicsComponent::AddForce(Vector3 force)
	{
		this->_force = force;
	}

	void PhysicsComponent::ResetForce()
	{
		_force.x = 0;
		_force.y = 0;
		_force.z = 0;
	}

	void PhysicsComponent::ResetVelocity()
	{
		_velocity.x = 0;
		_velocity.y = 0;
		_velocity.z = 0;
	}

	dod::Vector3 PhysicsComponent::GetVelocity()
	{
		return _velocity;
	}

	void PhysicsComponent::SetMass(float mass)
	{
		Assert(mass >= 0, "질량은 음수가 될 수 없습니다.");
		_mass = mass;
	}

}