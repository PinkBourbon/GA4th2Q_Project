#pragma once
#include "GameObject.h"

class TestPlayer;

namespace dod
{
	class RenderSprite;
}

class Inventory : public dod::GameObject
{
	friend class UIController;

public:
	Inventory();
	~Inventory();

public:
	virtual void OnCreate();
	virtual void OnEnable();

	virtual void OnUpdate();

	virtual void OnDisable();
	virtual void OnRelease();

private:
	int stateNumber;	// 0~6�� ����. ��������� 0, 1~6�� �ֻ��� ����.
	dod::RenderSprite* _pSpritePrint;
	TestPlayer* _player;
	std::map<int, int> _imageResourceManagerMap;
};
