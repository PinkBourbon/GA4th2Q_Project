#pragma once

namespace dod
{
	class GameObject;
	class GameEngine;
	class RenderLine;
	class RenderSprite;
};

class TestAttack;
class Boss;
class DiceController;
class TestAttack;
class TestPlayer;
class SceneManager;

class TitleScene
{
public:
	TitleScene();
	~TitleScene();
public:
	void TitleMain();
	void InitializeTitle(dod::GameEngine* engine, SceneManager* sceneManager);
	void Disabler();

	bool activecheck;
private:

	SceneManager* sceneManager;

	dod::GameEngine* _engineptr;
	dod::GameObject* pframePrinter;
	dod::GameObject* keyPrinter;
	dod::GameObject* playbox2[6];
	dod::GameObject* uiBox;
	dod::GameObject* bgBox;
	dod::GameObject* CreditBox;
	dod::GameObject* _pBackground;
	dod::GameObject* _pLogoIcon;
	//dod::GameObject* _pBackground;

	TestPlayer* tester;
	dod::GameObject* soundPlayer;


};

