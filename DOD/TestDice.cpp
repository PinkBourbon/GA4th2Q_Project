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
	//사각형 그리는 컴포넌트 추가
	//AddComponent(new dod::RenderRect(0, 0, 20, 20, 0));

	//피직스컴포넌트 등록
	AddComponent(new dod::Rectangle(10.f,10.f));

	// 스프라이트

	_pSpritePrint = new dod::RenderSprite(0, 0, 5);
	_imageResourceManagerMap.insert({ 0, _pSpritePrint->PushBackImageDataVector(IMAGE_PATH(UI\\Dice\\dice_Rolling.png))});
	_imageResourceManagerMap.insert({ 1, _pSpritePrint->PushBackImageDataVector(IMAGE_PATH(UI\\Dice\\dice_Sheet1.png)) });
	_imageResourceManagerMap.insert({ 2, _pSpritePrint->PushBackImageDataVector(IMAGE_PATH(UI\\Dice\\dice_Sheet2.png)) });
	_imageResourceManagerMap.insert({ 3, _pSpritePrint->PushBackImageDataVector(IMAGE_PATH(UI\\Dice\\dice_Sheet3.png)) });
	_imageResourceManagerMap.insert({ 4, _pSpritePrint->PushBackImageDataVector(IMAGE_PATH(UI\\Dice\\dice_Sheet4.png)) });
	_imageResourceManagerMap.insert({ 5, _pSpritePrint->PushBackImageDataVector(IMAGE_PATH(UI\\Dice\\dice_Sheet5.png)) });
	_imageResourceManagerMap.insert({ 6, _pSpritePrint->PushBackImageDataVector(IMAGE_PATH(UI\\Dice\\dice_Sheet6.png)) });
	AddComponent(_pSpritePrint);

	//트랜스폼 변수 초기화
	dod::Transform* transform = GetComponent<dod::Transform>();

	//주사위 숫자 출력해줄 하위 오브젝트 생성
	_namePrinter = engineptr->RegisterGameObject<dod::GameObject>(L"namePrinter");
	_namePrinter->AddComponent(new dod::RenderText(-5, -5, 0));
	_namePrinter->GetComponent<dod::Transform>()->SetParent(transform);
	_namePrinter->Enable();

	//객체 스케일 설정
	transform->scale.x = 2;
	transform->scale.y = 2;

	_player = (TestPlayer*)(engineptr->GetObjectptr(L"Tester"));
}

void TestDice::OnEnable()
{
	static bool isSoundPlay = false;

	dod::Transform* transform = GetComponent<dod::Transform>();
	
	//주사위의 X 위치에 대한 랜덤 좌표를 받아오기 위한것
	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_int_distribution<int> dis(-30, 30);
	transform->position.x += (float)dis(gen);

	//주사위의 Y 위치에 대한 랜덤좌표를 받아오기 위한것
	std::mt19937 gen2(rd());
	std::uniform_int_distribution<int> dis2(-15, 15);
	transform->position.y += (float)dis2(gen);

	//주사위 번호 랜덤지정
	std::mt19937 gen3(rd());
	std::uniform_int_distribution<int> dis3(1, 6);
	_diceNumber = dis3(gen3);

	//주사위 번호 출력
	//((dod::RenderText*)(_namePrinter->GetComponent<dod::RenderComponent>()))->SetString(L"%d", _diceNumber);
	_pSpritePrint->SetImageIndex(_imageResourceManagerMap.find(_diceNumber)->second);
	//_namePrinter->Enable();
	// _pSpritePrint->SetImageIndex(_imageResourceManagerMap.find(eImageList::PLAYERWALK)->second); //이와 같은 방법으로 실행조건문 안에 한줄만 추가해주면댐


	//주사위가 플레이어와 충돌 했을때, 호출될 람다식의 정의
	dod::PhysicsComponent* physics = GetComponent<dod::PhysicsComponent>();
	physics->onCollisionEnter = [](dod::GameObject* thisObject, dod::GameObject* otherObject) // 이 부분 뭘까
	{
		if (otherObject->objectName == L"Tester")
		{
			if (((TestPlayer*)otherObject)->GetControlable() == true)
			{
				if (((TestPlayer*)otherObject)->addDice(((TestDice*)thisObject)))
					// c 스타일 캐스팅은 확실하지 않으면 걸지 말 것.
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
