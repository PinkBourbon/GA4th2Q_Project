#include "MainGame.h"
#include "GameEngine.h"
#include "RenderCircle.h"
#include "RenderComponent.h"
#include "RenderText.h"
#include "RenderRect.h"
#include "RenderLine.h"
#include "RenderSprite.h"
#include "GameObject.h"
#include "Transform.h"
#include "KeyComponent.h"
#include "TestPlayer.h"
#include "TestDice.h"
#include "TestAttack.h"
#include "Boss.h"
#include "Background.h"
#include "Curtain_top.h"
#include "GameTable.h"
#include "EndingCutScene.h"
#include "MainCamera.h"
#include "DiceController.h"
#include "AttackController.h"
#include "UIContoller.h"
#include "SceneManager.h"
#include "Path.h"

MainGame::MainGame()
	: _engineptr(0), pframePrinter(0), keyPrinter(0)
	, bgBox(0), tester(0), boss(0), diceController(0)
	, activecheck(true), sceneManager(nullptr), uiPlayerHPBack()
	, uiPlayerFace(), uiPlayerHP(), uiPlayerInventory(), uiPlayerInventoryOutLine()
	, uiPlayerSkillOutLine(), uiPlayerSkillIcon(), uiPlayerSkill()
	, _mainCamera(), background(), curtain_top(), gameTable(), uiController(), attackController()
	, soundPlayer(), isSoundPlayStage(false), enterFirst(true)
{
}

MainGame::~MainGame()
{
}

void MainGame::GameScene()
{

	static bool isSoundPlayEnding = false;
	static bool isSoundCreateStage = false;
	static bool isSoundCreateEnding = false;
	if (activecheck)
	{
		for (auto e : uiPlayerHP)
		{
			e->Enable();
		}
		for (auto e : uiPlayerHPBack)
		{
			e->Enable();
		}

		for (int i = 0; i < 5; i++)
		{
			uiPlayerInventory[i]->Enable();
			uiPlayerSkill[i]->Enable();
		}
		pframePrinter->Enable();
		keyPrinter->Enable();
		bgBox->Enable();
		uiPlayerFace->Enable();
		uiPlayerInventoryOutLine->Enable();
		uiPlayerSkillOutLine->Enable();
		uiPlayerSkillIcon->Enable();
		tester->Enable();
		boss->Enable();
		diceController->Enable();
		attackController->Enable();
		background->Enable();
		curtain_top->Enable();
		gameTable->Enable();
		uiController->Enable();
		activecheck = false;

		if (isSoundPlayStage == false)
		{
			_engineptr->soundManager->Sound_BGMpause(dod::MAINLOBBY_BGM);
			_engineptr->soundManager->Sound_PlaySound(dod::STAGE_BGM);
			isSoundPlayStage = true;
		}
		isSoundPlayEnding = false;

		tester->HP = 6;
		if (enterFirst)
		{
			boss->hP = boss->maxHp;	// 이제 확정임
			enterFirst = false;
		}
	}

	HeartChanger();

	if (boss->hP <= 0)
	{
		if (isSoundCreateEnding == false)
		{
			_engineptr->soundManager->Sound_CreateBGMSound(SOUND_PATH(BGM\\BGM_Ending.ogg), dod::ENDING_BGM);
			isSoundCreateEnding = true;
		}
		if (isSoundPlayEnding == false)
		{
			_engineptr->soundManager->Sound_SoundPause(dod::STAGE_BGM);
			_engineptr->soundManager->Sound_PlaySound(dod::ENDING_BGM);
			isSoundPlayEnding = true;
		}
		isSoundPlayStage = false;
		sceneManager->gameScene = SceneManager::eGameScene::EndCutscene;
		sceneManager->ending->activecheck = true;
		boss->hP = 1;
		Disabler();
	}
}

