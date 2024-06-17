#pragma once

namespace dod
{
	class GameEngine;
	class RenderSprite;
	class GameObject;
};

class SceneManager;
class TitleScene;
class CreditPrinter;

class Credit
{
public:
	Credit();
	~Credit();
public:
	void CutScene();
	void InitializeScene(dod::GameEngine* engine, SceneManager* sceneManager);
	void Disabler();

	bool activecheck;
private:

	SceneManager* sceneManager;
	dod::GameEngine* _engineptr;
	
	CreditPrinter* _pImagePrinter;
	dod::RenderSprite* _pCreditRenderSprite;
};

