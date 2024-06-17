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
	// �÷��̾� ������ �޾ƿ���
	_player = (TestPlayer*)(engineptr->GetObjectptr(L"Tester"));

	// ���� ��������Ʈ �����
	// ��������Ʈ
	_pSpritePrint = new dod::RenderSprite(0, 0, 6);
	_imageResourceManagerMap.insert({ 0, _pSpritePrint->PushBackImageDataVector(IMAGE_PATH(UI\\Roulette\\Dice_Number_Sheet_48X48.png)) });
	_imageResourceManagerMap.insert({ 1, _pSpritePrint->PushBackImageDataVector(IMAGE_PATH(UI\\Roulette\\Dice1.png)) });
	_imageResourceManagerMap.insert({ 2, _pSpritePrint->PushBackImageDataVector(IMAGE_PATH(UI\\Roulette\\Dice2.png)) });
	_imageResourceManagerMap.insert({ 3, _pSpritePrint->PushBackImageDataVector(IMAGE_PATH(UI\\Roulette\\Dice3.png)) });
	_imageResourceManagerMap.insert({ 4, _pSpritePrint->PushBackImageDataVector(IMAGE_PATH(UI\\Roulette\\Dice4.png)) });
	_imageResourceManagerMap.insert({ 5, _pSpritePrint->PushBackImageDataVector(IMAGE_PATH(UI\\Roulette\\Dice5.png)) });
	_imageResourceManagerMap.insert({ 6, _pSpritePrint->PushBackImageDataVector(IMAGE_PATH(UI\\Roulette\\Dice6.png)) });
	AddComponent(_pSpritePrint);

	// Ʈ������ ���� �ʱ�ȭ
	dod::Transform* transform = GetComponent<dod::Transform>();

	//��ü ������ ����
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
