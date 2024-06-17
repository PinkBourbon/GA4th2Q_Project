#pragma once
#include "GameObject.h"

class GameEngine;
class TestDice;
class UIController;
class TestPlayer;

class DiceController : public dod::GameObject
{
	friend class UIController;
public:
	DiceController();
	~DiceController();

public:
	virtual void OnCreate();
	virtual void OnEnable();
							
	virtual void OnUpdate();
							
	virtual void OnDisable();
	virtual void OnRelease();

private:
	TestDice* _dicePool[11];
	UIController* _uiController;
	TestPlayer* _player;
	bool _rerollBySkill;
};

