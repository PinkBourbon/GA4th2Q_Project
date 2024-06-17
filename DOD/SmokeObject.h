#pragma once
#include "GameObject.h"

class SmokeObject : public dod::GameObject
{
public:
	SmokeObject();
	~SmokeObject();

public:

	virtual void OnCreate() override;	// 생성될 때 호출되는 콜백 함수
	virtual void OnEnable() override;	// 활성화될 때 호출되는 콜백 함수

	virtual void OnUpdate() override;	// 매프레임 마다 호출되는 콜백 함수

	virtual void OnDisable() override;	// 비활성화 될 때 호출되는 콜백 함수
	virtual void OnRelease() override;	// 해제될 때 호출되는 콜백 함수

private:
	double _timer;
	const double _disableTimer;
};

