#include <iostream>
#include <string>

#include "Timer.h"
#include "GameEngine.h"
#include "Id2d.h"
#include "KeyManager.h"
#include "PhysicsEngine.h"
#include "IPhysics.h"
#include "Transform.h"


#pragma comment (lib, "DODd2d.lib")
#pragma comment (lib, "DODphysics.lib")
#pragma comment(lib, "fmod_vc.lib")

dod::GameEngine::GameEngine()
{
	_pD2dEngine = CreateD2dEngine();
	_pKeyManger = nullptr;
	_physicsEngine = nullptr;
	soundManager = nullptr;

	timer.SetTimeScale(1.0);
}

dod::GameEngine::~GameEngine()
{
}

void dod::GameEngine::GameLoop()
{
	timer.Update();

	moveWaitingPooltoObjectPool();

	setGameObjectState(eObjectState::OnCreate);
	OnCreate();

	setGameObjectState(eObjectState::OnEnable);
	OnEnable();

	Physics();

	OnKeyCheck();

	OnUpdate();
	setGameObjectState(eObjectState::OnUpdate);

	Render();

	setGameObjectState(eObjectState::OnDisable);
	OnDisable();

	setGameObjectState(eObjectState::OnRelease);
	OnRelease();
}

void dod::GameEngine::InitializeD2dEngine(HWND hWnd, int screenWidth, int screenHeight)
{
	_pD2dEngine->Initialize(hWnd, screenWidth, screenHeight);
}


void dod::GameEngine::InitializeKeyManger(HWND hWnd)
{
	_pKeyManger = new KeyManager(hWnd);
}

void dod::GameEngine::InitializePhysicsEngine()
{
	_physicsEngine = new PhysicsEngine();
}

void dod::GameEngine::InitializeSoundManager()
{
	soundManager = new SoundManager();
}

void dod::GameEngine::OnCreate()
{
	std::vector<GameObject*>::iterator iter = _objectPool.begin();
	for (; iter != _objectPool.end(); iter++)
	{
		if ((*iter)->objState == eObjectState::OnCreate)
		{
			(*iter)->OnCreate();
			(*iter)->objState = eObjectState::OnDisable;
		}
	}
}

void dod::GameEngine::OnEnable()
{
	std::vector<GameObject*>::iterator iter = _objectPool.begin();
	for (; iter != _objectPool.end(); iter++)
	{
		if ((*iter)->objState == eObjectState::OnEnable)
		{
			(*iter)->OnEnable();
			InputChangeStateBuffer(eObjectState::OnUpdate, (*iter));

			RenderComponent* renderComponent = (*iter)->GetComponent<RenderComponent>();
			if (renderComponent != nullptr)
			{
				_pD2dEngine->EnrollComponent(renderComponent);
			}

			KeyComponent* keyComponent = (*iter)->GetComponent<KeyComponent>();
			if (keyComponent != nullptr)
			{
				_pKeyManger->EnrollComponent(keyComponent);
			}

			PhysicsComponent* physicsComponent = (*iter)->GetComponent<PhysicsComponent>();
			if (physicsComponent != nullptr)
			{
				_physicsEngine->EnrollComponent(physicsComponent);
			}
			(*iter)->earlyDisabled = true;
		}
	}
}

void dod::GameEngine::OnUpdate()
{
	std::vector<GameObject*>::iterator iter = _objectPool.begin();
	for (; iter != _objectPool.end(); iter++)
	{
		if ((*iter)->objState == eObjectState::OnUpdate)
		{
			(*iter)->OnUpdate();
		}
	}
}

