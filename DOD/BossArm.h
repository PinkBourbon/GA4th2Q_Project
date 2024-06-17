#pragma once
#include "GameObject.h"
#include "GameEngine.h"
#include "BossState.h"
#include "RenderRect.h"
#include "RenderComponent.h"
#include "Transform.h"
#include "StoneObject.h"
#include "Boss.h"
#include "BossArmCoverage.h"
#include "Rectangle.h"

class GameEngine;
class RenderComponent;
class Boss;
class BossArmCoverage;

namespace dod
{
	class RenderSprite;
}

struct dod::Transform;

class BossArm : public dod::GameObject
{
public:
	BossArm();
	~BossArm();
public:
	virtual void OnCreate();
	virtual void OnEnable();

	virtual void OnUpdate();

	virtual void OnDisable();
	virtual void OnRelease();

	void BossParentSet(Boss* bossptr);

	void BossInitalation();

	void BossArmIdle();

	void BossSwingAttackL();

	void BossSwingAttackR();

	dod::eBossPattern ReturnBossPattern();

	dod::Transform* bossArmTransform;

private:

	int attackspeed;

	dod::eBossState _eState;

	double _deltanum;

	double _bossArmDeltaTime;

	StoneObject* _stoneObject;

	dod::RenderComponent* _pArmLRenderComponenet;
	// 	dod::RenderSprite* _pArmLSprite;
	// 	std::map<eBossArmLPattern, int> _bossArmLMap;

	Boss* _bossptr;

	BossArmCoverage* _bossArmCoverage;

	dod::eBossPattern _bossPattern;

	dod::Rectangle* _physicsRectArm;
};


