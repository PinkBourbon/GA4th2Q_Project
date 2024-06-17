#pragma once
#include "GameObject.h"

namespace dod
{
	struct KeyComponent;
	class GameEngine;
}

class ImageViewer : public dod::GameObject
{
public:
	ImageViewer();
	~ImageViewer();

public:
	virtual void OnCreate();
	virtual void OnEnable();

	virtual void OnUpdate();

	virtual void OnDisable();
	virtual void OnRelease();

	int  Imagenumber;
};

