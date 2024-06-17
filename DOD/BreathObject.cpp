#include "BreathObject.h"
#include "RenderSprite.h"
#include "Path.h"

BreathObject::BreathObject() :
	breathTransform{ nullptr },
	_breathComponent{ nullptr },
	_bossptr{ nullptr },
	_smokeObject{ nullptr },
	_timer{ 0.0 },
	_disableTimer{5.0},
	_startSmokeTimer{3.0},
	_isStartSmoke{false}
{

}

BreathObject::~BreathObject()
{

}

void BreathObject::OnCreate()
{
	_smokeObject = engineptr->RegisterGameObject<SmokeObject>(L"Smoke");
	auto smokeRenderSprite = new dod::RenderSprite(0, 0, 7);
	/// 스프라이트 추가 코드
	smokeRenderSprite->PushBackImageDataVector(IMAGE_PATH(Effect\\Smoke\\Sheet\\Smoke_Sheet.png), 0.2);
	_smokeObject->AddComponent(smokeRenderSprite);
	auto smokeTransform = _smokeObject->GetComponent<dod::Transform>();
	smokeTransform->SetParent(this->GetComponent<dod::Transform>());
	smokeTransform->position.x = 0;
	smokeTransform->position.y = 0;
	smokeTransform->scale.x = GetComponent<dod::Transform>()->scale.x * 2;
	smokeTransform->scale.y = GetComponent<dod::Transform>()->scale.y * 2;
}

void BreathObject::OnEnable()
{
	_timer = 0.0;
	_isStartSmoke = false;
	((dod::RenderSprite*)_breathComponent)->ChangeCurrentAnimationIndex(0);
}

void BreathObject::OnUpdate()
{
	_timer += engineptr->timer.GetDeltaTime();

	if (_timer > _startSmokeTimer)
	{
		if (!_isStartSmoke)
		{
			_smokeObject->Enable();
			_isStartSmoke = true;
		}
	}

	if (_timer > _disableTimer)
	{
		Disable();
	}
}

void BreathObject::OnDisable()
{

}

void BreathObject::OnRelease()
{

}

void BreathObject::BreathInitalation()
{
	_breathComponent = GetComponent<dod::RenderComponent>();
	breathTransform = GetComponent<dod::Transform>();
}

void BreathObject::BreathTransform()
{

}

void BreathObject::BossParentSet(Boss* bossptr)
{
	_bossptr = bossptr;
}

