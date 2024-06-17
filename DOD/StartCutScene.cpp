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
#include "MainCamera.h"
#include "DiceController.h"
#include "SceneManager.h"
#include "ImageViewer.h"
#include "StartCutScene.h"
#include "RenderSprite.h"
#include "Path.h"


StartCutScene::StartCutScene()
	:activecheck(true), _engineptr(nullptr)
	, sceneManager(nullptr),imageViewer()
{
}

StartCutScene::~StartCutScene()
{
}

void StartCutScene::CutScene()
{
	if (activecheck)
	{
		imageViewer->Enable();
		activecheck = false;
	}

	if (imageViewer->Imagenumber <= 11 && imageViewer->Imagenumber >=0)
	{
		_pCutSceneSprite->SetImageIndex(_pCutSceneSpriteMap.find(imageViewer->Imagenumber)->second);
	}

	if (imageViewer->Imagenumber > 11)
	{
		sceneManager->gameScene = SceneManager::eGameScene::IngameScene;
		imageViewer->Disable();
		sceneManager->inGame->activecheck = true;
		imageViewer->Imagenumber = 0;
	}
}

void StartCutScene::InitializeScene(dod::GameEngine* engine, SceneManager* sceneManager)
{
	_engineptr = engine;
	this->sceneManager = sceneManager;

	imageViewer = engine->RegisterGameObject<ImageViewer>(L"ImageViewer");
	//imageViewer->AddComponent(new dod::RenderRect(0, 0, 640, 360, 2));
	imageViewer->AddComponent(new dod::KeyComponent);
	imageViewer->GetComponent < dod::Transform>()->position.x = 950;
	imageViewer->GetComponent < dod::Transform>()->position.y = 520;

	_pCutSceneSprite = new dod::RenderSprite(0, 0, 4);
	_pCutSceneSpriteMap.insert({ 0,_pCutSceneSprite->PushBackImageDataVector(IMAGE_PATH(시나리오\\test\\#0.jpg)) });
	_pCutSceneSpriteMap.insert({ 1,_pCutSceneSprite->PushBackImageDataVector(IMAGE_PATH(시나리오\\test\\#1.jpg)) });
	_pCutSceneSpriteMap.insert({ 2,_pCutSceneSprite->PushBackImageDataVector(IMAGE_PATH(시나리오\\test\\#2.jpg)) });
	_pCutSceneSpriteMap.insert({ 3,_pCutSceneSprite->PushBackImageDataVector(IMAGE_PATH(시나리오\\test\\#3.jpg)) });
	_pCutSceneSpriteMap.insert({ 4,_pCutSceneSprite->PushBackImageDataVector(IMAGE_PATH(시나리오\\test\\#4.png)) });
	_pCutSceneSpriteMap.insert({ 5,_pCutSceneSprite->PushBackImageDataVector(IMAGE_PATH(시나리오\\test\\#5.png)) });
	_pCutSceneSpriteMap.insert({ 6,_pCutSceneSprite->PushBackImageDataVector(IMAGE_PATH(시나리오\\test\\#6.png)) });
	_pCutSceneSpriteMap.insert({ 7,_pCutSceneSprite->PushBackImageDataVector(IMAGE_PATH(시나리오\\test\\#7.png)) });
	_pCutSceneSpriteMap.insert({ 8,_pCutSceneSprite->PushBackImageDataVector(IMAGE_PATH(시나리오\\test\\#8.png)) });
	_pCutSceneSpriteMap.insert({ 9,_pCutSceneSprite->PushBackImageDataVector(IMAGE_PATH(시나리오\\test\\#9.png)) });
	_pCutSceneSpriteMap.insert({ 10,_pCutSceneSprite->PushBackImageDataVector(IMAGE_PATH(시나리오\\test\\#10.png)) });
	_pCutSceneSpriteMap.insert({ 11,_pCutSceneSprite->PushBackImageDataVector(IMAGE_PATH(시나리오\\test\\#11.png)) });
	imageViewer->AddComponent(_pCutSceneSprite);
}
