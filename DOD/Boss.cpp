#include <random>
#include "Boss.h"
#include "Transform.h"
#include "GameEngine.h"
#include "TestPlayer.h"

#include "PhysicsComponent.h"
#include "Circle.h"
#include "RenderText.h"
#include "SoundManager.h"
#include "Path.h"
#include "RenderSprite.h"

Boss::Boss() :
	_eState{ 0 },
	_bossArmL{ 0 }, _bossArmR{ 0 },
	_deltanum{ 0 },
	_attackNumber{ 0 },
	_bossTransform{ 0 },
	_stoneObject{ 0 },
	_testPlayerptr{ 0 },
	_pHPPrinter(nullptr), hP(30),
	realTime{ 0 },
	_isInitAttackSwing{ false },
	_breathCount{ 0 }
	, _bossArmLWarningObject(), _bossArmRWarningObject()
{
	_eState = dod::eBossState::BOSSSTART;
	maxHp = 1000;
	hP = maxHp;
	basicScale = 1.48f;
}

Boss::~Boss()
{

}

void Boss::OnCreate()
{
	_pBossSprite = new dod::RenderSprite(0, 0, 3);
	//_bossSpriteMap.insert({ eBossPattern::STARTSCENE,_pBossSprite->PushBackImageDataVector(IMAGE_PATH(Sprite\\Boss\\Boss.png))});

	_bossSpriteMap.insert({ dod::eBossPattern::IDLE,_pBossSprite->PushBackImageDataVector(IMAGE_PATH(Sprite\\Boss\\Sheet\\Boss_Base_Idle_Sheet.png)) });
	_bossSpriteMap.insert({ dod::eBossPattern::ATTACK,_pBossSprite->PushBackImageDataVector(IMAGE_PATH(Sprite\\Boss\\Sheet\\Boss_Base_Attack_Sheet.png),0.04) });
	_bossSpriteMap.insert({ dod::eBossPattern::ATTACKL,_pBossSprite->PushBackImageDataVector(IMAGE_PATH(Sprite\\Boss\\Sheet\\Boss_Base_AttackL_Sheet.png),0.04) });
	_bossSpriteMap.insert({ dod::eBossPattern::ATTACKR,_pBossSprite->PushBackImageDataVector(IMAGE_PATH(Sprite\\Boss\\Sheet\\Boss_Base_AttackR_Sheet.png),0.04) });
	_bossSpriteMap.insert({ dod::eBossPattern::BREATHE,_pBossSprite->PushBackImageDataVector(IMAGE_PATH(Sprite\\Boss\\Sheet\\Boss_Base_Breathe_Sheet.png),0.04) });
	AddComponent(_pBossSprite);

	_bossTransform = GetComponent<dod::Transform>(); // 이동	
	_bossTransform->position.x = 1000;
	_bossTransform->position.y = 400;
	_bossTransform->scale.x = 1.5f;
	_bossTransform->scale.y = 1.5f;

	_bossArmL = engineptr->RegisterGameObject<BossArm>(L"BossArm");

	_pArmLSprite = new dod::RenderSprite(0, 0, 6);
	_bossArmLMap.insert({ dod::eBossPattern::IDLE,_pArmLSprite->PushBackImageDataVector(IMAGE_PATH(Sprite\\Boss\\Sheet\\Boss_ArmL_Idle_Sheet.png),0.08) });
	_bossArmLMap.insert({ dod::eBossPattern::ATTACK,_pArmLSprite->PushBackImageDataVector(IMAGE_PATH(Sprite\\Boss\\Sheet\\Boss_ArmL_Attack_Sheet.png),0.04) });
	_bossArmLMap.insert({ dod::eBossPattern::ATTACKL,_pArmLSprite->PushBackImageDataVector(IMAGE_PATH(Sprite\\Boss\\Sheet\\Boss_ArmL_AttackL_Sheet.png),0.04) });
	_bossArmLMap.insert({ dod::eBossPattern::ATTACKR,_pArmLSprite->PushBackImageDataVector(IMAGE_PATH(Sprite\\Boss\\Sheet\\Boss_ArmL_AttackR_Sheet.png),0.04) });
	_bossArmLMap.insert({ dod::eBossPattern::BREATHE,_pArmLSprite->PushBackImageDataVector(IMAGE_PATH(Sprite\\Boss\\Sheet\\Boss_ArmL_Breathe_Sheet.png),0.04) });

	_bossArmL->AddComponent(_pArmLSprite);
	_bossArmL->BossInitalation();
	_bossArmL->BossParentSet(this);
	_bossArmL->bossArmTransform->SetParent(_bossTransform);
	_bossArmL->bossArmTransform->position.x = -520;
	_bossArmL->bossArmTransform->position.y = 0;

	// 왼팔 스윙 경고하는 오브젝트
	_bossArmLWarningObject = engineptr->RegisterGameObject<BossArm>(L"BossArmLWarningObject");
	dod::RenderSprite* _bossArmLWarningSprite = new dod::RenderSprite(0, 0, 9);
	_bossArmLWarningSprite->PushBackImageDataVector(IMAGE_PATH(Effect\\Warning\\BossL.png), 0.15);
	_bossArmLWarningObject->AddComponent(_bossArmLWarningSprite);
	_bossArmLWarningObject->BossInitalation();
	_bossArmLWarningObject->bossArmTransform->SetParent(_bossTransform);
	_bossArmLWarningObject->GetComponent<dod::Transform>()->position.x = -38;
	_bossArmLWarningObject->GetComponent<dod::Transform>()->position.y = 147;


	_bossArmR = engineptr->RegisterGameObject<BossArm>(L"BossArm");

	_pArmRSprite = new dod::RenderSprite(0, 0, 6);
	_bossArmRMap.insert({ dod::eBossPattern::IDLE,_pArmRSprite->PushBackImageDataVector(IMAGE_PATH(Sprite\\Boss\\Sheet\\Boss_ArmR_Idle_Sheet.png),0.08) });
	_bossArmRMap.insert({ dod::eBossPattern::ATTACK,_pArmRSprite->PushBackImageDataVector(IMAGE_PATH(Sprite\\Boss\\Sheet\\Boss_ArmR_Attack_Sheet.png),0.04) });
	_bossArmRMap.insert({ dod::eBossPattern::ATTACKL,_pArmRSprite->PushBackImageDataVector(IMAGE_PATH(Sprite\\Boss\\Sheet\\Boss_ArmR_AttackL_Sheet.png),0.04) });
	_bossArmRMap.insert({ dod::eBossPattern::ATTACKR,_pArmRSprite->PushBackImageDataVector(IMAGE_PATH(Sprite\\Boss\\Sheet\\Boss_ArmR_AttackR_Sheet.png),0.04) });
	_bossArmRMap.insert({ dod::eBossPattern::BREATHE,_pArmRSprite->PushBackImageDataVector(IMAGE_PATH(Sprite\\Boss\\Sheet\\Boss_ArmR_Breathe_Sheet.png),0.04) });	//_bossArmR->AddComponent(new dod::RenderRect(0,0,100,150,6));

	_bossArmR->AddComponent(_pArmRSprite);
	_bossArmR->BossInitalation();
	_bossArmR->BossParentSet(this);
	_bossArmR->bossArmTransform->SetParent(_bossTransform);
	_bossArmR->bossArmTransform->position.x = 520;
	_bossArmR->bossArmTransform->position.y = 0;

	// 오른팔 스윙 경고하는 오브젝트
	_bossArmRWarningObject = engineptr->RegisterGameObject<BossArm>(L"BossArmRWarningObject");
	dod::RenderSprite* _bossArmRWarningSprite = new dod::RenderSprite(0, 0, 9);
	_bossArmRWarningSprite->PushBackImageDataVector(IMAGE_PATH(Effect\\Warning\\BossR.png), 0.15);
	_bossArmRWarningObject->AddComponent(_bossArmRWarningSprite);
	_bossArmRWarningObject->BossInitalation();
	_bossArmRWarningObject->bossArmTransform->SetParent(_bossTransform);
	_bossArmRWarningObject->GetComponent<dod::Transform>()->position.x = -38;
	_bossArmRWarningObject->GetComponent<dod::Transform>()->position.y = 147;


	for (int i = 0; i < 6; i++) // 6개 생성
	{
		_stoneObject[i] = engineptr->RegisterGameObject<StoneObject>(L"StoneObject");
		dod::RenderSprite* stoneSprite = new dod::RenderSprite(0, 0, 7);
		stoneSprite->PushBackImageDataVector(IMAGE_PATH(Effect\\Stone\\Sheet\\Stone_Sheet.png));
		_stoneObject[i]->AddComponent(stoneSprite);
		_stoneObject[i]->AddComponent(new dod::Circle(10.0f));
		_stoneObject[i]->StoneInitalation();
		_stoneObject[i]->StoneTransform(i);
		_stoneObject[i]->GetComponent<dod::Transform>()->scale.x = 3;
		_stoneObject[i]->GetComponent<dod::Transform>()->scale.y = 3;
	}

	_thornObject = engineptr->RegisterGameObject<thornObject>(L"ThornObject"); // 가시 오브젝트
	dod::RenderSprite* _thornSprite = new dod::RenderSprite(0, 0, 5);
	_thornSprite->PushBackImageDataVector(IMAGE_PATH(Effect\\Spike\\Spike_Sheet.png), 0.1);
	_thornObject->AddComponent(_thornSprite);
	_thornObject->AddComponent(new dod::Rectangle(16.5f, 16.5f));
	_thornObject->ThornInitalation();
	_thornObject->thornTransform->position.x = 0.f;
	_thornObject->thornTransform->position.y = 0.f;
	_thornObject->thornTransform->scale.x = 4.f;
	_thornObject->thornTransform->scale.y = 4.f;


	_thornWarningObject = engineptr->RegisterGameObject<thornObject>(L"ThornWarningObject"); // 가시 출현을 경고하는 오브젝트
	dod::RenderSprite* _thornWarningSprite = new dod::RenderSprite(0, 0, 5);
	_thornWarningSprite->PushBackImageDataVector(IMAGE_PATH(Effect\\Warning\\Spike.png));
	_thornWarningObject->AddComponent(_thornWarningSprite);
	// 물리컴포넌트 없앴음 -AJY
	//_thornWarningObject->AddComponent(new dod::Circle());
	_thornWarningObject->ThornInitalation();
	_thornWarningObject->thornTransform->position.x = 0.f;
	_thornWarningObject->thornTransform->position.y = 0.f;
	_thornWarningObject->thornTransform->scale.x = 2.0f;
	_thornWarningObject->thornTransform->scale.y = 2.0f;

	_testPlayerptr = ((TestPlayer*)engineptr->GetObjectptr(L"Tester"));

	_breathObject = engineptr->RegisterGameObject<BreathObject>(L"BreathObject");
	_pBossBreathSprite = new dod::RenderSprite(0, 0, 7);
	_pBossBreathSprite->PushBackImageDataVector(IMAGE_PATH(Effect\\Smoke\\Sheet\\Breathe_Sheet.png), 0.1);
	_breathObject->AddComponent(_pBossBreathSprite);
	_breathObject->BreathInitalation();
	_breathObject->BossParentSet(this);
	_breathObject->breathTransform->SetParent(_bossTransform);
	_breathObject->breathTransform->position.x = 0;
	_breathObject->breathTransform->position.y = 0;


	// 보스 얼굴 아이콘 및 hp바
	_pBossIcon = engineptr->RegisterGameObject<dod::GameObject>(L"BossIcon");
	dod::RenderSprite* bossIconSprite = new dod::RenderSprite(0, 0, 9);
	bossIconSprite->PushBackImageDataVector(IMAGE_PATH(UI\\character_ui_boss.png));
	_pBossIcon->AddComponent(bossIconSprite);
	_pBossIcon->GetComponent<dod::Transform>()->scale.x = 1.5f;
	_pBossIcon->GetComponent<dod::Transform>()->scale.y = 1.5f;
	_pBossIcon->GetComponent<dod::Transform>()->position.x = 50;
	_pBossIcon->GetComponent<dod::Transform>()->position.y = 50;

	_pHPBarOutline = engineptr->RegisterGameObject<dod::GameObject>(L"BossHPBarOutline");
	dod::RenderSprite* bossHPBarOutLineSprite = new dod::RenderSprite(0, 0, 7);
	bossHPBarOutLineSprite->PushBackImageDataVector(IMAGE_PATH(UI\\hpbar_empty.png));
	_pHPBarOutline->AddComponent(bossHPBarOutLineSprite);
	_pHPBarOutline->GetComponent<dod::Transform>()->scale.x = 1.5f;
	_pHPBarOutline->GetComponent<dod::Transform>()->scale.y = 0.7f;
	_pHPBarOutline->GetComponent<dod::Transform>()->position.x = 950;
	_pHPBarOutline->GetComponent<dod::Transform>()->position.y = 30;

	_pHPBar = engineptr->RegisterGameObject<dod::GameObject>(L"BossHPBarOutline");
	dod::RenderSprite* bossHPBarSprite = new dod::RenderSprite(640, 0, 8);
	bossHPBarSprite->PushBackImageDataVector(IMAGE_PATH(UI\\hpbar_hp.png));
	_pHPBar->AddComponent(bossHPBarSprite);
	_pHPBar->GetComponent<dod::Transform>()->scale.x = basicScale;
	_pHPBar->GetComponent<dod::Transform>()->scale.y = 0.7f;
	_pHPBar->GetComponent<dod::Transform>()->position.x = 15;
	_pHPBar->GetComponent<dod::Transform>()->position.y = 30;


	// 오브젝트의 체력을 출력할 오브젝트
	_pHPPrinter = engineptr->RegisterGameObject<dod::GameObject>(L"HPPrinter");
	_pHPPrinter->AddComponent(new dod::RenderText(-29.7f, -0, 0));
	_pHPPrinter->GetComponent<dod::Transform>()->SetParent(GetComponent<dod::Transform>());
}

