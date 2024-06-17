#include "SmokeObject.h"
#include "GameEngine.h"
#include "RenderSprite.h"

SmokeObject::SmokeObject() : _timer{ 0.0 }, _disableTimer{ 5.0 }
{

}

SmokeObject::~SmokeObject()
{

}

void SmokeObject::OnCreate()
{

}

void SmokeObject::OnEnable()
{
	_timer = 0.0;
	dod::RenderSprite* renderSprite = (dod::RenderSprite*)this->GetComponent<dod::RenderComponent>();
	renderSprite->ChangeCurrentAnimationIndex(0);
}

void SmokeObject::OnUpdate()
{
	_timer += engineptr->timer.GetDeltaTime();
	if (_timer > _disableTimer)
	{
		Disable();
	}
}

void SmokeObject::OnDisable()
{

}

void SmokeObject::OnRelease()
{

}
