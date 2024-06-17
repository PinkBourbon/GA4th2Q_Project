#include <random>
#include <cmath>

#include "GameEngine.h"
#include "IComponent.h"
#include "RenderComponent.h"
#include "RenderText.h"
#include "RenderRect.h"
#include "RenderSprite.h"
#include "KeyComponent.h"
#include "Transform.h"
#include "PhysicsComponent.h"
#include "Circle.h"
#include "Rectangle.h"
#include "TestPlayer.h"
#include "KeyManager.h"
#include "TestDice.h"
#include "Path.h"

TestDice::TestDice()
	:_pSpritePrint()
{
	_namePrinter = nullptr;
	_player = nullptr;
	_diceNumber = 0;
}

TestDice::~TestDice()
{

}

void TestDice::OnCreate()
{
	//�簢�� �׸��� ������Ʈ �߰�
	//AddComponent(new dod::RenderRect(0, 0, 20, 20, 0));

	//������������Ʈ ���
	AddComponent(new dod::Rectangle(10.f,10.f));

	// ��������Ʈ

	_pSpritePrint = new dod::RenderSprite(0, 0, 5);
	_imageResourceManagerMap.insert({ 0, _pSpritePrint->PushBackImageDataVector(IMAGE_PATH(UI\\Dice\\dice_Rolling.png))});
	_imageResourceManagerMap.insert({ 1, _pSpritePrint->PushBackImageDataVector(IMAGE_PATH(UI\\Dice\\dice_Sheet1.png)) });
	_imageResourceManagerMap.insert({ 2, _pSpritePrint->PushBackImageDataVector(IMAGE_PATH(UI\\Dice\\dice_Sheet2.png)) });
	_imageResourceManagerMap.insert({ 3, _pSpritePrint->PushBackImageDataVector(IMAGE_PATH(UI\\Dice\\dice_Sheet3.png)) });
	_imageResourceManagerMap.insert({ 4, _pSpritePrint->PushBackImageDataVector(IMAGE_PATH(UI\\Dice\\dice_Sheet4.png)) });
	_imageResourceManagerMap.insert({ 5, _pSpritePrint->PushBackImageDataVector(IMAGE_PATH(UI\\Dice\\dice_Sheet5.png)) });
	_imageResourceManagerMap.insert({ 6, _pSpritePrint->PushBackImageDataVector(IMAGE_PATH(UI\\Dice\\dice_Sheet6.png)) });
	AddComponent(_pSpritePrint);

	//Ʈ������ ���� �ʱ�ȭ
	dod::Transform* transform = GetComponent<dod::Transform>();

	//�ֻ��� ���� ������� ���� ������Ʈ ����
	_namePrinter = engineptr->RegisterGameObject<dod::GameObject>(L"namePrinter");
	_namePrinter->AddComponent(new dod::RenderText(-5, -5, 0));
	_namePrinter->GetComponent<dod::Transform>()->SetParent(transform);
	_namePrinter->Enable();

	//��ü ������ ����
	transform->scale.x = 2;
	transform->scale.y = 2;

	_player = (TestPlayer*)(engineptr->GetObjectptr(L"Tester"));
}

void TestDice::OnEnable()
{
	static bool isSoundPlay = false;

	dod::Transform* transform = GetComponent<dod::Transform>();
	
	//�ֻ����� X ��ġ�� ���� ���� ��ǥ�� �޾ƿ��� ���Ѱ�
	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_int_distribution<int> dis(-30, 30);
	transform->position.x += (float)dis(gen);

	//�ֻ����� Y ��ġ�� ���� ������ǥ�� �޾ƿ��� ���Ѱ�
	std::mt19937 gen2(rd());
	std::uniform_int_distribution<int> dis2(-15, 15);
	transform->position.y += (float)dis2(gen);

	//�ֻ��� ��ȣ ��������
	std::mt19937 gen3(rd());
	std::uniform_int_distribution<int> dis3(1, 6);
	_diceNumber = dis3(gen3);

	//�ֻ��� ��ȣ ���
	//((dod::RenderText*)(_namePrinter->GetComponent<dod::RenderComponent>()))->SetString(L"%d", _diceNumber);
	_pSpritePrint->SetImageIndex(_imageResourceManagerMap.find(_diceNumber)->second);
	//_namePrinter->Enable();
	// _pSpritePrint->SetImageIndex(_imageResourceManagerMap.find(eImageList::PLAYERWALK)->second); //�̿� ���� ������� �������ǹ� �ȿ� ���ٸ� �߰����ָ��


	//�ֻ����� �÷��̾�� �浹 ������, ȣ��� ���ٽ��� ����
	dod::PhysicsComponent* physics = GetComponent<dod::PhysicsComponent>();
	physics->onCollisionEnter = [](dod::GameObject* thisObject, dod::GameObject* otherObject) // �� �κ� ����
	{
		if (otherObject->objectName == L"Tester")
		{
			if (((TestPlayer*)otherObject)->GetControlable() == true)
			{
				if (((TestPlayer*)otherObject)->addDice(((TestDice*)thisObject)))
					// c ��Ÿ�� ĳ������ Ȯ������ ������ ���� �� ��.
				{
					thisObject->engineptr->soundManager->Sound_CreateSFXSound(SOUND_PATH(SFX\\Player_Eat.ogg), dod::DICE_CAPTURE_SFX);
					isSoundPlay = true;
					thisObject->Disable();
				}
			}
		}
	};
}

void TestDice::OnUpdate()
{

}

void TestDice::OnDisable()
{
	//_namePrinter->Disable();
}

void TestDice::OnRelease()
{

}

int TestDice::GetDiceNumber()
{
	return _diceNumber;
}

void TestDice::Disabler()
{
	Disable();
}