void Boss::OnEnable()
{
	_pHPBar->Enable();
	_pHPBarOutline->Enable();
	_pBossIcon->Enable();
	_pHPPrinter->Enable();
	_bossArmL->Enable();
	_bossArmR->Enable();

	_breathCount = 0;
}

void Boss::OnUpdate()
{
	//dod::Transform* transform = GetComponent<dod::Transform>();
	BossState();

	// 보스 팔공격 패턴에 따른 스프라이트애니메이션 변경 일단주석
// 	_pBossSprite->SetImageIndex(_bossSpriteMap.find(_bossArmL->ReturnBossPattern())->second);
// 	_pArmLSprite->SetImageIndex(_bossArmRMap.find(_bossArmL->ReturnBossPattern())->second);
// 	_pArmRSprite->SetImageIndex(_bossArmLMap.find(_bossArmL->ReturnBossPattern())->second);

	//오브젝트의 체력을 출력
	if (_pHPPrinter != nullptr)
	{
		((dod::RenderText*)(_pHPPrinter->GetComponent<dod::RenderComponent>()))->SetString(L"HP : %d", hP);
	}

	_pHPBar->GetComponent<dod::Transform>()->scale.x = ((float)hP / (float)maxHp) * basicScale;
}

void Boss::OnDisable()
{
	_pHPBar->Disable();
	_pHPBarOutline->Disable();
	_pHPPrinter->Disable();
	_bossArmL->Disable();
	_bossArmR->Disable();
	_pBossIcon->Disable();

	for (auto& e : _stoneObject)
	{
		e->Disable();
	}
	_thornWarningObject->Disable();
	_thornObject->Disable();
}

