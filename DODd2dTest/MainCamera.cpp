#include "MainCamera.h"
#include "KeyComponent.h"
#include "GameEngine.h"
#include "Transform.h"

using namespace dod;

MainCamera::MainCamera()
	: _transform(nullptr)
{

}

void MainCamera::OnCreate()
{
	KeyComponent* keyComponent = new KeyComponent();
	AddComponent(keyComponent);

	_transform = GetComponent<Transform>();
	_transform->position.x = 800;
	_transform->position.y = 600;
	Enable();

	keyComponent->onKeyStay = [&](const KeyInfo& keyinfo, const GameObject& thisObject) 
	{
		MainCamera* mainCamera = (MainCamera*)&thisObject;
		//MainCamera* mainCamera = (MainCamera*)(thisObject.engineptr->GetObjectptr(L"Camera"));

		if (keyinfo.code == dod::eButtonCode::KEY_SPACE)
		{
			_transform->scale.x *= 1.1f;
			_transform->scale.y *= 1.1f;
		}

		if (keyinfo.code == dod::eButtonCode::KEY_LCRTL)
		{
			_transform->scale.x *= 0.9f;
			_transform->scale.y *= 0.9f;
		}

		if (keyinfo.code == dod::eButtonCode::KEY_UP)
		{
			_transform->position.y += 3.f;
		}

		if (keyinfo.code == dod::eButtonCode::KEY_DOWN)
		{
			_transform->position.y -= 3.f;
		}

		if (keyinfo.code == dod::eButtonCode::KEY_RIGHT)
		{
			_transform->position.x -= 3.f;
		}

		if (keyinfo.code == dod::eButtonCode::KEY_LEFT)
		{
			_transform->position.x += 3.f;
		}
	};
}

void MainCamera::OnEnable()
{
	engineptr->SetCameraObject(GetComponent<Transform>());
}

void MainCamera::OnUpdate()
{

}

void MainCamera::OnDisable()
{

}

void MainCamera::OnRelease()
{

}
