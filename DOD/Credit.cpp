#include "GameObject.h"
#include "SceneManager.h"
#include "KeyComponent.h"
#include "GameEngine.h"
#include "RenderSprite.h"
#include "Credit.h"
#include "Path.h"
#include "TitleScene.h"
#include "CreditPrinter.h"

Credit::Credit()
	: activecheck(true)
	, sceneManager(nullptr)
	, _engineptr(nullptr)
	, _pImagePrinter(nullptr)
	, _pCreditRenderSprite(nullptr)
{

}

Credit::~Credit()
{

}

void Credit::CutScene()
{
	if (activecheck)
	{
		_pImagePrinter->Enable();
	}

	if (!activecheck)
	{
		Disabler();
		activecheck = true;
	}
}

void Credit::InitializeScene(dod::GameEngine* engine, SceneManager* sceneManager)
{
	_engineptr = engine;
	this->sceneManager = sceneManager;

	_pImagePrinter = (CreditPrinter*)engine->RegisterGameObject<dod::GameObject>(L"CraditViewer");
	_pCreditRenderSprite = new dod::RenderSprite(0, 0, 6);
	_pCreditRenderSprite->PushBackImageDataVector(IMAGE_PATH(Illust\\¿£µùÄÆ½ÅÅ©·¹µ÷¿¹½Ã.png));
	_pImagePrinter->AddComponent(_pCreditRenderSprite);
	_pImagePrinter->sceneManager = sceneManager;

	dod::KeyComponent* tempKeyComponent = new dod::KeyComponent;
	_pImagePrinter->AddComponent(tempKeyComponent);
	_pImagePrinter->GetComponent < dod::Transform>()->position.x = 950;
	_pImagePrinter->GetComponent < dod::Transform>()->position.y = 520;

	tempKeyComponent->onKeyDown = [](const dod::KeyInfo& keyinfo, const dod::GameObject& thisObject)
	{
		 CreditPrinter* CreditObject = (CreditPrinter*)&thisObject;
		if (keyinfo.code == dod::eButtonCode::PAD_DPAD_B)
		{
			CreditObject->sceneManager->gameScene = SceneManager::eGameScene::Title;
			CreditObject->Disable();
			CreditObject->sceneManager->title->activecheck = true;
		}
	};
}

void Credit::Disabler()
{
	_pImagePrinter->Disable();
}
