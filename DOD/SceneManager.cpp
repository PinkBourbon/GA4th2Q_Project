#include "Macro.h"
#include "GameEngine.h"
#include "MainGame.h"
#include "SceneManager.h"
#include "TitleScene.h"
#include "GameEmblem.h"
#include "StartCutScene.h"
#include "EndingCutScene.h"
#include "Credit.h"

#pragma comment (lib,"DODengine.lib")
#pragma comment (lib, "DODutil.lib")
#pragma comment (lib, "fmod_vc.lib")

SceneManager::SceneManager()
	: title(nullptr), inGame(nullptr)
	, gameEmblem(nullptr), startCutScene(nullptr)
	, gameScene(eGameScene::Gameemblem)
{

}

SceneManager::~SceneManager()
{

}

void SceneManager::InitializeSceneManager(dod::GameEngine* engine)
{
	inGame = new MainGame();
	title = new TitleScene();
	gameEmblem = new GameEmblem();
	startCutScene = new StartCutScene();
	ending = new EndingCutScene();
	credit = new Credit();
	inGame->InitializeScene(engine, this);
	title->InitializeTitle(engine, this);
	gameEmblem->InitializeScene(engine, this);
	startCutScene->InitializeScene(engine, this);
	ending->InitializeScene(engine, this);
	credit->InitializeScene(engine, this);
}

void SceneManager::SeceneManagement()
{
	switch (gameScene)
	{
		case SceneManager::eGameScene::Gameemblem:
			gameEmblem->Emblemview();
			break;
		case SceneManager::eGameScene::Title:
			title->TitleMain();
			break;
		case SceneManager::eGameScene::StartCutscene:
			startCutScene->CutScene();
			break;
		case SceneManager::eGameScene::IngameScene:
			inGame->GameScene();
			break;
		case SceneManager::eGameScene::EndCutscene:
			ending->CutScene();
			break;
		case SceneManager::eGameScene::CreditScene:
			credit->CutScene();
			break;
		default:
			Assert(false, "존재하지 않는 게임 씬에 접근하였습니다.");
			break;
	}
}
