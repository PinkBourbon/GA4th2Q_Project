#pragma once
#include "GameObject.h"
#include "RenderSprite.h"
#include <map>


	class Background : public dod::GameObject
	{
	public:
		Background();
		~Background();

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

