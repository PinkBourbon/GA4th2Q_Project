#pragma once
#include "GameObject.h"

class SmokeObject : public dod::GameObject
{
public:
	SmokeObject();
	~SmokeObject();

public:

	virtual void OnCreate() override;	// ������ �� ȣ��Ǵ� �ݹ� �Լ�
	virtual void OnEnable() override;	// Ȱ��ȭ�� �� ȣ��Ǵ� �ݹ� �Լ�

	virtual void OnUpdate() override;	// �������� ���� ȣ��Ǵ� �ݹ� �Լ�

	virtual void OnDisable() override;	// ��Ȱ��ȭ �� �� ȣ��Ǵ� �ݹ� �Լ�
	virtual void OnRelease() override;	// ������ �� ȣ��Ǵ� �ݹ� �Լ�

private:
	double _timer;
	const double _disableTimer;
};

