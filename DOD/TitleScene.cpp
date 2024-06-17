#include "MainGame.h"
#include "GameEngine.h"
#include "RenderCircle.h"
#include "RenderComponent.h"
#include "RenderText.h"
#include "RenderRect.h"
#include "RenderLine.h"
#include "GameObject.h"
#include "Transform.h"
#include "KeyComponent.h"
#include "TestPlayer.h"
#include "TestDice.h"
#include "TestAttack.h"
#include "Boss.h"
#include "DiceController.h"
#include "TitleScene.h"
#include "SceneManager.h"
#include "Rectangle.h"
#include "RenderSprite.h"
#include "Path.h"

TitleScene::TitleScene()
	: _engineptr(0), pframePrinter(0), keyPrinter(0)
	, playbox2{ nullptr, nullptr, nullptr, nullptr,nullptr, nullptr }
	, uiBox(0), bgBox(0), tester(0)
	, activecheck(true), sceneManager(nullptr)
	, _pBackground(nullptr), soundPlayer(nullptr)
{

}

TitleScene::~TitleScene()
{

}

void TitleScene::TitleMain()
{
	if (activecheck)
	{
		for (int i = 0; i < 6; i++)
		{
			playbox2[i]->Enable();
		}
		_engineptr->soundManager->Sound_BGMpause(dod::STAGE_BGM);
		_engineptr->soundManager->Sound_BGMpause(dod::TITLE_BGM);
		_engineptr->soundManager->Sound_PlaySound(dod::MAINLOBBY_BGM);
		
		pframePrinter->Enable();
		keyPrinter->Enable();
		uiBox->Enable();
		bgBox->Enable();
		CreditBox->Enable();
		tester->Enable();
		_pBackground->Enable();
		_pLogoIcon->Enable();
		CreditBox->Enable();
		activecheck = false;
	}
}

void TitleScene::InitializeTitle(dod::GameEngine* engine, SceneManager* sceneManager)
{
	this->sceneManager = sceneManager;
	_engineptr = engine;

	//플레이어 생성
	tester = engine->RegisterGameObject<TestPlayer>(L"MenuTester");
	dod::PhysicsComponent* physics = tester->GetComponent<dod::PhysicsComponent>();
	tester->SetScene(sceneManager);

	soundPlayer = engine->RegisterGameObject<dod::GameObject>(L"SoundPlayer");

	// 게임시작 체크용 박스
	bgBox = engine->RegisterGameObject<dod::GameObject>(L"GameButton");
	bgBox->AddComponent(new dod::RenderRect(0, 0, 400, 376, 0));
	bgBox->GetComponent < dod::Transform >()->position.x = 960;
	bgBox->GetComponent < dod::Transform >()->position.y = 350;
	bgBox->AddComponent(new dod::Rectangle(200, 188));

	// 크래딧 씬 전환용 박스
	CreditBox = engine->RegisterGameObject<dod::GameObject>(L"CreditButton");
	CreditBox->AddComponent(new dod::RenderRect(0, 0, 200, 200, 0));
	CreditBox->GetComponent < dod::Transform >()->position.x = 150;
	CreditBox->GetComponent < dod::Transform >()->position.y = 400;
	CreditBox->AddComponent(new dod::Rectangle(100, 100));

	_engineptr->soundManager->Sound_CreateBGMSound(SOUND_PATH(BGM\\BGM_Lobby.ogg), dod::MAINLOBBY_BGM);
	_engineptr->soundManager->Sound_CreateBGMSound(SOUND_PATH(BGM\\BGM_Title.ogg), dod::TITLE_BGM);

	_engineptr->soundManager->Sound_PlaySound(dod::TITLE_BGM);
	//soundPlayer->engineptr->soundManager->Sound_BGMDownCtl(dod::MAINLOBBY_BGM);


	// 백그라운드 생성
	_pBackground = engine->RegisterGameObject<dod::GameObject>(L"TitleSceneBackGround");
	dod::RenderSprite* _pBackgroundSprite = new dod::RenderSprite(630, 355, 1);
	_pBackgroundSprite->PushBackImageDataVector(IMAGE_PATH(Background\\main_background.png));
	_pBackground->AddComponent(_pBackgroundSprite);
	_pBackground->GetComponent<dod::Transform>()->scale.x = 1.5f;
	_pBackground->GetComponent<dod::Transform>()->scale.y = 1.5f;

	_pLogoIcon = engine->RegisterGameObject<dod::GameObject>(L"TitleSceneLogoIcon");
	dod::RenderSprite* _pLogoIconSprite = new dod::RenderSprite(633, 355, 2);
	_pLogoIconSprite->PushBackImageDataVector(IMAGE_PATH(Background\\main_ui.png));
	_pLogoIcon->AddComponent(_pLogoIconSprite);
	_pLogoIcon->GetComponent<dod::Transform>()->scale.x = 1.5f;
	_pLogoIcon->GetComponent<dod::Transform>()->scale.y = 1.5f;
}

void TitleScene::Disabler()
{
	if (sceneManager->gameScene != SceneManager::eGameScene::Title)
	{
		for (int i = 0; i < 6; i++)
		{
			playbox2[i]->Enable();
		}
		pframePrinter->Disable();
		keyPrinter->Disable();
		uiBox->Disable();
		bgBox->Disable();
		tester->Disable();
		CreditBox->Disable();
		_pBackground->Disable();
		_pLogoIcon->Disable();

		activecheck = false;
	}
}