void Boss::OnRelease()
{

}

void Boss::BossState() // 업데이트에서 반복할 예정 한 프레임에서 
{

	switch (_eState)
	{
		case dod::eBossState::BOSSSTART:
			BossStart();
			break;
		case dod::eBossState::BOSSIDLE:
			BossIdle();
			break;
		case dod::eBossState::BOSSSTONE:
			BossAttack_Stone();
			break;
		case dod::eBossState::BOSSSUNKEN:
			BossAttack_Sunken();
			break;
		case dod::eBossState::BOSSSWIGATTACK:
			BossAttack_Swing(_swingAttackNumber);
			break;
		case dod::eBossState::BOSSBREATH:
			BossAttack_Breath();
			break;
		case dod::eBossState::BOSSHIT:
			//BossHit(); // 보스 피격시, 일반공격에 피격할때 마다 출력할지는 모르겠음
			break;
		case dod::eBossState::BOSSDIE:
			BossDead();
			break;
		default:
			break;
	}
}

void Boss::BossStart()
{
	static bool isSoundPlay = false;
	static double startTime = 0;
	startTime += engineptr->timer.GetFrameTime();

	if (_bossTransform->position.y > 260)
	{
		_bossTransform->position.y -= 1;
		_bossArmL->bossArmTransform->position.x += 3.7f;
		_bossArmR->bossArmTransform->position.x -= 3.7f;
	}
	else
	{
		if (isSoundPlay == false)
		{
			engineptr->soundManager->Sound_CreateSFXSound(SOUND_PATH(SFX\\Boss_Growl.ogg), dod::BOSS_START_SFX);
			isSoundPlay = true;
		}
		engineptr->soundManager->Sound_PlaySound(dod::BOSS_START_SFX);

		if (startTime > 1)
		{
			_eState = dod::eBossState::BOSSIDLE; // 넘어가는 구문
		}
	}
	// 게임 시작할때 모션 기능, 이후 IDLE로 넘어감
}