void dod::GameEngine::OnDisable()
{
	std::vector<GameObject*>::iterator iter = _objectPool.begin();
	for (; iter != _objectPool.end(); iter++)
	{
		if ((*iter)->objState == eObjectState::OnDisable && (*iter)->earlyDisabled != false)
		{
			(*iter)->OnDisable();
			RenderComponent* renderComponent = (*iter)->GetComponent<RenderComponent>();
			if (renderComponent != nullptr)
			{
				_pD2dEngine->DisenrollComponent(renderComponent);
			}

			KeyComponent* keyComponent = (*iter)->GetComponent<KeyComponent>();
			if (keyComponent != nullptr)
			{
				_pKeyManger->DisenrollComponent(keyComponent);
			}

			PhysicsComponent* physicsComponent = (*iter)->GetComponent<PhysicsComponent>();
			if (physicsComponent != nullptr)
			{
				_physicsEngine->DisenrollComponent(physicsComponent);
			}
			(*iter)->earlyDisabled = false;
		}
	}
}

void dod::GameEngine::OnRelease()
{
	std::vector<GameObject*>::iterator iter = _objectPool.begin();
	for (; iter != _objectPool.end(); iter++)
	{
		if ((*iter)->objState == eObjectState::OnRelease)
		{
			(*iter)->OnRelease();
			delete (*iter);
			_objectPool.erase(iter);
			iter = _objectPool.begin();
			if (_objectPool.begin() == _objectPool.end())
				return;
		}
	}
}

void dod::GameEngine::InputChangeStateBuffer(eObjectState state, GameObject* ptr)
{
	switch (state)
	{
		case dod::eObjectState::OnCreate:
			_createObjectBuffer.push_back(ptr);
			break;
		case dod::eObjectState::OnEnable:
			_EnableStateBuffer.push_back(ptr);
			break;
		case dod::eObjectState::OnUpdate:
			 _UpdateStateBuffer.push_back(ptr);
			break;
		case dod::eObjectState::OnDisable:
			_DisableStateBuffer.push_back(ptr);
			break;
		case dod::eObjectState::OnRelease:
			_ReleaseStateBuffer.push_back(ptr);
			break;
		default:
			break;
	}
}

dod::GameObject* dod::GameEngine::GetObjectptr(std::wstring objectName)
{
	std::vector<GameObject*>::iterator itr = _objectPool.begin();
	for (; itr != _objectPool.end(); itr++)
	{
		if ((*itr)->objectName == objectName)
		{
			return *itr;
		}
	}

	Assert(false, "그런 오브젝트 없음 ㅅㄱ");
	return nullptr;
}

void dod::GameEngine::Render()
{
	_pD2dEngine->AllRender(timer.GetDeltaTime());

}

void dod::GameEngine::Physics()
{
	_physicsEngine->Physics(timer.GetDeltaTime());
}

void dod::GameEngine::OnKeyCheck()
{
	_pKeyManger->KeyInput();
	_pKeyManger->PadInput();
}

void dod::GameEngine::setGameObjectState(eObjectState type)
{
	std::vector<GameObject*>* pBuffer = nullptr;

	switch (type)
	{
		case dod::eObjectState::OnCreate:
			pBuffer = &_createObjectBuffer;
			break;
		case dod::eObjectState::OnEnable:
			pBuffer = &_EnableStateBuffer;
			break;
		case dod::eObjectState::OnUpdate:
			pBuffer = &_UpdateStateBuffer;
			break;
		case dod::eObjectState::OnDisable:
			pBuffer = &_DisableStateBuffer;
			break;
		case dod::eObjectState::OnRelease:
			pBuffer = &_ReleaseStateBuffer;
			break;
		default:
			break;
	}

	if (pBuffer == nullptr)
	{
		return;
	}

	for (auto& e : *pBuffer)
	{
		e->objState = type;
	}
	
	pBuffer->clear();
}

void dod::GameEngine::moveWaitingPooltoObjectPool()
{
	std::vector<GameObject*>::iterator itr = _createObjectBuffer.begin();
	for (; itr != _createObjectBuffer.end(); itr++)
	{
		_objectPool.push_back(*itr);
	}
	_createObjectBuffer.clear();
}

void dod::GameEngine::SetCameraObject(Transform* transform)
{
	_pD2dEngine->SetCamera(transform);
}

namespace dod
{
	GameEngine g_GameEngine;
}

