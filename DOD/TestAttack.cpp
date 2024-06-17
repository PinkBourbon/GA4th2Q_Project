#include <random>
#include <cmath>

#include "GameEngine.h"
#include "IComponent.h"
#include "RenderComponent.h"
#include "RenderText.h"
#include "RenderRect.h"
#include "KeyComponent.h"
#include "Transform.h"
#include "PhysicsComponent.h"
#include "Circle.h"
#include "TestPlayer.h"
#include "KeyManager.h"
#include "TestAttack.h"
#include "UIContoller.h"
#include "Boss.h"
#include "Path.h"
#include "RenderSprite.h"


enum eAttackSprite
{
	SPRITE_NORMAL_ATTACK,
	SPRITE_NORMAL_EFFECT,
	SPRITE_SKILL_3_ATTACK,
	SPRITE_SKILL_3_EFFECT,
	SPRITE_SKILL_4_ATTACK,
	SPRITE_SKILL_4_EFFECT,
	SPRITE_SKILL_5_ATTACK,
	SPRITE_SKILL_5_EFFECT
};

TestAttack::TestAttack()
	: _namePrinter(nullptr), _player(nullptr), _boss(nullptr), _uiController()
	, _diceNumber(0), _directionX(0.f), _directionY(0.f), _speed(0.f)
	, _isShooting(false), _damage(0), _attackType(AutoAttack), _isAttackSound(false), _pSpritePrint()
{

}

TestAttack::~TestAttack()
{

}

void TestAttack::OnCreate()
{
	//사각형 그리는 컴포넌트 추가
	//dod::RenderRect* pRenderRect = new dod::RenderRect(-16, -9, 16, 9, 3);
	//AddComponent(pRenderRect);

	//피직스컴포넌트 등록
	AddComponent(new dod::Circle(3.f));

	// 플레이어 얻어오기
	_player = (TestPlayer*)(engineptr->GetObjectptr(L"Tester"));
	_player->_diceNumber[0] = 0;

	// 보스 얻어오기
	_boss = (Boss*)(engineptr->GetObjectptr(L"Boss"));

	//트랜스폼 변수 초기화
	dod::Transform* transform = GetComponent<dod::Transform>();
	dod::Transform* pltransform = _player->GetComponent<dod::Transform>();	//주사위 숫자 출력해줄 하위 오브젝트 생성
	_namePrinter = engineptr->RegisterGameObject<dod::GameObject>(L"namePrinter");
	_namePrinter->AddComponent(new dod::RenderText(-30, -16, 3));
	_namePrinter->GetComponent<dod::Transform>()->SetParent(transform);

	// 공격 유형 스프라이트. 날라갈 때와 터질 때
	_pSpritePrint = new dod::RenderSprite(0, 0, 7);
	_imageResourceManagerMap.insert({ (int)SPRITE_NORMAL_ATTACK, _pSpritePrint->PushBackImageDataVector(IMAGE_PATH(Effect\\Dice\\Sheet\\Dice_Sheet.png)) });
	_imageResourceManagerMap.insert({ (int)SPRITE_NORMAL_EFFECT, _pSpritePrint->PushBackImageDataVector(IMAGE_PATH(Effect\\Dice\\Sheet\\Dice_Sheet.png)) });
	_imageResourceManagerMap.insert({ (int)SPRITE_SKILL_3_ATTACK, _pSpritePrint->PushBackImageDataVector(IMAGE_PATH(Effect\\Chip\\Sheet\\Chip_Blue_Sheet.png)) });
	_imageResourceManagerMap.insert({ (int)SPRITE_SKILL_3_EFFECT, _pSpritePrint->PushBackImageDataVector(IMAGE_PATH(Effect\\Chip\\Sheet\\Chip_Red_Sheet.png)) });
	_imageResourceManagerMap.insert({ (int)SPRITE_SKILL_4_ATTACK, _pSpritePrint->PushBackImageDataVector(IMAGE_PATH(Effect\\Card\\Sheet\\Spade_Card_Roll_Sheet.png)) });
	_imageResourceManagerMap.insert({ (int)SPRITE_SKILL_4_EFFECT, _pSpritePrint->PushBackImageDataVector(IMAGE_PATH(Effect\\Card\\Sheet\\Spade_Card_Hit_Sheet.png)) });
	_imageResourceManagerMap.insert({ (int)SPRITE_SKILL_5_ATTACK, _pSpritePrint->PushBackImageDataVector(IMAGE_PATH(Effect\\Coin\\Sheet\\Coin_Projectile_Sheet.png)) });
	_imageResourceManagerMap.insert({ (int)SPRITE_SKILL_5_EFFECT, _pSpritePrint->PushBackImageDataVector(IMAGE_PATH(Effect\\Coin\\Sheet\\Coin_Hit_Sheet.png)) });
	AddComponent(_pSpritePrint);

	//객체 스케일 설정
	transform->scale.x = 2;
	transform->scale.y = 2;
	//객체 스케일 설정
	transform->scale.x = 2;
	transform->scale.y = 2;

	transform->position.x = -100.f;
	transform->position.y = 1000.f;
}

