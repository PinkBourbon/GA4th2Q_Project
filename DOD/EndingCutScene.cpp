#include "EndingCutScene.h"
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
#include "TitleScene.h"
#include "MainCamera.h"
#include "DiceController.h"
#include "SceneManager.h"
#include "ImageViewer.h"
#include "StartCutScene.h"
#include "RenderSprite.h"
#include "Path.h"


EndingCutScene::EndingCutScene()
	:activecheck(true), _engineptr(nullptr)
	, sceneManager(nullptr), imageViewer(), _pCutSceneSprite(nullptr)
{
}

EndingCutScene::~EndingCutScene()
{
}

void EndingCutScene::CutScene()
{
	
	if (activecheck)
	{
		imageViewer->Enable();
		activecheck = false;
	}



	if (imageViewer->Imagenumber > 0)
	{
		sceneManager->gameScene = SceneManager::eGameScene::Title;
		sceneManager->title->activecheck = true;
		imageViewer->Disable();
		imageViewer->Imagenumber = 0;
		_engineptr->soundManager->Sound_SoundPause(dod::ENDING_BGM);		
	}
}

void EndingCutScene::InitializeScene(dod::GameEngine* engine, SceneManager* sceneManager)
{
	_engineptr = engine;
	this->sceneManager = sceneManager;

	imageViewer = engine->RegisterGameObject<ImageViewer>(L"ImageViewer2");
	_pCutSceneSprite = new dod::RenderSprite(0, 0, 6);
	_pCutSceneSprite->PushBackImageDataVector(IMAGE_PATH(Illust\\¿£µùÄÆ½Å.png));
	imageViewer->AddComponent(_pCutSceneSprite);
	imageViewer->AddComponent(new dod::KeyComponent);
	imageViewer->GetComponent < dod::Transform>()->position.x = 950;
	imageViewer->GetComponent < dod::Transform>()->position.y = 520;

	//_pCutSceneSprite = new dod::RenderSprite(0, 0, 4);

}