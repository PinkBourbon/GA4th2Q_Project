#pragma once
#include "GameObject.h"
#include "Vector3.h"


class TestPlayer;
class Boss;
class UIController;

namespace dod
{
	class RenderSprite;
}

enum eAttackType
{
	AutoAttack,
	SkillAttack3,
	SkillAttack4,
	SkillAttack5,
	None
};


class TestAttack : public dod::GameObject
{
	friend class AttackController;

public:
	TestAttack();
	~TestAttack();
public:
	virtual void OnCreate();
	virtual void OnEnable();

	virtual void OnUpdate();

	virtual void OnDisable();
	virtual void OnRelease();

	void EnableSkill(eAttackType attackType);
	void EnableAttack();

	int GetDiceNumber();

	void Disabler();
	void ShootAttack();
	void ShootSkill();
	void Reset();

private:
	GameObject* _namePrinter;
	TestPlayer* _player;
	Boss* _boss;
	UIController* _uiController;
	int _diceNumber;
	//Vector3 _direction;
	float _directionX;
	float _directionY;
	float _speed;
	bool _isShooting;
	bool _isAttackSound;
	int _damage;
	eAttackType _attackType;

	dod::RenderSprite* _pSpritePrint;
	std::map<int, int> _imageResourceManagerMap;
};