void TestAttack::OnEnable()
{
	static bool isSoundCreate = false;



	if (isSoundCreate == false)
	{
		engineptr->soundManager->Sound_CreateSFXSound(SOUND_PATH(SFX\\Player_Attack.ogg), dod::PLAYER_NORMALATTACK_SFX); //내려치는 소리
		engineptr->soundManager->Sound_CreateSFXSound(SOUND_PATH(SFX\\Player_Skill.ogg), dod::PLAYER_SKILL_3COST_SFX);
		engineptr->soundManager->Sound_CreateSFXSound(SOUND_PATH(SFX\\Player_Skill_4_cost_Card.ogg), dod::PLAYER_SKILL_4COST_SFX);
		engineptr->soundManager->Sound_CreateSFXSound(SOUND_PATH(SFX\\Player_Skill_5_cost.ogg), dod::PLAYER_SKILL_5COST_FIRST_SFX);
		engineptr->soundManager->Sound_CreateSFXSound(SOUND_PATH(SFX\\Player_Skill_Coin_Fall.ogg), dod::PLAYER_SKILL_5COST_SECEND_SFX);
		isSoundCreate = true;
	}

	// 투사체 이미지 바꿔주기
	// 공격개시
	if (_attackType == AutoAttack)
	{
		if (_isAttackSound == false)
		{
			engineptr->soundManager->Sound_PlaySound(dod::PLAYER_NORMALATTACK_SFX);
			_isAttackSound = true;
		}
		_damage = 10;
		ShootAttack();
		_pSpritePrint->SetImageIndex(_imageResourceManagerMap.find((int)SPRITE_NORMAL_ATTACK)->second);
		return;
	}
	else if (_attackType == SkillAttack3)
	{
		if (_isAttackSound == false)
		{
			engineptr->soundManager->Sound_PlaySound(dod::PLAYER_SKILL_3COST_SFX);
			_isAttackSound = true;
		}
		_pSpritePrint->SetImageIndex(_imageResourceManagerMap.find((int)SPRITE_SKILL_3_ATTACK)->second);
		_damage = 60;
	}
	else if (_attackType == SkillAttack4)
	{
		if (_isAttackSound == false)
		{
			engineptr->soundManager->Sound_PlaySound(dod::PLAYER_SKILL_4COST_SFX);
			_isAttackSound = true;
		}
		_pSpritePrint->SetImageIndex(_imageResourceManagerMap.find((int)SPRITE_SKILL_4_ATTACK)->second);
		_damage = 85;
	}
	else if (_attackType == SkillAttack5)
	{
		if (_isAttackSound == false)
		{
			engineptr->soundManager->Sound_PlaySound(dod::PLAYER_SKILL_5COST_FIRST_SFX);
			engineptr->soundManager->Sound_PlaySound(dod::PLAYER_SKILL_5COST_SECEND_SFX); // 5코스트 부분 연출 되면 수정해야함
			_isAttackSound = true;
		}
		_pSpritePrint->SetImageIndex(_imageResourceManagerMap.find((int)SPRITE_SKILL_5_ATTACK)->second);
		_damage = 120;
	}
	else if (_attackType == None)
	{
		Assert(false, "또 죽었어?! 이젠 아주 타입이 없다고?");
	}

	ShootSkill();
	return;
}