void Boss::BossIdle()
{
	// 가만히 있을때의 대기 애니메이션 여기서 다양한 공격, 피격으로 넘어감
	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_int_distribution<int> dis(1, 4);
	_swingAttackNumber = dis(gen);


	static double idleTime = 0;

	realTime += engineptr->timer.GetDeltaTime();
	idleTime += engineptr->timer.GetDeltaTime();
	static bool isBodyUp = false;

	static bool doAttack = false;
	static bool doSwing = false;




	_pBossSprite->SetImageIndex(_bossSpriteMap.find(dod::eBossPattern::IDLE)->second);
	_pArmLSprite->SetImageIndex(_bossArmRMap.find(dod::eBossPattern::IDLE)->second);
	_pArmRSprite->SetImageIndex(_bossArmLMap.find(dod::eBossPattern::IDLE)->second);

	if ((hP < maxHp * 8 / 10 && _breathCount == 0)
		|| (hP < maxHp * 6 / 10 && _breathCount == 1)
		|| (hP < maxHp * 3 / 10 && _breathCount == 2))
	{
		_eState = dod::eBossState::BOSSBREATH;
		_breathCount++;
		doAttack = true;
		realTime = 0;
	}
	else if (realTime > 3) //몇 초에 한번 노멀 공격 발동
	{
		if (_swingAttackNumber == 1)
		{
			realTime = 0;
			_eState = dod::eBossState::BOSSSTONE;
			doAttack = true;
		}
		else if (_swingAttackNumber == 2 || _swingAttackNumber == 3)
		{
			realTime = 0;
			_eState = dod::eBossState::BOSSSWIGATTACK;
			doAttack = true;
		}
		else if (_swingAttackNumber == 4)
		{
			realTime = 0;
			_eState = dod::eBossState::BOSSSUNKEN;
			doAttack = true;
		}
	}
}

