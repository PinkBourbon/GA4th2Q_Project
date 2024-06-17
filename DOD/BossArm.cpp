#include "BossArm.h"
#include "GameEngine.h"
#include "Path.h"
#include "RenderSprite.h"

BossArm::BossArm() :
	_eState{ 0 },
	_bossArmDeltaTime{ 0 },
	_deltanum{ 0 },
	bossArmTransform{ 0 },
	_pArmLRenderComponenet{ 0 },
	_stoneObject{ 0 },
	_bossptr{ 0 }, _bossPattern{ dod::eBossPattern::IDLE },
	_bossArmCoverage{ nullptr },
	_physicsRectArm{ nullptr }
{
	attackspeed = 45;
}

BossArm::~BossArm()
{

}

void BossArm::OnCreate()
{
	// 	_pArmLSprite = new dod::RenderSprite(0, 0, 6);	
	// 	_bossArmLMap.insert({ eBossArmLPattern::IDLE,_pArmLSprite->PushBackImageDataVector(IMAGE_PATH(Sprite\\Boss\\Sheet\\Boss_ArmL_Idle_Sheet.png)) });
	// 	_bossArmLMap.insert({ eBossArmLPattern::ATTACK,_pArmLSprite->PushBackImageDataVector(IMAGE_PATH(Sprite\\Boss\\Sheet\\Boss_ArmL_Attack_Sheet.png)) });
	// 	_bossArmLMap.insert({ eBossArmLPattern::ATTACKL,_pArmLSprite->PushBackImageDataVector(IMAGE_PATH(Sprite\\Boss\\Sheet\\Boss_ArmL_AttackL_Sheet.png)) });
	// 	_bossArmLMap.insert({ eBossArmLPattern::ATTACKR,_pArmLSprite->PushBackImageDataVector(IMAGE_PATH(Sprite\\Boss\\Sheet\\Boss_ArmL_AttackR_Sheet.png)) });
	// 	_bossArmLMap.insert({ eBossArmLPattern::BREATHE,_pArmLSprite->PushBackImageDataVector(IMAGE_PATH(Sprite\\Boss\\Sheet\\Boss_ArmL_Breathe_Sheet.png)) });
	// 	AddComponent(_pArmLSprite);
}

void BossArm::OnEnable()
{
	// RegisterGameObject�� �� ������Ʈ�� ����� ���� main ���� �� ����
}

void BossArm::OnUpdate()
{

}

void BossArm::OnDisable()
{

}

void BossArm::OnRelease()
{

}

void BossArm::BossParentSet(Boss* bossptr)
{
	_bossptr = bossptr;
}

void BossArm::BossInitalation()
{
	_pArmLRenderComponenet = GetComponent<dod::RenderComponent>();
	_bossArmDeltaTime = engineptr->timer.GetDeltaTime();
	bossArmTransform = GetComponent<dod::Transform>();


	_bossArmCoverage = engineptr->RegisterGameObject<BossArmCoverage>(L"BossArmCoverage");
	_physicsRectArm = new dod::Rectangle(100.f, 150.f);
	_bossArmCoverage->AddComponent(_physicsRectArm);
	_bossArmCoverage->AddComponent(new dod::RenderRect(0, 0, 200, 300, 0));
	_bossArmCoverage->GetComponent<dod::Transform>();
	_bossArmCoverage->BossArmCoverageInitalation();
	_bossArmCoverage->bossArmCoverageTransform->position.x = 0;
	_bossArmCoverage->bossArmCoverageTransform->position.y = 0;
}

void BossArm::BossArmIdle()
{

	static double idleTime = 0;

	idleTime += engineptr->timer.GetDeltaTime();
	static bool isBodyUp = false;


	// RegisterGameObject�� �� ������Ʈ�� ����� ���� main ���� �� ����

	if (idleTime < 1 && isBodyUp == false)  // �����̴� �κ�
	{
		bossArmTransform->position.y += 0.5f;
	}
	else if (idleTime > 1 && isBodyUp == false) // ������ ��ȯ�ϴ� �κ�
	{
		isBodyUp = true;
		idleTime = 0;
	}

	if (idleTime < 1 && isBodyUp == true)
	{
		bossArmTransform->position.y -= 0.5f;
	}
	else if (idleTime > 1 && isBodyUp == true)
	{
		isBodyUp = false;
		idleTime = 0;
	}
}

