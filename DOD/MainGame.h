#pragma once
#include <map>

namespace dod
{
	class GameObject;
	class GameEngine;
	class RenderSprite;
};

class TestAttack;
class Boss;
class DiceController;
class UIController;
class AttackController;
class TestPlayer;
class SceneManager;
class MainCamera;
class Background;
class Curtain_top;
class GameTable;
class EndingCutScene;

class MainGame
{
public:
	MainGame();
	~MainGame();

public:
	void GameScene();
	void InitializeScene(dod::GameEngine* engine, SceneManager* sceneManager);
	void Disabler();
	void HeartChanger();

	bool activecheck;
	bool isSoundPlayStage;

	bool enterFirst;
private:

	SceneManager* sceneManager;
	dod::GameEngine* _engineptr;

	MainCamera* _mainCamera;

	dod::GameObject* pframePrinter;
	dod::GameObject* keyPrinter;
	dod::GameObject* uiPlayerFace;
	dod::GameObject* uiPlayerHP[3];
	dod::GameObject* uiPlayerHPBack[3];
	dod::GameObject* uiPlayerInventory[5];
	dod::GameObject* uiPlayerInventoryOutLine;
	dod::GameObject* uiPlayerSkillOutLine;
	dod::GameObject* uiPlayerSkillIcon;
	dod::GameObject* uiPlayerSkill[5];

	dod::GameObject* bgBox;
	TestPlayer* tester;
	Boss* boss;
	Background* background;
	Curtain_top* curtain_top;
	GameTable* gameTable;
	UIController* uiController;
	DiceController* diceController;
	AttackController* attackController;
	dod::GameObject* soundPlayer;

	//dod::RenderSprite* _pUIPlayerHPSprite;
	std::map<int, int> _uiPlayerHPSpriteMap;
};

