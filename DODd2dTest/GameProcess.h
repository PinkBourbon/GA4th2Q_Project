#pragma once
#include <vector>
#include <map>
#include <windows.h>

#include "RenderComponent.h"
#include "RenderCircle.h"
#include "RenderSprite.h"
#include "RenderText.h"
#include "RenderRect.h"
#include "Transform.h"
#include "KeyManager.h"



namespace dod
{
	class Id2d;
	class SpriteGI;
	class GameObject;
	class GameEngine;
}

class MainCamera;

enum class eImageList
{
	STARTBACKGROUND,
	MAINBACKGROUND,
	PLAYERMAIN,
	PLAYERWALK,
	PLAYERJUMP,
	PLAYERHIT,
	PLAYERDIE,
	PLAYERATTACK,
	PLAYERROLLING,
	DICE1,
	DICE2,
	DICE3,
	DICE4,
	DICE5,
	DICE6,
	DICEROLLING
};

class GameProcess
{
public:
	GameProcess();
	~GameProcess();


	HRESULT Initialize();

	void Loop();

	void Finalize();

	static LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);


private:
	std::map<eImageList, int> _imageResourceManagerMap;

	dod::RenderCircle* _circleComponent1 = 0;
	dod::RenderSprite* _backGround = 0;
	dod::RenderSprite* _player = 0;
	dod::RenderSprite* _dice = 0;
	dod::RenderComponent* _rectComponenet = 0;

	dod::RenderText* _ameText = 0;

	dod::KeyManager* _keyManager = 0;
	dod::KeyComponent* _keyComponenet = 0;

	const int _screenWidth = 1600;
	const int _screenHeight = 1200;
	int _ame = 0;

	HWND _hWnd;
	MSG _MSG;

	//dod::Id2d* _giEngine;
	dod::GameEngine* _gameEngine;

	// 스프라이트풀
	std::vector<dod::SpriteGI*> _spritePool;

	// 애니메이션 관리

	dod::GameObject* _obj;
	dod::GameObject* _obj1;
	dod::GameObject* _obj2;
	dod::GameObject* _obj3;
	dod::GameObject* _obj4;
	dod::GameObject* _obj5;

	MainCamera* _camera;

	// 트랜스폼
	dod::Transform _cameraTR;
	dod::Transform _playerTR;
	dod::Transform _playerTR2;
	dod::Transform _allTR;
};