void TestAttack::OnUpdate()
{
	dod::Transform* transform = this->GetComponent<dod::Transform>();

	// 피격시 이펙트 변경
	if (transform->position.y < 400)
	{
		if (_attackType == AutoAttack)
		{
			_pSpritePrint->SetImageIndex(_imageResourceManagerMap.find((int)SPRITE_NORMAL_EFFECT)->second);
		}
		else if (_attackType == SkillAttack3)
		{
			_pSpritePrint->SetImageIndex(_imageResourceManagerMap.find((int)SPRITE_SKILL_3_EFFECT)->second);
		}
		else if (_attackType == SkillAttack4)
		{
			_pSpritePrint->SetImageIndex(_imageResourceManagerMap.find((int)SPRITE_SKILL_4_EFFECT)->second);
		}
		else if (_attackType == SkillAttack5)
		{
			_pSpritePrint->SetImageIndex(_imageResourceManagerMap.find((int)SPRITE_SKILL_5_EFFECT)->second);
		}
	}

	// 보스 피격
	if (transform->position.y < 300)
	{
		if (_attackType != AutoAttack)
		{
			_player->_specialAttack = false;
		}
		_boss->AdjustHP(_damage);
		Reset();
		Disabler();
	}
}

void TestAttack::OnDisable()
{
	_isShooting = false;
}

void TestAttack::OnRelease()
{

}

void TestAttack::EnableSkill(eAttackType attackType)
{
	_attackType = attackType;	// 스위치 문에 스킬별 함수 넣으면 뺄것
	Enable();
}

void TestAttack::EnableAttack()
{
	_attackType = AutoAttack;
	Enable();
}

int TestAttack::GetDiceNumber()
{
	return _diceNumber;
}

void TestAttack::Disabler()
{
	_isShooting = false;
	_namePrinter->Disable();
	Disable();
}

void TestAttack::ShootAttack()
{
	static bool isSoundPlay = false;
	dod::Transform* transform = GetComponent<dod::Transform>();
	dod::Transform* pltransform = _player->GetComponent<dod::Transform>();
	_player = (TestPlayer*)(engineptr->GetObjectptr(L"Tester"));

	//주사위 번호 가져오기
	_diceNumber = _player->_diceNumber[0];
	_player->DiceCut();

	_player->_diceNumber[0] = 0;
	_player->CleanMydice();

	// 초기 위치와 방향, 속력 설정
	transform->position.x = pltransform->position.x;
	transform->position.y = pltransform->position.y;
	_directionX = (960 - pltransform->position.x);
	_directionY = (300 - pltransform->position.y);

	float denom = (float)sqrt(pow(_directionX, 2) + pow(_directionY, 2));
	_speed = (15 / denom);

	dod::PhysicsComponent* _transform = this->GetComponent<dod::PhysicsComponent>();
	_transform->SetVelocity(_directionX * _speed, _directionY * _speed);
}

void TestAttack::ShootSkill()
{
	dod::Transform* transform = GetComponent<dod::Transform>();
	dod::Transform* pltransform = _player->GetComponent<dod::Transform>();
	_player = (TestPlayer*)(engineptr->GetObjectptr(L"Tester"));
	_uiController = (UIController*)(engineptr->GetObjectptr(L"UIController"));

	_player->CleanMydice();

	// 플레이어 스킬모션 출력 위한 상태 변경
	_player->_specialAttack = true;

	// 초기 위치와 방향, 속력 설정
	transform->position.x = pltransform->position.x;
	transform->position.y = pltransform->position.y;

	_directionX = (960 - pltransform->position.x);
	_directionY = (300 - pltransform->position.y);

	float denom = (float)sqrt(pow(_directionX, 2) + pow(_directionY, 2));
	_speed = (10 / denom);

	dod::PhysicsComponent* _transform = this->GetComponent<dod::PhysicsComponent>();
	_transform->SetVelocity(_directionX * _speed, _directionY * _speed);
}

void TestAttack::Reset()
{
	dod::Transform* transform = this->GetComponent<dod::Transform>();

	_speed = 0;
	transform->position.x = -100.f;;
	transform->position.y = 1000.f;
	_diceNumber = 0;
	_damage = 0;
	_isShooting = false;
	_attackType = None;
	_isAttackSound = false;

}
