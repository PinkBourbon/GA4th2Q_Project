#pragma once
#include "GameObject.h"
#include "RenderSprite.h"
#include <map>


class Curtain_top : public dod::GameObject
{
public:
	Curtain_top();
	~Curtain_top();

public:
	virtual void OnCreate();
	virtual void OnEnable();

	virtual void OnUpdate();

	virtual void OnDisable();
	virtual void OnRelease();

private:
	dod::RenderSprite* _pSpritePrint;
	std::map<int, int> _imageResourceManagerMap;
};
