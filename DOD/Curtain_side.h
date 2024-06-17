#pragma once
#include "GameObject.h"
#include "RenderSprite.h"
#include <map>


	class Curtain_side : public dod::GameObject
	{
		friend class UIController;

	public:
		Curtain_side();
		~Curtain_side();

	public:
		virtual void OnCreate();
		virtual void OnEnable();

		virtual void OnUpdate();

		virtual void OnDisable();
		virtual void OnRelease();

	private:
		int direction;
		dod::RenderSprite* _pSpritePrint;
		std::map<int, int> _imageResourceManagerMap;
	};
