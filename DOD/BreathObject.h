#pragma once
#include "GameEngine.h"
#include "GameObject.h"
#include "RenderCircle.h"
#include "Boss.h"
#include "SmokeObject.h"

class RenderComponent;
struct dod::Transform;


class BreathObject : public dod::GameObject
{
public:
	BreathObject();
	~BreathObject();

public:

	virtual void OnCreate() override;	// 생성될 때 호출되는 콜백 함수
	virtual void OnEnable() override;	// 활성화될 때 호출되는 콜백 함수

	virtual void OnUpdate() override;	// 매프레임 마다 호출되는 콜백 함수

	virtual void OnDisable() override;	// 비활성화 될 때 호출되는 콜백 함수
	virtual void OnRelease() override;	// 해제될 때 호출되는 콜백 함수

	void BreathInitalation();

	void BreathTransform();

	void BossParentSet(Boss* bossptr);


	dod::Transform* breathTransform;

private:
	dod::RenderComponent* _breathComponent;
	Boss* _bossptr;

	SmokeObject* _smokeObject;
	double _timer;
	const double _disableTimer;
	const double _startSmokeTimer;
	bool _isStartSmoke;
};

