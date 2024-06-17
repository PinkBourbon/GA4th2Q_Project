#include "GameEngine.h"
#include "GameObject.h"
#include "RenderComponent.h"
#include "RenderRect.h"
#include "Transform.h"
#include "SceneManager.h"
#include "GameEmblem.h"
#include "TitleScene.h"
#include "RenderSprite.h"
#include "Path.h"

GameEmblem::GameEmblem()
	: _Blanker(nullptr), _emblemObejct(nullptr), _engineptr(nullptr)
	, sceneManager(nullptr), timer(0)
	, _pBlackBaox(nullptr), _plogo(nullptr)
{
}

GameEmblem::~GameEmblem()
{

}

void GameEmblem::Emblemview()
{
	timer += _Blanker->engineptr->timer.GetDeltaTime();

	if (_Blanker->objState == dod::eObjectState::OnDisable)
	{
		_Blanker->Enable();
	}

	if (_emblemObejct->objState == dod::eObjectState::OnDisable)
	{
		_emblemObejct->Enable();
		_pBossBreath->Enable();
		_pBoss->Enable();
		_pArmL->Enable();
		_pArmR->Enable();
	}

	if (timer < 2)
	{
		int key = static_cast<int>((timer) * 10);
		if (key < 1)
		{
			key = 1;
		}
		_pBlackBaox->SetImageIndex(_blackBoxResourceMap.find(key)->second);
	}
	else if (timer < 6)
	{
		static int i = 0;
		_Blanker->Disable();
		_pBossBreathSprite->SetImageIndex(1);
		//이미지 3초간 출력
		_pBossSprite->SetImageIndex(i);
		_pArmLSprite->SetImageIndex(i);
		_pArmRSprite->SetImageIndex(i);
		if (i < 4)
		{
			i++;
		}
		else
		{
			i = 0;
		}
	}
	else
	{
		//_emblemObejct->engineptr->soundManager->Sound_SoundPause(dod::MAINLOBBY_BGM);
		timer = 0;
		_emblemObejct->Disable();
		_Blanker->Disable();
		_pBossBreath->Disable();
		_pBoss->Disable();
		_pArmL->Disable();
		_pArmR->Disable();
		sceneManager->gameScene = SceneManager::eGameScene::Title;
		sceneManager->title->activecheck = true;
	}
}