void Boss::BossAttack_Sunken()
{
	static double thornAttackTime = 0;
	thornAttackTime += engineptr->timer.GetDeltaTime();
	static bool isShow = false;
	static float tempX = 0;
	static float tempY = 0;
	static bool isSoundPlayFirst = false;
	static bool isSoundPlaySecend = false;
	static bool isSoundCreateFirst = false;
	static bool isSoundCreateSecend = false;
	//static bool isSoundThird = false;

	_pBossSprite->SetImageIndex(_bossSpriteMap.find(dod::eBossPattern::ATTACK)->second);
	_pArmLSprite->SetImageIndex(_bossArmRMap.find(dod::eBossPattern::ATTACK)->second);
	_pArmRSprite->SetImageIndex(_bossArmLMap.find(dod::eBossPattern::ATTACK)->second);


	if (isSoundCreateFirst == false)
	{
		engineptr->soundManager->Sound_CreateSFXSound(SOUND_PATH(SFX\\Boss_Skill_1.ogg), dod::BOSS_ATTACK_SUNKEN_FIRST_SFX); //내려치는 소리
		isSoundCreateFirst = true;
	}

	if (isSoundPlayFirst == false)
	{
		engineptr->soundManager->Sound_PlaySound(dod::BOSS_ATTACK_SUNKEN_FIRST_SFX);
		isSoundPlayFirst = true;
	}

	if (thornAttackTime > 0.8f && 1 > thornAttackTime) // 먼저 경고 원 출력  , 플레이어 위치로
	{
		if (isShow == false)
		{
			tempX = _testPlayerptr->GetComponent<dod::Transform>()->position.x;
			tempY = _testPlayerptr->GetComponent<dod::Transform>()->position.y;
			isShow = true;
		}
		_thornWarningObject->thornTransform->position.x = tempX;
		_thornWarningObject->thornTransform->position.y = tempY;
		_thornWarningObject->Enable();

	}
	else if (thornAttackTime > 1.2f && 2 > thornAttackTime) // 원의 위치로 출력 , 이렇게하면 따라올듯
	{
		if (isSoundCreateSecend == false)
		{
			engineptr->soundManager->Sound_CreateSFXSound(SOUND_PATH(SFX\\Boss_Skill_2.ogg), dod::BOSS_ATTACK_SUNKEN_SECOND_SFX); //가시 출현
			isSoundCreateSecend = true;
		}
		if (isSoundPlaySecend == false)
		{
			engineptr->soundManager->Sound_PlaySound(dod::BOSS_ATTACK_SUNKEN_SECOND_SFX);
			isSoundPlaySecend = true;
		}

		_thornWarningObject->Disable();
		_thornObject->thornTransform->position.x = _thornWarningObject->thornTransform->position.x;
		_thornObject->thornTransform->position.y = _thornWarningObject->thornTransform->position.y;
		_thornObject->Enable();
	}
	else if (thornAttackTime > 2.8f && thornAttackTime <= 2.9f)
	{
		_thornObject->GetComponent<dod::Transform>()->position.y = 3000.f;
	}
	else if (thornAttackTime > 2.9f)
	{
		_thornObject->Disable();
		thornAttackTime = 0;
		isShow = false;
		isSoundPlayFirst = false;
		isSoundPlaySecend = false;
		_eState = dod::eBossState::BOSSIDLE;

		_pBossSprite->ChangeCurrentAnimationIndex(0);
		_pArmLSprite->ChangeCurrentAnimationIndex(0);
		_pArmRSprite->ChangeCurrentAnimationIndex(0);
	}
}

