#include "thornObject.h"
#include "RenderComponent.h"
#include "Transform.h"

thornObject::thornObject() : thornTransform{ 0 }, _thornComponent{ 0 }, _bossptr{ 0 }
{

}

thornObject::~thornObject()
{

}

void thornObject::OnCreate()
{

}

void thornObject::OnEnable()
{

}

void thornObject::OnUpdate()
{

}

void thornObject::OnDisable()
{

}

void thornObject::OnRelease()
{

}

void thornObject::ThornCreate()
{

}

void thornObject::ThornInitalation()
{
	_thornComponent = GetComponent<dod::RenderComponent>();
	thornTransform = GetComponent<dod::Transform>();

}

void thornObject::BossParentSet(Boss* bossptr)
{
	_bossptr = bossptr;
}

void thornObject::TargetEnable(dod::Transform transform)  //매개변수로 받을수 있을까? 트랜스폼을 받아 그 위치에 출력
{

}
