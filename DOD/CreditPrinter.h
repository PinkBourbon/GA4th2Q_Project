#pragma once
#include "GameObject.h"

class SceneManager;

class CreditPrinter : public dod::GameObject
{
public:
	CreditPrinter();
	~CreditPrinter();
public:
	virtual void OnCreate();
	virtual void OnEnable();

	virtual void OnUpdate();

	virtual void OnDisable();
	virtual void OnRelease();

	SceneManager* sceneManager;
};