void Boss::BossAttack_Stone()
{
	static double normalAttackTime = 0;
	static bool isSoundCreateFirst = false;
	static bool isSoundCreateSecend = false;
	static bool isSoundCreateThird = false;
	static bool isSoundPlayFirst = false;
	static bool isSoundPlaySecend = false;
	static bool isSoundPlayThird = false;

	normalAttackTime += engineptr->timer.GetDeltaTime();

	if (normalAttackTime < 2.5f)
	{
		for (int i = 0; i < 6; i++) // 6개 활성화
		{
			_stoneObject[i]->Enable();
			if (isSoundCreateFirst == false)
			{
				engineptr->soundManager->Sound_CreateSFXSound(SOUND_PATH(SFX\\Boss_Stone_1.ogg), dod::BOSS_ATTACK_STONE_FIRST_SFX); // 돌이 생기는 소리
				isSoundCreateFirst = true;
			}
			if (isSoundPlayFirst == false)
			{
				engineptr->soundManager->Sound_PlaySound(dod::BOSS_ATTACK_STONE_FIRST_SFX);
				isSoundPlayFirst = true;
			}

			if (1 < normalAttackTime)
			{
				_stoneObject[i]->StoneMove();
				if (isSoundCreateThird == false)
				{
					engineptr->soundManager->Sound_CreateSFXSound(SOUND_PATH(SFX\\Boss_Stone_Hit.ogg), dod::BOSS_ATTACK_STONE_SECOND_SFX);
					isSoundCreateThird = true;
				}
				if (isSoundPlayThird == false)
				{
					engineptr->soundManager->Sound_PlaySound(dod::BOSS_ATTACK_STONE_SECOND_SFX);
					isSoundPlayThird = true;
				}
			}
		}
	}

	if (normalAttackTime > 2.5f && normalAttackTime < 2.6f)
	{
		for (int i = 0; i < 6; i++) // 6개 비활성화
		{
			_stoneObject[i]->Disable();
		}
		if (isSoundCreateSecend == false)
		{
			engineptr->soundManager->Sound_CreateSFXSound(SOUND_PATH(SFX\\Boss_Stone_Shoot.ogg), dod::BOSS_ATTACK_STONE_THIRD_SFX);
			isSoundCreateSecend = true;
		}
		if (isSoundPlaySecend == false)
		{
			engineptr->soundManager->Sound_PlaySound(dod::BOSS_ATTACK_STONE_THIRD_SFX);
			isSoundPlaySecend = true;
		}
	}
	else if (normalAttackTime > 2.5f)
	{
		for (int i = 0; i < 6; i++) // 좌표 재 설정
		{
			_stoneObject[i]->StoneTransform(i);
		}
		isSoundPlayFirst = false;
		isSoundPlaySecend = false;
		isSoundPlayThird = false;
		_eState = dod::eBossState::BOSSIDLE;
		normalAttackTime = 0;

		_pBossSprite->ChangeCurrentAnimationIndex(0);
		_pArmLSprite->ChangeCurrentAnimationIndex(0);
		_pArmRSprite->ChangeCurrentAnimationIndex(0);
	}
}

