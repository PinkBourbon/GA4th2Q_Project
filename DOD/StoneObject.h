#pragma once
#include "GameEngine.h"
#include "GameObject.h"
#include "RenderCircle.h"

class RenderComponent;
struct dod::Transform;

class StoneObject : public dod::GameObject//���� ���Ͽ��� ����� �� ������Ʈ, 6���� ���
{
public:
	StoneObject();
	~StoneObject();

public:
	
	virtual void OnCreate() override;	// ������ �� ȣ��Ǵ� �ݹ� �Լ�
	virtual void OnEnable() override;	// Ȱ��ȭ�� �� ȣ��Ǵ� �ݹ� �Լ�

	virtual void OnUpdate() override;	// �������� ���� ȣ��Ǵ� �ݹ� �Լ�

	virtual void OnDisable() override;	// ��Ȱ��ȭ �� �� ȣ��Ǵ� �ݹ� �Լ�
	virtual void OnRelease() override;	// ������ �� ȣ��Ǵ� �ݹ� �Լ�
		
	void StoneInitalation();

	void StoneTransform(int i);

	void StoneMove();


private:
	float _speed;

	dod::RenderComponent* _stoneComponent;

	dod::Transform* _stoneTransform;
};

