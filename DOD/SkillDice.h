#pragma once
#include "GameObject.h"

class TestPlayer;

namespace dod
{
	class RenderSprite;
}

class SkillDice : public dod::GameObject
{
	friend class UIController;

public:
	SkillDice();
	~SkillDice();

public:
	virtual void OnCreate();
	virtual void OnEnable();

	virtual void OnUpdate();

	virtual void OnDisable();
	virtual void OnRelease();

	void MatchNumberImage();
	void MatchNumberImage(int num);

private:
	int stateNumber;	// 0~6�� ����. ���� �̹����� 0, 1~6�� �ֻ��� ����. 7�̸� ���ư��� ����
	dod::RenderSprite* _pSpritePrint;
	TestPlayer* _player;
	std::map<int, int> _imageResourceManagerMap;
};
