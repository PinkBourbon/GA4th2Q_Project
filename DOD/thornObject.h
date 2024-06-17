#pragma once

#include "GameEngine.h"
#include "GameObject.h"
#include "RenderRect.h"
#include "Boss.h"


class GameEngine;
class Boss;
class RenderComponent;
struct dod::Transform;

class thornObject : public dod::GameObject
{
public:
	thornObject();
	~thornObject();

public:

	virtual void OnCreate() override;	// 생성될 때 호출되는 콜백 함수
	virtual void OnEnable() override;	// 활성화될 때 호출되는 콜백 함수

	virtual void OnUpdate() override;	// 매프레임 마다 호출되는 콜백 함수

	virtual void OnDisable() override;	// 비활성화 될 때 호출되는 콜백 함수
	virtual void OnRelease() override;	// 해제될 때 호출되는 콜백 함수

	void ThornCreate();

	void ThornInitalation();

	void BossParentSet(Boss* bossptr);

	void TargetEnable(dod::Transform transform);

	dod::Transform* thornTransform;

private:

	dod::RenderComponent* _thornComponent;

	Boss* _bossptr;

	

};

