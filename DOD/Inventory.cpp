#include "Inventory.h"
#include "RenderSprite.h"
#include "GameEngine.h"
#include "Path.h"

Inventory::Inventory()
	:stateNumber(0)
	, _pSpritePrint(), _player()
{

}

Inventory::~Inventory()
{

}

void Inventory::OnCreate()
{
	// 플레이어 포인터 받아오기
	_player = (TestPlayer*)(engineptr->GetObjectptr(L"Tester"));

	// 렌더 스프라이트 만들기
	// 스프라이트
	_pSpritePrint = new dod::RenderSprite(0, 0, 6);
	_imageResourceManagerMap.insert({ 0, _pSpritePrint->PushBackImageDataVector(IMAGE_PATH(UI\\Roulette\\Dice_Number_Sheet_48X48.png)) });
	_imageResourceManagerMap.insert({ 1, _pSpritePrint->PushBackImageDataVector(IMAGE_PATH(UI\\Roulette\\Dice1.png)) });
	_imageResourceManagerMap.insert({ 2, _pSpritePrint->PushBackImageDataVector(IMAGE_PATH(UI\\Roulette\\Dice2.png)) });
	_imageResourceManagerMap.insert({ 3, _pSpritePrint->PushBackImageDataVector(IMAGE_PATH(UI\\Roulette\\Dice3.png)) });
	_imageResourceManagerMap.insert({ 4, _pSpritePrint->PushBackImageDataVector(IMAGE_PATH(UI\\Roulette\\Dice4.png)) });
	_imageResourceManagerMap.insert({ 5, _pSpritePrint->PushBackImageDataVector(IMAGE_PATH(UI\\Roulette\\Dice5.png)) });
	_imageResourceManagerMap.insert({ 6, _pSpritePrint->PushBackImageDataVector(IMAGE_PATH(UI\\Roulette\\Dice6.png)) });
	AddComponent(_pSpritePrint);

	// 트랜스폼 변수 초기화
	dod::Transform* transform = GetComponent<dod::Transform>();

	//객체 스케일 설정
	transform->scale.x = 3.3f;
	transform->scale.y = 3.3f;
}

void Inventory::OnEnable()
{
	_pSpritePrint->SetImageIndex(_imageResourceManagerMap.find(stateNumber)->second);
}

void Inventory::OnUpdate()
{
	_pSpritePrint->SetImageIndex(_imageResourceManagerMap.find(stateNumber)->second);
}

void Inventory::OnDisable()
{

}

void Inventory::OnRelease()
{

}