void Boss::BossAttack_Swing(int _swingAttackNumber)
{
	if (!_isInitAttackSwing)
	{
		if (_swingAttackNumber == 2)
		{
			_pBossSprite->SetImageIndex(_bossSpriteMap.find(dod::eBossPattern::ATTACKL)->second);
			_pArmLSprite->SetImageIndex(_bossArmRMap.find(dod::eBossPattern::ATTACKL)->second);
			_pArmRSprite->SetImageIndex(_bossArmLMap.find(dod::eBossPattern::ATTACKL)->second);		//if(isSoundPlayFirst == false)
		}
		else if (_swingAttackNumber == 3)
		{
			_pBossSprite->SetImageIndex(_bossSpriteMap.find(dod::eBossPattern::ATTACKR)->second);
			_pArmLSprite->SetImageIndex(_bossArmRMap.find(dod::eBossPattern::ATTACKR)->second);
			_pArmRSprite->SetImageIndex(_bossArmLMap.find(dod::eBossPattern::ATTACKR)->second);
		}

		_pBossSprite->ChangeCurrentAnimationIndex(0);
		_pArmLSprite->ChangeCurrentAnimationIndex(0);
		_pArmRSprite->ChangeCurrentAnimationIndex(0);
		_isInitAttackSwing = true;
	}
	if (_swingAttackNumber == 2) // 왼쪽 스윙
	{
		_bossArmL->BossSwingAttackL();
	}
	else if (_swingAttackNumber == 3) // 오른쪽 스윙
	{
		_bossArmR->BossSwingAttackR();
	}
}