void MainGame::InitializeScene(dod::GameEngine* engine, SceneManager* sceneManager)
{
	this->sceneManager = sceneManager;
	_engineptr = engine;

	//플레이어 생성
	tester = engine->RegisterGameObject<TestPlayer>(L"Tester");
	tester->SetScene(sceneManager);

	//보스 생성
	boss = engine->RegisterGameObject<Boss>(L"Boss");

	// 배경 생성
	background = engine->RegisterGameObject<Background>(L"Background");
	curtain_top = engine->RegisterGameObject<Curtain_top>(L"Curtain_Top");
	gameTable = engine->RegisterGameObject<GameTable>(L"GameTable");

	// UI 관리자 생성
	uiController = engine->RegisterGameObject<UIController>(L"UIController");

	// 공격 관리자 생성
	attackController = engine->RegisterGameObject<AttackController>(L"AttackController");

	//주사위 관리자 생성
	diceController = engine->RegisterGameObject<DiceController>(L"DiceController");

	//프레임 출력용
	pframePrinter = engine->RegisterGameObject<dod::GameObject>(L"framePrinter");
	pframePrinter->AddComponent(new dod::RenderText(0, 0, 6));

	//사운드 출력 오브젝트 생성
	soundPlayer = engine->RegisterGameObject<dod::GameObject>(L"SoundPlayer");


	//입력받은 키 출력용
	keyPrinter = engine->RegisterGameObject<dod::GameObject>(L"keyPrinter");
	keyPrinter->AddComponent(new dod::RenderText(0, 15, 6));

	dod::KeyComponent* cptr = new dod::KeyComponent();
	keyPrinter->AddComponent(cptr);

	cptr->onKeyDown = [](const dod::KeyInfo& keyinfo, const dod::GameObject& thisObject)
	{
		((dod::RenderText*)(thisObject.GetComponent<dod::RenderComponent>()))->SetString(L"%d", ((int)(keyinfo.code)));
	};

	// 플레이어 hp와 초상화 부분
	uiPlayerFace = engine->RegisterGameObject<dod::GameObject>(L"Face");
	//uiPlayerFace->AddComponent(new dod::RenderRect(0, 0, 100, 160, 3));

	dod::RenderSprite* pUIPlayerFaceSprite = new dod::RenderSprite(0, 0, 5);
	pUIPlayerFaceSprite->PushBackImageDataVector(IMAGE_PATH(UI\\character_ui_player.png));
	uiPlayerFace->AddComponent(pUIPlayerFaceSprite);

	uiPlayerFace->GetComponent < dod::Transform >()->position.x = 110;
	uiPlayerFace->GetComponent < dod::Transform >()->position.y = 900;
	uiPlayerFace->GetComponent < dod::Transform >()->scale.x = 1.5f;
	uiPlayerFace->GetComponent < dod::Transform >()->scale.y = 1.5f;

	//플레이어 체력
	for (int i = 0; i < 3; i++)
	{
		dod::RenderSprite* pUIPlayerHPSprite = new dod::RenderSprite(0, 0, 5);
		_uiPlayerHPSpriteMap.insert({ 0, pUIPlayerHPSprite->PushBackImageDataVector(IMAGE_PATH(UI\\fullheart.png)) });
		_uiPlayerHPSpriteMap.insert({ 1, pUIPlayerHPSprite->PushBackImageDataVector(IMAGE_PATH(UI\\emptyheart.png)) });
		uiPlayerHP[i] = engine->RegisterGameObject<dod::GameObject>(L"Hp");

		uiPlayerHP[i]->AddComponent(pUIPlayerHPSprite);

		uiPlayerHP[i]->GetComponent<dod::Transform>()->position.y = 985;
		uiPlayerHP[i]->GetComponent<dod::Transform>()->position.x = 320.f + 65.f * i;
		uiPlayerHP[i]->GetComponent<dod::Transform>()->scale.x = 2.f;
		uiPlayerHP[i]->GetComponent<dod::Transform>()->scale.y = 2.f;

		dod::RenderSprite* pUIPlayerHPBackSprite = new dod::RenderSprite(0, 0, 6);
		pUIPlayerHPBackSprite->PushBackImageDataVector(IMAGE_PATH(UI\\Heart.png));
		pUIPlayerHPBackSprite->PushBackImageDataVector(IMAGE_PATH(UI\\Heart_Empty.png));

		uiPlayerHPBack[i] = engine->RegisterGameObject<dod::GameObject>(L"Hp");
		uiPlayerHPBack[i]->AddComponent(pUIPlayerHPBackSprite);
		uiPlayerHPBack[i]->GetComponent<dod::Transform>()->position.y = 985;
		uiPlayerHPBack[i]->GetComponent<dod::Transform>()->position.x = 320.f + 65.f * i;
		uiPlayerHPBack[i]->GetComponent<dod::Transform>()->scale.x = 1.9f;
		uiPlayerHPBack[i]->GetComponent<dod::Transform>()->scale.y = 1.9f;
	}

	// 플레이어 인벤토리					(스프라이트 사용x중)
	dod::RenderSprite* pUIPlayerInventorySprite = new dod::RenderSprite(0, 0, 0);
	pUIPlayerInventorySprite->PushBackImageDataVector(IMAGE_PATH(Reference\\dummy.jpg));
	for (int i = 0; i < 5; i++)
	{
		uiPlayerInventory[i] = engine->RegisterGameObject<dod::GameObject>(L"Inven");
		//uiPlayerInventory[i]->AddComponent(new dod::RenderRect(0, 0, 80, 80, 3));
		uiPlayerInventory[i]->AddComponent(pUIPlayerInventorySprite);
		uiPlayerInventory[i]->GetComponent < dod::Transform >()->position.y = 930;
		uiPlayerInventory[i]->GetComponent < dod::Transform >()->position.x = 720.f + 90.f * i;
	}

	dod::RenderSprite* pUIPlayerInventoryOutLineSprite = new dod::RenderSprite(0, 0, 5);

	pUIPlayerInventoryOutLineSprite->PushBackImageDataVector(IMAGE_PATH(UI\\inventory_ui.png));
	uiPlayerInventoryOutLine = engine->RegisterGameObject<dod::GameObject>(L"Inven");

	uiPlayerInventoryOutLine->AddComponent(pUIPlayerInventoryOutLineSprite); // 인벤 겉부분

	uiPlayerInventoryOutLine->GetComponent < dod::Transform >()->position.x = 950;
	uiPlayerInventoryOutLine->GetComponent < dod::Transform >()->position.y = 975;
	uiPlayerInventoryOutLine->GetComponent < dod::Transform >()->scale.x = 1.5f;
	uiPlayerInventoryOutLine->GetComponent < dod::Transform >()->scale.y = 1.3f;

	uiPlayerSkillOutLine = engine->RegisterGameObject<dod::GameObject>(L"SkillOutLine");
	dod::RenderSprite* uiPlayerSkillOutLineSprite = new dod::RenderSprite(0, 0, 5);
	uiPlayerSkillOutLineSprite->PushBackImageDataVector(IMAGE_PATH(UI\\Roulette\\new_Roulette.png));
	uiPlayerSkillOutLine->AddComponent(uiPlayerSkillOutLineSprite);
	uiPlayerSkillOutLine->GetComponent < dod::Transform >()->position.x = 1600;
	uiPlayerSkillOutLine->GetComponent < dod::Transform >()->position.y = 950;
	uiPlayerSkillOutLine->GetComponent < dod::Transform >()->scale.x = 1.5f;
	uiPlayerSkillOutLine->GetComponent < dod::Transform >()->scale.y = 1.5f;
	//스테이지 음악 생성
	soundPlayer->engineptr->soundManager->Sound_CreateBGMSound(SOUND_PATH(BGM\\BGM_Battle.wav), dod::STAGE_BGM);
}

