#pragma once
#include "GameEngine.h"
#include "GameObject.h"
#include "RenderCircle.h"

class RenderComponent;
struct dod::Transform;

class StoneObject : public dod::GameObject//보스 패턴에서 사용할 돌 오브젝트, 6개를 쏠것
{
public:
	StoneObject();
	~StoneObject();

public:
	
	virtual void OnCreate() override;	// 생성될 때 호출되는 콜백 함수
	virtual void OnEnable() override;	// 활성화될 때 호출되는 콜백 함수

	virtual void OnUpdate() override;	// 매프레임 마다 호출되는 콜백 함수

	virtual void OnDisable() override;	// 비활성화 될 때 호출되는 콜백 함수
	virtual void OnRelease() override;	// 해제될 때 호출되는 콜백 함수
		
	void StoneInitalation();

	void StoneTransform(int i);

	void StoneMove();


private:
	float _speed;

	dod::RenderComponent* _stoneComponent;

	dod::Transform* _stoneTransform;
};

