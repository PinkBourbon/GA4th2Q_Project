#pragma once
#include "BossArm.h"
#include "Transform.h"
#include "GameObject.h"
#include "RenderRect.h"

class RenderComponent;
struct dod::Transform;

class BossArmCoverage : public dod::GameObject
{
public:
	BossArmCoverage();
	~BossArmCoverage();

public:
	virtual void OnCreate();
	virtual void OnEnable();

	virtual void OnUpdate();

	virtual void OnDisable();
	virtual void OnRelease();

	void BossArmCoverageInitalation();

	dod::Transform* bossArmCoverageTransform;

private:

	dod::RenderComponent* _pArmCoverageRenderComponenet;


};