void GameEmblem::InitializeScene(dod::GameEngine* engine, SceneManager* sceneManager)
{
	_engineptr = engine;
	this->sceneManager = sceneManager;

	_emblemObejct = engine->RegisterGameObject<dod::GameObject>(L"Emblem");
	//_emblemObejct->AddComponent(new dod::RenderRect(420, 260, 820, 460, 1));

	_Blanker = engine->RegisterGameObject<dod::GameObject>(L"Blanker");
	//_Blanker->AddComponent(new dod::RenderRect(0, 0, 1240, 720, 1));

	_pBlackBaox = new dod::RenderSprite(960, 380, 4);
	_blackBoxResourceMap.insert({ 1,_pBlackBaox->PushBackImageDataVector(IMAGE_PATH(Reference\\Alpha\\#1.png)) });
	_blackBoxResourceMap.insert({ 2,_pBlackBaox->PushBackImageDataVector(IMAGE_PATH(Reference\\Alpha\\#2.png)) });
	_blackBoxResourceMap.insert({ 3,_pBlackBaox->PushBackImageDataVector(IMAGE_PATH(Reference\\Alpha\\#3.png)) });
	_blackBoxResourceMap.insert({ 4,_pBlackBaox->PushBackImageDataVector(IMAGE_PATH(Reference\\Alpha\\#4.png)) });
	_blackBoxResourceMap.insert({ 5,_pBlackBaox->PushBackImageDataVector(IMAGE_PATH(Reference\\Alpha\\#5.png)) });
	_blackBoxResourceMap.insert({ 6,_pBlackBaox->PushBackImageDataVector(IMAGE_PATH(Reference\\Alpha\\#6.png)) });
	_blackBoxResourceMap.insert({ 7,_pBlackBaox->PushBackImageDataVector(IMAGE_PATH(Reference\\Alpha\\#7.png)) });
	_blackBoxResourceMap.insert({ 8,_pBlackBaox->PushBackImageDataVector(IMAGE_PATH(Reference\\Alpha\\#8.png)) });
	_blackBoxResourceMap.insert({ 9,_pBlackBaox->PushBackImageDataVector(IMAGE_PATH(Reference\\Alpha\\#9.png)) });
	_blackBoxResourceMap.insert({ 10,_pBlackBaox->PushBackImageDataVector(IMAGE_PATH(Reference\\Alpha\\#10.png)) });
	_blackBoxResourceMap.insert({ 11,_pBlackBaox->PushBackImageDataVector(IMAGE_PATH(Reference\\Alpha\\#11.png)) });
	_blackBoxResourceMap.insert({ 12,_pBlackBaox->PushBackImageDataVector(IMAGE_PATH(Reference\\Alpha\\#12.png)) });
	_blackBoxResourceMap.insert({ 13,_pBlackBaox->PushBackImageDataVector(IMAGE_PATH(Reference\\Alpha\\#13.png)) });
	_blackBoxResourceMap.insert({ 14,_pBlackBaox->PushBackImageDataVector(IMAGE_PATH(Reference\\Alpha\\#14.png)) });
	_blackBoxResourceMap.insert({ 15,_pBlackBaox->PushBackImageDataVector(IMAGE_PATH(Reference\\Alpha\\#15.png)) });
	_blackBoxResourceMap.insert({ 16,_pBlackBaox->PushBackImageDataVector(IMAGE_PATH(Reference\\Alpha\\#16.png)) });
	_blackBoxResourceMap.insert({ 17,_pBlackBaox->PushBackImageDataVector(IMAGE_PATH(Reference\\Alpha\\#17.png)) });
	_blackBoxResourceMap.insert({ 18,_pBlackBaox->PushBackImageDataVector(IMAGE_PATH(Reference\\Alpha\\#18.png)) });
	_blackBoxResourceMap.insert({ 19,_pBlackBaox->PushBackImageDataVector(IMAGE_PATH(Reference\\Alpha\\#19.png)) });
	_blackBoxResourceMap.insert({ 20,_pBlackBaox->PushBackImageDataVector(IMAGE_PATH(Reference\\Alpha\\#20.png)) });
	_blackBoxResourceMap.insert({ 21,_pBlackBaox->PushBackImageDataVector(IMAGE_PATH(Reference\\Alpha\\#21.png)) });
	_Blanker->AddComponent(_pBlackBaox);

	_plogo = new dod::RenderSprite(940, 380, 3);
	_plogo->PushBackImageDataVector(IMAGE_PATH(UI\\LogoUI.png));
	_emblemObejct->AddComponent(_plogo);


	// 스프라이트 미리 출력용
	_pBossBreath = _engineptr->RegisterGameObject<dod::GameObject>(L"ForwardBossBreath");
	_pBossBreath->GetComponent<dod::Transform>()->scale.x = 1.f;
	_pBossBreath->GetComponent<dod::Transform>()->scale.y = 1.f;
	_pBossBreath->GetComponent<dod::Transform>()->position.x = -3000;
	_pBossBreath->GetComponent<dod::Transform>()->position.y = -3000;
	_pBossBreathSprite = new dod::RenderSprite(0, 0, 0);
	_bossBreathSpriteMap.insert({ 0,_pBossBreathSprite->PushBackImageDataVector(IMAGE_PATH(Effect\\Smoke\\Sheet\\Breathe_Sheet.png)) });
	_bossBreathSpriteMap.insert({ 1,_pBossBreathSprite->PushBackImageDataVector(IMAGE_PATH(Effect\\Smoke\\Sheet\\Smoke_Sheet.png)) });
	_pBossBreath->AddComponent(_pBossBreathSprite);

	_pBoss = _engineptr->RegisterGameObject<dod::GameObject>(L"ForwardBossBreath");
	_pBoss->GetComponent<dod::Transform>()->SetParent(_pBossBreath->GetComponent<dod::Transform>());
	_pBossSprite = new dod::RenderSprite(0, 0, 0);
	_bossSpriteMap.insert({ 0,_pBossSprite->PushBackImageDataVector(IMAGE_PATH(Sprite\\Boss\\Sheet\\Boss_Base_Idle_Sheet.png)) });
	_bossSpriteMap.insert({ 1,_pBossSprite->PushBackImageDataVector(IMAGE_PATH(Sprite\\Boss\\Sheet\\Boss_Base_Breathe_Sheet.png)) });
	_bossSpriteMap.insert({ 2,_pBossSprite->PushBackImageDataVector(IMAGE_PATH(Sprite\\Boss\\Sheet\\Boss_Base_AttackR_Sheet.png)) });
	_bossSpriteMap.insert({ 3,_pBossSprite->PushBackImageDataVector(IMAGE_PATH(Sprite\\Boss\\Sheet\\Boss_Base_AttackL_Sheet.png)) });
	_bossSpriteMap.insert({ 4,_pBossSprite->PushBackImageDataVector(IMAGE_PATH(Sprite\\Boss\\Sheet\\Boss_Base_Attack_Sheet.png)) });
	_pBoss->AddComponent(_pBossSprite);

	_pArmL = _engineptr->RegisterGameObject<dod::GameObject>(L"ForwardBossBreath");
	_pArmL->GetComponent<dod::Transform>()->SetParent(_pBossBreath->GetComponent<dod::Transform>());
	_pArmLSprite = new dod::RenderSprite(0, 0, 0);
	_bossArmLMap.insert({ 0,_pArmLSprite->PushBackImageDataVector(IMAGE_PATH(Sprite\\Boss\\Sheet\\Boss_ArmL_Idle_Sheet.png)) });
	_bossArmLMap.insert({ 1,_pArmLSprite->PushBackImageDataVector(IMAGE_PATH(Sprite\\Boss\\Sheet\\Boss_ArmL_Breathe_Sheet.png)) });
	_bossArmLMap.insert({ 2,_pArmLSprite->PushBackImageDataVector(IMAGE_PATH(Sprite\\Boss\\Sheet\\Boss_ArmL_AttackR_Sheet.png)) });
	_bossArmLMap.insert({ 3,_pArmLSprite->PushBackImageDataVector(IMAGE_PATH(Sprite\\Boss\\Sheet\\Boss_ArmL_AttackL_Sheet.png)) });
	_bossArmLMap.insert({ 4,_pArmLSprite->PushBackImageDataVector(IMAGE_PATH(Sprite\\Boss\\Sheet\\Boss_ArmL_Attack_Sheet.png)) });
	_pArmL->AddComponent(_pArmLSprite);

	_pArmR = _engineptr->RegisterGameObject<dod::GameObject>(L"ForwardBossBreath");
	_pArmR->GetComponent<dod::Transform>()->SetParent(_pBossBreath->GetComponent<dod::Transform>());
	_pArmRSprite = new dod::RenderSprite(0, 0, 0);
	_bossArmRMap.insert({ 0,_pArmRSprite->PushBackImageDataVector(IMAGE_PATH(Sprite\\Boss\\Sheet\\Boss_ArmR_Idle_Sheet.png)) });
	_bossArmRMap.insert({ 1,_pArmRSprite->PushBackImageDataVector(IMAGE_PATH(Sprite\\Boss\\Sheet\\Boss_ArmR_Breathe_Sheet.png)) });
	_bossArmRMap.insert({ 2,_pArmRSprite->PushBackImageDataVector(IMAGE_PATH(Sprite\\Boss\\Sheet\\Boss_ArmR_AttackR_Sheet.png)) });
	_bossArmRMap.insert({ 3,_pArmRSprite->PushBackImageDataVector(IMAGE_PATH(Sprite\\Boss\\Sheet\\Boss_ArmR_AttackL_Sheet.png)) });
	_bossArmRMap.insert({ 4,_pArmRSprite->PushBackImageDataVector(IMAGE_PATH(Sprite\\Boss\\Sheet\\Boss_ArmR_Attack_Sheet.png)) });
	_pArmR->AddComponent(_pArmRSprite);
}

void GameEmblem::Disabler()
{

}