void BossArm::BossSwingAttackL()
{

	static double swingTime = 0;
	static bool leftSwing = false;
	static bool isSoundCreateSecend = false;
	static bool isSoundPlay = false;
	swingTime += engineptr->timer.GetDeltaTime();


	if (leftSwing == false)
	{
		_bossArmCoverage->bossArmCoverageTransform->position.x = 300;
		_bossArmCoverage->bossArmCoverageTransform->position.y = 500;
		_bossArmCoverage->bossArmCoverageTransform->scale.x = 1;
		_bossArmCoverage->bossArmCoverageTransform->scale.y = 2;
		_physicsRectArm->SetHalfHeight(300.f);
		leftSwing = true;
	}
	if (swingTime < 1.2f)
	{
		_bossptr->_bossArmLWarningObject->Enable();
	}
	else if (swingTime > 1.2f && swingTime < 2.2f)
	{
		_bossptr->_bossArmLWarningObject->Disable();
		_bossArmCoverage->Enable();
		_bossArmCoverage->bossArmCoverageTransform->position.x += 10 * (float)engineptr->timer.GetDeltaTime() * attackspeed;
		if (isSoundCreateSecend == false)
		{
			engineptr->soundManager->Sound_CreateSFXSound(SOUND_PATH(SFX\\Boss_Skill_3.ogg), dod::BOSS_ATTACK_SWING_FIRST_SFX); // �ȿ� ���� ���̺��� ������, �μ����� �Ҹ�
			isSoundCreateSecend = true;
		}

		if (isSoundPlay == false)
		{
			engineptr->soundManager->Sound_PlaySound(dod::BOSS_ATTACK_SWING_FIRST_SFX);
			isSoundPlay = true;
		}
		//bossArmLTransform->rotation += 0.5f;
		//bossArmLTransform->position.y -= 10;

	}
	else if (swingTime > 2.2f && swingTime < 2.3f)
	{
		_bossArmCoverage->Disable();
	}
	else
	{
		swingTime = 0;

		_bossArmCoverage->bossArmCoverageTransform->position.x = 0;
		_bossArmCoverage->bossArmCoverageTransform->position.y = 0;

		_bossArmCoverage->bossArmCoverageTransform->scale.x = 1;
		_bossArmCoverage->bossArmCoverageTransform->scale.y = 1;
		_physicsRectArm->SetHalfHeight(150.f);

		_bossArmCoverage->bossArmCoverageTransform->rotation = 0;

		leftSwing = false;
		isSoundPlay = false;
		_bossptr->_eState = dod::eBossState::BOSSIDLE;
		_bossptr->_isInitAttackSwing = false;
	}
}

void BossArm::BossSwingAttackR()
{

	static double swingTime = 0;
	static bool isSoundCreateSecend = false;
	static bool isSoundPlay = false;

	swingTime += engineptr->timer.GetDeltaTime();
	static bool leftSwing = false;

	if (leftSwing == false)
	{
		_bossArmCoverage->bossArmCoverageTransform->position.x = 1600;
		_bossArmCoverage->bossArmCoverageTransform->position.y = 500;
		_bossArmCoverage->bossArmCoverageTransform->scale.x = 1;
		_bossArmCoverage->bossArmCoverageTransform->scale.y = 2;
		_physicsRectArm->SetHalfHeight(300.f);
		leftSwing = true;
	}

	if (swingTime < 1.2f)
	{
		_bossptr->_bossArmRWarningObject->Enable();
	}
	else if (swingTime > 1.2f && swingTime < 2.2f)
	{
		_bossptr->_bossArmRWarningObject->Disable();
		_bossArmCoverage->Enable();
		_bossArmCoverage->bossArmCoverageTransform->position.x -= 10 * (float)engineptr->timer.GetDeltaTime() * attackspeed;
		//bossArmLTransform->rotation -= 0.5f;
		//bossArmLTransform->position.y -= 10;
		if (isSoundCreateSecend == false)
		{
			engineptr->soundManager->Sound_CreateSFXSound(SOUND_PATH(SFX\\Boss_Skill_3.ogg), dod::BOSS_ATTACK_SWING_FIRST_SFX); // �ȿ� ���� ���̺��� ������, �μ����� �Ҹ�
			isSoundCreateSecend = true; // �ι� ������� �ǽɵ����� �� ���ư��� �ϴ� ����
		}

		if (isSoundPlay == false)
		{
			engineptr->soundManager->Sound_PlaySound(dod::BOSS_ATTACK_SWING_FIRST_SFX);
			isSoundPlay = true;
		}

	}
	else if (swingTime > 2.2f && swingTime < 2.3f)
	{
		_bossArmCoverage->Disable();
	}
	else
	{
		swingTime = 0;

		_bossArmCoverage->bossArmCoverageTransform->position.x = 0;
		_bossArmCoverage->bossArmCoverageTransform->position.y = 0;

		_bossArmCoverage->bossArmCoverageTransform->scale.x = 1;
		_bossArmCoverage->bossArmCoverageTransform->scale.y = 1;
		_physicsRectArm->SetHalfHeight(150.f);

		_bossArmCoverage->bossArmCoverageTransform->rotation = 0;
		leftSwing = false;

		_bossptr->_eState = dod::eBossState::BOSSIDLE;
		_bossptr->_isInitAttackSwing = false;
	}
}

dod::eBossPattern BossArm::ReturnBossPattern()
{
	return _bossPattern;
}

