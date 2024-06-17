#pragma once

namespace dod
{
	class GameObject;
	class GameEngine;
};

class MainGame;
class TitleScene;
class GameEmblem;
class StartCutScene;
class EndingCutScene;
class Credit;

class SceneManager
{
public:
	SceneManager();
	~SceneManager();

public:
	enum class eGameScene
	{
		Gameemblem,
		Title,
		StartCutscene,
		IngameScene,
		EndCutscene,
		CreditScene
	};

	void InitializeSceneManager(dod::GameEngine* engine);
	void SeceneManagement();
	void Disabler();
public:
	eGameScene gameScene;
	TitleScene* title;
	GameEmblem* gameEmblem;
	MainGame* inGame;
	StartCutScene* startCutScene;
	EndingCutScene* ending;
	Credit* credit;
};

