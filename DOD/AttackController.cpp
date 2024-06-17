#include "AttackController.h"
#include "TestAttack.h"
#include "TestPlayer.h"
#include "GameEngine.h"
#include "Transform.h"
#include "KeyManager.h"
#include "UIContoller.h"

#include <vector>

AttackController::AttackController()
	:_attackPool()
	, _attackIndex(0), _uiController()
	, _isSkilled(false), _player()
{

}

AttackController::~AttackController()
{

}

void AttackController::OnCreate()
{
	for (int i = 0; i < 5; i++)
	{
		// ���� ����
		_attackPool[i] = engineptr->RegisterGameObject<TestAttack>(L"Attack");
	}

	// Ű ������Ʈ ���
	dod::KeyComponent* keyComponent = new dod::KeyComponent();
	AddComponent(keyComponent);
	keyComponent->onKeyDown = [](const dod::KeyInfo& keyinfo, const dod::GameObject& thisObject)
	{
		AttackController* thisptr = (AttackController*)(thisObject.engineptr->GetObjectptr(L"AttackController"));

		if (keyinfo.code == dod::eButtonCode::PAD_DPAD_A)
		{
			for (int i = 0; i < 5; i++)
			{
				if (thisptr->_attackPool[i]->_isShooting == false)
				{
					thisptr->_attackPool[i]->_isShooting = true;
					thisptr->_attackPool[i]->_attackType = thisptr->DecideAttackType();
					if (thisptr->_attackPool[i]->_attackType == AutoAttack)
					{
						thisptr->_attackPool[i]->EnableAttack();
					}
					else if (thisptr->_attackPool[i]->_attackType == None)
					{
						thisptr->_attackPool[i]->_isShooting = false;
						break;
					}
					else
					{
						thisptr->_attackPool[i]->EnableSkill(thisptr->_attackPool[i]->_attackType);
					}
					break;
				}
			}
		}
	};
	return;
}

void AttackController::OnEnable()
{

}

void AttackController::OnUpdate()
{
	static double time = 0.0;

	if (_isSkilled)
	{
		time += engineptr->timer.GetFrameTime();
		if (time < 3.0)
		{
			engineptr->timer.SetTimeScale(0.3f);
		}
		else
		{
			engineptr->timer.SetTimeScale(1.0f);
			time = 0.0;
			_isSkilled = false;
		}
	}
}

void AttackController::OnDisable()
{

}

void AttackController::OnRelease()
{

}

eAttackType AttackController::DecideAttackType()
{
	_player = (TestPlayer*)(engineptr->GetObjectptr(L"Tester"));
	_uiController = (UIController*)(engineptr->GetObjectptr(L"UIController"));

	if (_player->GetDiceNumber(0) == 0)
	{
		return None;
	}

	std::vector<int> mydice;
	mydice.reserve(DICE_CAPCITY);
	for (int i = 0; i < DICE_CAPCITY; i++)
	{
		mydice.push_back(_player->GetDiceNumber(i));
	}

	int diceCount = 0;
	// �������� Ž���� ��ų �ֻ����� �ٲ���
	for (int i = 0; i < 5; i++)
	{
		int skillDice = _uiController->GetSkillDiceNumber(i);
		if (skillDice == 0 || skillDice == 7)
		{
			continue;
		}

		// �� �� ������ ��ų �ֻ��� �ϳ��� Ȯ��.
		bool hasDice = false;
		for (int j = 0; j < DICE_CAPCITY; j++)
		{
			if (skillDice == mydice[j])
			{
				hasDice = true;
				mydice[j] = 0;
				diceCount++;
				break;
			}
		}

		// ��ų�ֻ����� �������� �ʴ´ٸ� �Ϲݰ���
		if (hasDice == false)
		{
			return AutoAttack;	// �� ��� �Ϲݰ���
		}
	}

	for (int i = 0; i < DICE_CAPCITY; ++i)
	{
		_player->SetDiceNumber(i, mydice[i]);
	}
	switch (diceCount)
	{
		case 0:
		{
			return AutoAttack;
		}
		break;
		case 3:
		{
			_player->DiceCut();
			_player->DiceCut();
			_player->DiceCut();
			return SkillAttack3;
		}
		case 4:
		{
			_player->DiceCut();
			_player->DiceCut();
			_player->DiceCut();
			_player->DiceCut();
			return SkillAttack4;
		}
		case 5:
		{
			_player->DiceCut();
			_player->DiceCut();
			_player->DiceCut();
			_player->DiceCut();
			_player->DiceCut();
			return SkillAttack5;
		}
		default:
		{
			Assert(false, "�ùٸ��� ���� ��ų����Ʈ ��Ī");
			return None;
		}
	}
}
