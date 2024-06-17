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
	//�簢�� �׸��� ������Ʈ �߰�
	//dod::RenderRect* pRenderRect = new dod::RenderRect(-16, -9, 16, 9, 3);
	//AddComponent(pRenderRect);

	//������������Ʈ ���
	AddComponent(new dod::Circle(3.f));

	// �÷��̾� ������
	_player = (TestPlayer*)(engineptr->GetObjectptr(L"Tester"));
	_player->_diceNumber[0] = 0;

	// ���� ������
	_boss = (Boss*)(engineptr->GetObjectptr(L"Boss"));

	//Ʈ������ ���� �ʱ�ȭ
	dod::Transform* transform = GetComponent<dod::Transform>();
	dod::Transform* pltransform = _player->GetComponent<dod::Transform>();	//�ֻ��� ���� ������� ���� ������Ʈ ����
	_namePrinter = engineptr->RegisterGameObject<dod::GameObject>(L"namePrinter");
	_namePrinter->AddComponent(new dod::RenderText(-30, -16, 3));
	_namePrinter->GetComponent<dod::Transform>()->SetParent(transform);

	// ���� ���� ��������Ʈ. ���� ���� ���� ��
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

	//��ü ������ ����
	transform->scale.x = 2;
	transform->scale.y = 2;
	//��ü ������ ����
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
		engineptr->soundManager->Sound_CreateSFXSound(SOUND_PATH(SFX\\Player_Attack.ogg), dod::PLAYER_NORMALATTACK_SFX); //����ġ�� �Ҹ�
		engineptr->soundManager->Sound_CreateSFXSound(SOUND_PATH(SFX\\Player_Skill.ogg), dod::PLAYER_SKILL_3COST_SFX);
		engineptr->soundManager->Sound_CreateSFXSound(SOUND_PATH(SFX\\Player_Skill_4_cost_Card.ogg), dod::PLAYER_SKILL_4COST_SFX);
		engineptr->soundManager->Sound_CreateSFXSound(SOUND_PATH(SFX\\Player_Skill_5_cost.ogg), dod::PLAYER_SKILL_5COST_FIRST_SFX);
		engineptr->soundManager->Sound_CreateSFXSound(SOUND_PATH(SFX\\Player_Skill_Coin_Fall.ogg), dod::PLAYER_SKILL_5COST_SECEND_SFX);
		isSoundCreate = true;
	}

	// ����ü �̹��� �ٲ��ֱ�
	// ���ݰ���
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
			engineptr->soundManager->Sound_PlaySound(dod::PLAYER_SKILL_5COST_SECEND_SFX); // 5�ڽ�Ʈ �κ� ���� �Ǹ� �����ؾ���
			_isAttackSound = true;
		}
		_pSpritePrint->SetImageIndex(_imageResourceManagerMap.find((int)SPRITE_SKILL_5_ATTACK)->second);
		_damage = 120;
	}
	else if (_attackType == None)
	{
		Assert(false, "�� �׾���?! ���� ���� Ÿ���� ���ٰ�?");
	}

	ShootSkill();
	return;
}

void TestAttack::OnUpdate()
{
	dod::Transform* transform = this->GetComponent<dod::Transform>();

	// �ǰݽ� ����Ʈ ����
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

	// ���� �ǰ�
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
	_attackType = attackType;	// ����ġ ���� ��ų�� �Լ� ������ ����
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

	//�ֻ��� ��ȣ ��������
	_diceNumber = _player->_diceNumber[0];
	_player->DiceCut();

	_player->_diceNumber[0] = 0;
	_player->CleanMydice();

	// �ʱ� ��ġ�� ����, �ӷ� ����
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

	// �÷��̾� ��ų��� ��� ���� ���� ����
	_player->_specialAttack = true;

	// �ʱ� ��ġ�� ����, �ӷ� ����
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
