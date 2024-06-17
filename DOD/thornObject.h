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

	virtual void OnCreate() override;	// ������ �� ȣ��Ǵ� �ݹ� �Լ�
	virtual void OnEnable() override;	// Ȱ��ȭ�� �� ȣ��Ǵ� �ݹ� �Լ�

	virtual void OnUpdate() override;	// �������� ���� ȣ��Ǵ� �ݹ� �Լ�

	virtual void OnDisable() override;	// ��Ȱ��ȭ �� �� ȣ��Ǵ� �ݹ� �Լ�
	virtual void OnRelease() override;	// ������ �� ȣ��Ǵ� �ݹ� �Լ�

	void ThornCreate();

	void ThornInitalation();

	void BossParentSet(Boss* bossptr);

	void TargetEnable(dod::Transform transform);

	dod::Transform* thornTransform;

private:

	dod::RenderComponent* _thornComponent;

	Boss* _bossptr;

	

};

