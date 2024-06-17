#include "SkillDice.h"
#include "RenderSprite.h"
#include "GameEngine.h"
#include "Path.h"

SkillDice::SkillDice()
	:stateNumber(0)
	, _pSpritePrint(), _player()
{

}

SkillDice::~SkillDice()
{

}

void SkillDice::OnCreate()
{
	// 플레이어 포인터 받아오기
	_player = (TestPlayer*)(engineptr->GetObjectptr(L"Tester"));

	// 렌더 스프라이트 만들기
	// 스프라이트

	_pSpritePrint = new dod::RenderSprite(0, 0, 6);
	_imageResourceManagerMap.insert({ 0, _pSpritePrint->PushBackImageDataVector(IMAGE_PATH(UI\\Roulette\\Roulette_Roll_Sheet_64X64.png)) });
	_imageResourceManagerMap.insert({ 1, _pSpritePrint->PushBackImageDataVector(IMAGE_PATH(UI\\Roulette\\Roulette_Numberl_Sheet1.png)) });
	_imageResourceManagerMap.insert({ 2, _pSpritePrint->PushBackImageDataVector(IMAGE_PATH(UI\\Roulette\\Roulette_Numberl_Sheet2.png)) });
	_imageResourceManagerMap.insert({ 3, _pSpritePrint->PushBackImageDataVector(IMAGE_PATH(UI\\Roulette\\Roulette_Numberl_Sheet3.png)) });
	_imageResourceManagerMap.insert({ 4, _pSpritePrint->PushBackImageDataVector(IMAGE_PATH(UI\\Roulette\\Roulette_Numberl_Sheet4.png)) });
	_imageResourceManagerMap.insert({ 5, _pSpritePrint->PushBackImageDataVector(IMAGE_PATH(UI\\Roulette\\Roulette_Numberl_Sheet5.png)) });
	_imageResourceManagerMap.insert({ 6, _pSpritePrint->PushBackImageDataVector(IMAGE_PATH(UI\\Roulette\\Roulette_Numberl_Sheet6.png)) });
	_imageResourceManagerMap.insert({ 7, _pSpritePrint->PushBackImageDataVector(IMAGE_PATH(UI\\Roulette\\Roulette_Shadow.png)) });
	AddComponent(_pSpritePrint);

	// 트랜스폼 변수 초기화
	dod::Transform* transform = GetComponent<dod::Transform>();

	//객체 스케일 설정
	transform->scale.x = 2.9f;
	transform->scale.y = 2.9f;
}

void SkillDice::OnEnable()
{

}

void SkillDice::OnUpdate()
{

}

void SkillDice::OnDisable()
{

}

void SkillDice::OnRelease()
{

}

void SkillDice::MatchNumberImage()
{
	_pSpritePrint->SetImageIndex(_imageResourceManagerMap.find(stateNumber)->second);
}

void SkillDice::MatchNumberImage(int num)
{
	stateNumber = num;
	_pSpritePrint->SetImageIndex(_imageResourceManagerMap.find(stateNumber)->second);
}
