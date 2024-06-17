#pragma once
#include "GameObject.h"

class TestPlayer;

namespace dod
{
	class RenderSprite;
}

class TestDice : public dod::GameObject
{
public:
	TestDice();
	~TestDice();
public:
	virtual void OnCreate();
	virtual void OnEnable();

	virtual void OnUpdate();

	virtual void OnDisable();
	virtual void OnRelease();

	int GetDiceNumber();

	void Disabler();

private:
	GameObject* _namePrinter;
	TestPlayer* _player;
	int _diceNumber;

	dod::RenderSprite* _pSpritePrint;
	std::map<int, int> _imageResourceManagerMap;
};

