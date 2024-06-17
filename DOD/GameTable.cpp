#include "GameTable.h"
#include "RenderSprite.h"
#include "Path.h"

GameTable::GameTable()
	:_pSpritePrint()
{

}

GameTable::~GameTable()
{

}

void GameTable::OnCreate()
{
	_pSpritePrint = new dod::RenderSprite(0, 0, 4);
	_imageResourceManagerMap.insert({ 0, _pSpritePrint->PushBackImageDataVector(IMAGE_PATH(Background\\Game_Table.png)) });
	AddComponent(_pSpritePrint);
	dod::Transform* transform = GetComponent<dod::Transform>();
	transform->scale.x = 1.55f;
	transform->scale.y = 1.65f;
	transform->position.x = 950.f;
	transform->position.y = 470.f;
}

void GameTable::OnEnable()
{

}

void GameTable::OnUpdate()
{

}

void GameTable::OnDisable()
{

}

void GameTable::OnRelease()
{

}
