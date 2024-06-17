#include "Background.h"
#include "RenderSprite.h"
#include "Path.h"


	Background::Background()
		:_pSpritePrint()
	{

	}

	Background::~Background()
	{

	}

	void Background::OnCreate()
	{
		_pSpritePrint = new dod::RenderSprite(0, 0, 0);
		_imageResourceManagerMap.insert({ 0, _pSpritePrint->PushBackImageDataVector(IMAGE_PATH(Background\\Background.png)) });
		AddComponent(_pSpritePrint);
		dod::Transform* transform = GetComponent<dod::Transform>();
		transform->scale.x = 1.6f;
		transform->scale.y = 1.6f;
		transform->position.x = 920.f;
		transform->position.y = 480.f;
	}

	void Background::OnEnable()
	{

	}

	void Background::OnUpdate()
	{

	}

	void Background::OnDisable()
	{

	}

	void Background::OnRelease()
	{

	}
