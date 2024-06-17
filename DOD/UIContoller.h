#pragma once
#include "GameObject.h"

#define DICE_CAPCITY 6

namespace dod
{
	class  RenderSprite;
};

class GameEngine;
class Inventory;
class TestPlayer;
class Curtain_side;
class SkillDice;

class UIController : public dod::GameObject
{
public:
	UIController();
	~UIController();

public:
	virtual void OnCreate();
	virtual void OnEnable();

	virtual void OnUpdate();

	virtual void OnDisable();
	virtual void OnRelease();

	void ReRollSkill();
	void SetReRollState(bool rollstate);
	int GetSkillDiceNumber(int index);

private:
	Inventory* _inventory[DICE_CAPCITY];

	dod::GameObject* uiPlayerSkillLever;
	std::map<int, int> _UIPlayerSkillLeverSpriteMap;

	dod::RenderSprite* _pSpritePrint;

	SkillDice* _skillDice[5];
	TestPlayer* _player;
	Curtain_side* _curtain[2];
	int _diceCount;
	bool _isCurtainMove;
	bool _isReRoll;

	bool _Leveractioned;
};
