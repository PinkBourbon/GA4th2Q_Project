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

	virtual void OnCreate() override;	// ������ �� ȣ��Ǵ� �ݹ� �Լ�
	virtual void OnEnable() override;	// Ȱ��ȭ�� �� ȣ��Ǵ� �ݹ� �Լ�

	virtual void OnUpdate() override;	// �������� ���� ȣ��Ǵ� �ݹ� �Լ�

	virtual void OnDisable() override;	// ��Ȱ��ȭ �� �� ȣ��Ǵ� �ݹ� �Լ�
	virtual void OnRelease() override;	// ������ �� ȣ��Ǵ� �ݹ� �Լ�

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

