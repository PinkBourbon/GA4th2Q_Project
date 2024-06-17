#include "Curtain_top.h"
#include "RenderSprite.h"
#include "Path.h"

	Curtain_top::Curtain_top()
		:_pSpritePrint()
	{

	}

	Curtain_top::~Curtain_top()
	{

	}

	void Curtain_top::OnCreate()
	{
		_pSpritePrint = new dod::RenderSprite(0, 0, 2);
		_imageResourceManagerMap.insert({ 0, _pSpritePrint->PushBackImageDataVector(IMAGE_PATH(Background\\Curtain_Top.png)) });
		AddComponent(_pSpritePrint);
		dod::Transform* transform = GetComponent<dod::Transform>();
		transform->scale.x = 1.6f;
		transform->scale.y = 1.6f;
		transform->position.x = 920.f;
		transform->position.y = 480.f;
	}

	void Curtain_top::OnEnable()
	{

	}

	void Curtain_top::OnUpdate()
	{

	}

	void Curtain_top::OnDisable()
	{

	}

	void Curtain_top::OnRelease()
	{

	}
