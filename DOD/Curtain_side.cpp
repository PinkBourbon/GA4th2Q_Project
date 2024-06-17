#include "Curtain_side.h"
#include "RenderSprite.h"
#include "GameEngine.h"
#include "Path.h"

	Curtain_side::Curtain_side()
		:direction(0), _pSpritePrint(), _imageResourceManagerMap()
	{

	}

	Curtain_side::~Curtain_side()
	{

	}

	void Curtain_side::OnCreate()
	{
		_pSpritePrint = new dod::RenderSprite(0, 0, 1);
		_imageResourceManagerMap.insert({ 0, _pSpritePrint->PushBackImageDataVector(IMAGE_PATH(Background\\Curtain_Side.png)) });
		AddComponent(_pSpritePrint);
	}

	void Curtain_side::OnEnable()
	{

	}

	void Curtain_side::OnUpdate()
	{

	}

	void Curtain_side::OnDisable()
	{

	}

	void Curtain_side::OnRelease()
	{

	}
