#include "Macro.h"
#include "IComponent.h"
#include "GameObject.h"
#include "GameEngine.h"
#include "RenderComponent.h"
#include "Transform.h"
#include "KeyComponent.h"

dod::GameObject::GameObject()
	: objState(eObjectState::OnCreate)
	//, isRender(true)
	, earlyDisabled(false)
	, _componentArray{ 0 }
	, engineptr(nullptr)
{
	Transform* ptr = new Transform();
	ptr->scale.x = 1.0f;
	ptr->scale.y = 1.0f;
	AddComponent(ptr);
};

void dod::GameObject::Enable()
{
	if (this == nullptr)
	{
		return;
	}
	engineptr->InputChangeStateBuffer(eObjectState::OnEnable, this);
}

void dod::GameObject::Disable()
{
	if (this != nullptr)
	{
		engineptr->InputChangeStateBuffer(eObjectState::OnDisable, this);
		earlyDisabled = true;
	}
	return;
}

void dod::GameObject::Release()
{
	if (this != nullptr)
	{
		engineptr->InputChangeStateBuffer(eObjectState::OnRelease, this);
	}
}

void dod::GameObject::AddComponent(IComponent* pComponent)
{
	pComponent->_pObejct = this;
	switch (pComponent->_componentType)
	{
		case dod::eComponentType::Transform:
			if (_componentArray[(int)eComponentType::Transform] == nullptr)
			{
				_componentArray[(int)eComponentType::Transform] = pComponent;
			}
			else
			{
				Assert(false, "트랜스폼이 이미 설정 됨, 재설정 불가능");
			}
				
			break;

		case dod::eComponentType::Physics:
			if (_componentArray[(int)eComponentType::Physics] == nullptr)
			{
				_componentArray[(int)eComponentType::Physics] = pComponent;
			}
			else
			{
				// Assert(false, "물리 컴포넌트가 이미 설정 됨, 재설정 불가능");
				// BossArm 패턴 충돌범위를 수정해야 할 일이 있어서 주석처리 -ajy
			}
			break;

		case dod::eComponentType::Render:
			if (_componentArray[(int)eComponentType::Render] == nullptr)
			{
				_componentArray[(int)eComponentType::Render] = pComponent;
				((RenderComponent*)pComponent)->SetTransform((Transform*)(this->_componentArray[(int)eComponentType::Transform]));
			}
			else
			{
				Assert(false, "랜더 컴포넌트가 이미 설정 됨, 재설정 불가능");
			}
			break;

		case dod::eComponentType::Controller:
			if (_componentArray[(int)eComponentType::Controller] == nullptr)
			{
				_componentArray[(int)eComponentType::Controller] = pComponent;	
			}
			else
			{
				Assert(false, "컨트롤러가 이미 설정 됨, 재설정 불가능");
			}
			break;

		default:
			Assert(false, "이 메세지를 발견한다면 즉시 프로그램을 종료하고 개발자에게 연락해야 합니다.");
			break;
	}
}

dod::GameObject* dod::GameObject::GetGameObject(std::wstring _name)
{
	return engineptr->GetObjectptr(_name);
}

bool dod::GameObject::CheckObjectExiests(std::wstring _name)
{
	void* ptr = GetGameObject(_name);
	if (ptr == nullptr)
	{
		return false;
	}

	return true;
}