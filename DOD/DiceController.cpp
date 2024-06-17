#include "DiceController.h"
#include "TestDice.h"
#include "GameEngine.h"
#include "Transform.h"
#include "UIContoller.h"
#include "TestPlayer.h"

DiceController::DiceController()
	:_dicePool(), _uiController(), _player(), _rerollBySkill(false)
{

}

DiceController::~DiceController()
{

}

void DiceController::OnCreate()
{
	for (int i = 0; i < 11; i++)
	{
		//주사위 생성
		_dicePool[i] = engineptr->RegisterGameObject<TestDice>(L"Dice");
		dod::Transform* diceTransform = _dicePool[i]->GetComponent<dod::Transform>();


		switch (i)
		{

			case 0:
			{
				diceTransform->position.x = 240.f;
				diceTransform->position.y = 430.f;
			}
			break;
			case 1:
			{
				diceTransform->position.x = 945.f;
				diceTransform->position.y = 440.f;
			}
			break;
			case 2:
			{
				diceTransform->position.x = 1500.f;
				diceTransform->position.y = 435.f;
			}
			break;
			case 3:
			{
				diceTransform->position.x = 1700.f;
				diceTransform->position.y = 510.f;
			}
			break;
			case 4:
			{
				diceTransform->position.x = 335.f;
				diceTransform->position.y = 590.f;
			}
			break;
			case 5:
			{
				diceTransform->position.x = 740.f;
				diceTransform->position.y = 600.f;
			}
			break;
			case 6:
			{
				diceTransform->position.x = 1145.f;
				diceTransform->position.y = 590.f;
			}
			break;
			case 7:
			{
				diceTransform->position.x = 1550.f;
				diceTransform->position.y = 600.f;
			}
			break;
			case 8:
			{
				diceTransform->position.x = 400.f;
				diceTransform->position.y = 760.f;
			}
			break;
			case 9:
			{
				diceTransform->position.x = 650.f;
				diceTransform->position.y = 755.f;
			}
			break;
			case 10:
			{
				diceTransform->position.x = 1365.f;
				diceTransform->position.y = 750.f;
			}
			break;
		}
	}
_uiController = (UIController*)(engineptr->GetObjectptr(L"UIController"));
_player = (TestPlayer*)(engineptr->GetObjectptr(L"Tester"));
}

void DiceController::OnEnable()
{

	for (int i = 0; i < 11; i++)
	{
		_dicePool[i]->Enable();
	}
	//static bool isSoundPlay = false;
	//if (isSoundPlay == false)
	//{
	//	engineptr->soundManager->Sound_CreateSound("", dod::DICE_DROP_SFX);
	//	isSoundPlay = true;
	//}
	//engineptr->soundManager->Sound_PlaySound(dod::DICE_DROP_SFX);
	_uiController->SetReRollState(true);
}

void DiceController::OnUpdate()
{
	int disableCount = 0;
	for (int i = 0; i < 11; i++)
	{
		if (_dicePool[i]->objState == dod::eObjectState::OnDisable)
		{
			disableCount++;
		}
	}

	if (disableCount == 11)
	{
		for (int i = 0; i < 11; i++)
		{
			_dicePool[i]->Enable();
		}
		_uiController->SetReRollState(true);
	}

	if (_player->GetSpecialAttack() == true)
	{
		if (_rerollBySkill == false)
		{
			for (int i = 0; i < 11; i++)
			{
				if (_dicePool[i]->objState != dod::eObjectState::OnDisable)
				{
					_dicePool[i]->Disable();
				}
			}
			for (int i = 0; i < 11; i++)
			{
				_dicePool[i]->Enable();
			}
			_uiController->SetReRollState(true);
			_rerollBySkill = true;
		}
	}
	else
	{
		_rerollBySkill = false;
	}
}

void DiceController::OnDisable()
{
	for (int i = 0; i < 11; i++)
	{
		_dicePool[i]->Disable();
	}
}

void DiceController::OnRelease()
{

}