void Boss::BossAttack_Breath()
{
	static double breathTime = 0;
	static bool isSoundCreateFirst = false;
	static bool isSoundCreateSecend = false;
	static bool isSoundPlayFirst = false;
	static bool isSoundPlaySecend = false;
	breathTime += engineptr->timer.GetDeltaTime();

	_pBossSprite->SetImageIndex(_bossSpriteMap.find(dod::eBossPattern::BREATHE)->second);
	_pArmLSprite->SetImageIndex(_bossArmRMap.find(dod::eBossPattern::BREATHE)->second);
	_pArmRSprite->SetImageIndex(_bossArmLMap.find(dod::eBossPattern::BREATHE)->second);

	if (isSoundCreateFirst == false)  // 브레스 뿜기 전
	{
		engineptr->soundManager->Sound_CreateSFXSound(SOUND_PATH(SFX\\Boss_Inhale.ogg), dod::BOSS_ATTACK_BREATH_FIRST_SFX);
		isSoundCreateFirst = true;
	}
	if (isSoundPlayFirst == false)
	{
		engineptr->soundManager->Sound_PlaySound(dod::BOSS_ATTACK_BREATH_FIRST_SFX);
		isSoundPlayFirst = true;
	}

	_breathObject->breathTransform->position.y = 200;
	if (1 < breathTime && breathTime < 3)
	{
		if (isSoundCreateSecend == false)
		{
			engineptr->soundManager->Sound_CreateSFXSound(SOUND_PATH(SFX\\Boss_Exhale.ogg), dod::BOSS_ATTACK_BREATH_SECOND_SFX);
			isSoundCreateSecend = true;
		}
		if (isSoundPlaySecend == false)
		{
			engineptr->soundManager->Sound_PlaySound(dod::BOSS_ATTACK_BREATH_SECOND_SFX);
			isSoundPlaySecend = true;
		}

		_breathObject->Enable();
	}
	else if (breathTime > 3.1f)
	{
		isSoundPlayFirst = false;
		isSoundPlaySecend = false;
		_eState = dod::eBossState::BOSSIDLE;
		breathTime = 0;

		_pBossSprite->ChangeCurrentAnimationIndex(0);
		_pArmLSprite->ChangeCurrentAnimationIndex(0);
		_pArmRSprite->ChangeCurrentAnimationIndex(0);
	}
}

void Boss::BossDead() // 게임 종료
{

}

void Boss::AdjustHP(int damage)
{
	static bool isSoundPlay = false;
	static bool isSoundCreate = false;

	if (isSoundCreate == false)
	{
		engineptr->soundManager->Sound_CreateSFXSound(SOUND_PATH(SFX\\Boss_Hit.ogg), dod::BOSS_NORMAL_HIT_SFX);
		engineptr->soundManager->Sound_CreateSFXSound(SOUND_PATH(SFX\\Boss_5_Cost_Hit.ogg), dod::BOSS_SKILL_HIT_SFX);
		isSoundCreate = true;
	}
	if (damage == 15)
	{
		engineptr->soundManager->Sound_PlaySound(dod::BOSS_SKILL_HIT_SFX);
	}
	else
	{
		engineptr->soundManager->Sound_PlaySound(dod::BOSS_NORMAL_HIT_SFX);
	}

	hP -= damage;
}
