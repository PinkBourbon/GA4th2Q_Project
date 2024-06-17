#pragma once
#include "GameObject.h"
#include "BossState.h"
#include "RenderRect.h"
#include "BossArm.h"
#include "StoneObject.h"
#include "thornObject.h"
#include "BreathObject.h"
#include "Rectangle.h"

namespace dod
{
	class RenderSprite;
}

class TestPlayer;
class GameEngine;
class dod::Rectangle;
struct dod::Transform;

class Boss : public dod::GameObject
{
	friend class BossArm;
	friend class BossArmR;
	friend class thornObject;
	friend class BreathObject;
public:

	Boss();
	~Boss();
public:
	virtual void OnCreate();
	virtual void OnEnable();

	virtual void OnUpdate();

	virtual void OnDisable();
	virtual void OnRelease();


	void BossState();
	void BossStart();
	void BossNormalAttack();
	void BossAttack_Sunken();
	void BossAttack_Stone();
	void BossAttack_Swing(int _swingAttackNumber);
	void BossAttack_Breath();
	void BossIdle();
	void BossDead();
	void AdjustHP(int damage);
	int hP;
	int maxHp;

private:
	float basicScale;

	dod::eBossState _eState;

	BossArm* _bossArmL;
	BossArm* _bossArmR;

	BossArm* _bossArmLWarningObject;
	BossArm* _bossArmRWarningObject;

	double _deltanum;

	int _attackNumber;
	int _swingAttackNumber;

	StoneObject* _stoneObject[6];

	dod::Transform* _bossTransform;

	thornObject* _thornObject;
	thornObject* _thornWarningObject;

	TestPlayer* _testPlayerptr;

	BreathObject* _breathObject;
	int _breathCount;

	GameObject* _pHPPrinter;
	GameObject* _pBossIcon;
	GameObject* _pHPBar;
	GameObject* _pHPBarOutline;

	dod::RenderSprite* _pBossBreathSprite;
	std::map<int, int> _bossBreathSpriteMap;

	dod::RenderSprite* _pBossSprite;
	std::map<dod::eBossPattern, int> _bossSpriteMap;

	dod::RenderSprite* _pArmLSprite;
	std::map<dod::eBossPattern, int> _bossArmLMap;

	dod::RenderSprite* _pArmRSprite;
	std::map<dod::eBossPattern, int> _bossArmRMap;

	double realTime;

	bool _isInitAttackSwing;
};