void MainGame::Disabler()
{
	for (auto e : uiPlayerHP)
	{
		e->Disable();
	}
	for (auto e : uiPlayerHPBack)
	{
		e->Disable();
	}
	for (int i = 0; i < 5; i++)
	{
		uiPlayerInventory[i]->Disable();
		uiPlayerSkill[i]->Disable();
	}
	pframePrinter->Disable();
	keyPrinter->Disable();
	bgBox->Disable();
	uiPlayerFace->Disable();
	uiPlayerInventoryOutLine->Disable();
	uiPlayerSkillOutLine->Disable();
	uiPlayerSkillIcon->Disable();
	tester->Disable();
	boss->Disable();
	diceController->Disable();
	attackController->Disable();
	attackController->Disable();
	background->Disable();
	curtain_top->Disable();
	gameTable->Disable();
	uiController->Disable();

	enterFirst = true;

	activecheck = true;
}

void MainGame::HeartChanger()
{
	for (auto e : uiPlayerHP)
	{
		((dod::RenderSprite*)(e->GetComponent<dod::RenderComponent>()))->SetImageIndex(0);
	}

	((dod::RenderText*)(pframePrinter->GetComponent<dod::RenderComponent>()))->SetString(L"%f", _engineptr->timer.GetFps());
	if (tester->HP >= 5)
	{
		((dod::RenderSprite*)(uiPlayerHPBack[0]->GetComponent<dod::RenderComponent>()))->SetImageIndex(0);
		((dod::RenderSprite*)(uiPlayerHPBack[1]->GetComponent<dod::RenderComponent>()))->SetImageIndex(0);
		((dod::RenderSprite*)(uiPlayerHPBack[2]->GetComponent<dod::RenderComponent>()))->SetImageIndex(0);
	}

	else if (tester->HP >= 3)
	{
		((dod::RenderSprite*)(uiPlayerHPBack[0]->GetComponent<dod::RenderComponent>()))->SetImageIndex(1);
		((dod::RenderSprite*)(uiPlayerHPBack[1]->GetComponent<dod::RenderComponent>()))->SetImageIndex(0);
		((dod::RenderSprite*)(uiPlayerHPBack[2]->GetComponent<dod::RenderComponent>()))->SetImageIndex(0);
	}

	else if (tester->HP >= 1)
	{
		((dod::RenderSprite*)(uiPlayerHPBack[0]->GetComponent<dod::RenderComponent>()))->SetImageIndex(1);
		((dod::RenderSprite*)(uiPlayerHPBack[1]->GetComponent<dod::RenderComponent>()))->SetImageIndex(1);
		((dod::RenderSprite*)(uiPlayerHPBack[2]->GetComponent<dod::RenderComponent>()))->SetImageIndex(0);
	}


	else if (tester->HP <= 0)
	{
		((dod::RenderSprite*)(uiPlayerHPBack[0]->GetComponent<dod::RenderComponent>()))->SetImageIndex(1);
		((dod::RenderSprite*)(uiPlayerHPBack[1]->GetComponent<dod::RenderComponent>()))->SetImageIndex(1);
		((dod::RenderSprite*)(uiPlayerHPBack[2]->GetComponent<dod::RenderComponent>()))->SetImageIndex(1);
	}
}
