#include "StoneObject.h"
#include "RenderComponent.h"
#include "Transform.h"

StoneObject::StoneObject() : _stoneComponent{ 0 }, _stoneTransform{ 0 }
{
	_speed = 600;
}

StoneObject::~StoneObject()
{

}

void StoneObject::OnCreate()
{

}

void StoneObject::OnEnable()
{

}

void StoneObject::OnUpdate()
{

}

void StoneObject::OnDisable()
{

}

void StoneObject::OnRelease()
{

}

void StoneObject::StoneInitalation()
{
	_stoneComponent = GetComponent<dod::RenderComponent>();
	_stoneTransform = GetComponent<dod::Transform>();
}

// void StoneObject::CreateStone(int i)
// {
// 	_engineptr->RegisterGameObject<StoneObject>(L"StoneObject");
// 	Disable();
// }

void StoneObject::StoneTransform(int i)
{
	_stoneTransform->position.x = (float)(350 + i * 250);
	_stoneTransform->position.y = (float)300;
}

void StoneObject::StoneMove()
{
	_stoneTransform->position.y += (float)engineptr->timer.GetDeltaTime() * _speed;
}

