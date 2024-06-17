#include <random>
#include <cmath>

#include "UIContoller.h"
#include "Inventory.h"
#include "TestPlayer.h"
#include "Curtain_side.h"
#include "GameEngine.h"
#include "Transform.h"
#include "SkillDice.h"
#include "DiceController.h"
#include "TestDice.h"
#include "Path.h"
#include "RenderSprite.h"


UIController::UIController()
	: _inventory(), _player(), _curtain(), _skillDice()
	, _diceCount(0), _isCurtainMove(false), _isReRoll(false)
	, _Leveractioned(false), uiPlayerSkillLever(), _pSpritePrint()
{

}

UIController::~UIController()
{

}

void UIController::OnCreate()
{
	// �÷��̾� ������ �޾ƿ���
	_player = (TestPlayer*)(engineptr->GetObjectptr(L"Tester"));

	// �κ��丮 �ʱ�ȭ
	for (int i = 0; i < DICE_CAPCITY; i++)
	{
		_inventory[i] = engineptr->RegisterGameObject<Inventory>(L"Inventory");
		_inventory[i]->stateNumber = _player->_diceNumber[i];
		dod::Transform* invenTransform = _inventory[i]->GetComponent<dod::Transform>();
		invenTransform->position.x = 90.0f * i + 726.0f;
		invenTransform->position.y = 973;
	}

	// ��ų���̽� �ʱ�ȭ
	for (int i = 0; i < 5; i++)
	{
		_skillDice[i] = engineptr->RegisterGameObject<SkillDice>(L"SkillDice");
		_skillDice[i]->stateNumber = _player->_diceNumber[i];
		dod::Transform* skillDiceTransform = _skillDice[i]->GetComponent<dod::Transform>();
		skillDiceTransform->position.x = 84.0f * i + 1433.0f;
		skillDiceTransform->position.y = 950;
	}

	// Ŀư �ʱ�ȭ
	for (int i = 0; i < 2; i++)
	{
		_curtain[i] = engineptr->RegisterGameObject<Curtain_side>(L"Curtain_Side");
		dod::Transform* curtainTransform = _curtain[i]->GetComponent<dod::Transform>();
		curtainTransform->scale.x = 1.4f;
		curtainTransform->scale.y = 1.6f;
		curtainTransform->position.y = 480.f;
		curtainTransform->position.x = 320.f + 1115.f * i;
		_curtain[i]->direction = -1 + (2 * i);
	}

	uiPlayerSkillLever = engineptr->RegisterGameObject<dod::GameObject>(L"Lever");
	dod::RenderSprite* pUIPlayerSkillLeverSprite = new dod::RenderSprite(0, 0, 5);
	_pSpritePrint = pUIPlayerSkillLeverSprite;
	_UIPlayerSkillLeverSpriteMap.insert({ 0,pUIPlayerSkillLeverSprite->PushBackImageDataVector(IMAGE_PATH(UI\\Roulette\\Labor_Sheet.png)) });
	_UIPlayerSkillLeverSpriteMap.insert({ 1,pUIPlayerSkillLeverSprite->PushBackImageDataVector(IMAGE_PATH(UI\\Roulette\\Labor_Sheet_64X64.png)) });
	uiPlayerSkillLever->AddComponent(pUIPlayerSkillLeverSprite);
	uiPlayerSkillLever->GetComponent < dod::Transform >()->scale.x = 2.5f;
	uiPlayerSkillLever->GetComponent < dod::Transform >()->scale.y = 3.0f;
	uiPlayerSkillLever->GetComponent < dod::Transform >()->position.x = 1868;
	uiPlayerSkillLever->GetComponent < dod::Transform >()->position.y = 940;
}

void UIController::OnEnable()
{
	// �÷��̾� ������ �޾ƿ���
	_player = (TestPlayer*)(engineptr->GetObjectptr(L"Tester"));
	_diceCount = _player->_diceCount;

	// �κ��丮, ��ų���̽� enable
	for (int i = 0; i < DICE_CAPCITY; i++)
	{
		if (_player->_diceNumber[i] != 0)
		{
			_inventory[i]->Enable();
		}
	}
	for (int i = 0; i < 5; i++)
	{
		_skillDice[i]->Enable();
	}
	_curtain[0]->Enable();
	_curtain[1]->Enable();
	// ������ �� Ŀư ����
	_isCurtainMove = true;

	uiPlayerSkillLever->Enable();
}

void UIController::OnUpdate()
{


	_player = (TestPlayer*)(engineptr->GetObjectptr(L"Tester"));

	// �κ��丮�� ����
	for (int i = 0; i < DICE_CAPCITY; ++i)
	{
		if (i < _player->_diceCount)
		{
			_inventory[i]->stateNumber = _player->_diceNumber[i];
			if (_inventory[i]->objState == dod::eObjectState::OnDisable)
			{
				_inventory[i]->Enable();
			}
		}
		else
		{
			if (_inventory[i]->objState != dod::eObjectState::OnDisable)
			{
				_inventory[i]->stateNumber = 0;
				_inventory[i]->Disable();
			}
		}
	}

	// Ŀư�� ����
	double curtainTime = 0;
	if (_isCurtainMove == true)
	{
		curtainTime += engineptr->timer.GetDeltaTime();
		if (curtainTime < 3.0f)
		{
			_player->_controlable = false;
			for (int i = 0; i < 2; i++)
			{
				dod::Transform* curtainTransform = _curtain[i]->GetComponent<dod::Transform>();
				curtainTransform->scale.x -= 0.003f;
				curtainTransform->position.x += (_curtain[i]->direction * 1.15f);
			}
		}

		_player->_controlable = true;
		curtainTime = 0;
		_isCurtainMove = false;
	}

	// ��ų���̽��� ����
	if (_isReRoll == true)
	{
		static bool isSoundCreate = false;
		if (isSoundCreate == false)
		{
			engineptr->soundManager->Sound_CreateSFXSound(SOUND_PATH(SFX\\Slotmachine.wav), dod::SLOTMACHINE_STAT_SFX);
			isSoundCreate = true;
		}

		static bool isSoundPlay = false;
		if (isSoundPlay == false)
		{
			engineptr->soundManager->Sound_PlaySound(dod::SLOTMACHINE_STAT_SFX);
			isSoundPlay = true;
		}

		static bool isReadyDice = false;
		if (!isReadyDice)
		{
			for (int i = 0; i < 5; i++)
			{
				_skillDice[i]->MatchNumberImage(0);
			}
			ReRollSkill();
			isReadyDice = true;
		}

		_pSpritePrint->SetImageIndex(_UIPlayerSkillLeverSpriteMap.find(0)->second);

		static double rouletteDelayTime = 0;
		rouletteDelayTime += engineptr->timer.GetDeltaTime();
		if (rouletteDelayTime > 0.0f && rouletteDelayTime <= 0.6f)
		{
			_pSpritePrint->SetImageIndex(_UIPlayerSkillLeverSpriteMap.find(1)->second);
		}
		else if (rouletteDelayTime > 1.5f && rouletteDelayTime <= 2.0f)
		{
			_pSpritePrint->SetImageIndex(_UIPlayerSkillLeverSpriteMap.find(0)->second);
			_skillDice[0]->MatchNumberImage();
		}
		else if (rouletteDelayTime > 2.0f && rouletteDelayTime <= 2.5f)
		{
			_skillDice[0]->MatchNumberImage();
			_skillDice[1]->MatchNumberImage();
		}
		else if (rouletteDelayTime > 2.5f && rouletteDelayTime <= 3.0f)
		{
			_skillDice[0]->MatchNumberImage();
			_skillDice[1]->MatchNumberImage();
			_skillDice[2]->MatchNumberImage();
		}
		else if (rouletteDelayTime > 3.0f && rouletteDelayTime <= 3.5f)
		{
			_skillDice[0]->MatchNumberImage();
			_skillDice[1]->MatchNumberImage();
			_skillDice[2]->MatchNumberImage();
			_skillDice[3]->MatchNumberImage();
		}
		else if (rouletteDelayTime > 3.5f)
		{
			_pSpritePrint->SetImageIndex(_UIPlayerSkillLeverSpriteMap.find(0)->second);
			_skillDice[0]->MatchNumberImage();
			_skillDice[1]->MatchNumberImage();
			_skillDice[2]->MatchNumberImage();
			_skillDice[3]->MatchNumberImage();
			_skillDice[4]->MatchNumberImage();
			rouletteDelayTime = 0;
			isSoundPlay = false;
			_isReRoll = false;

			isReadyDice = false;
			return;
		}

	}
}

void UIController::OnDisable()
{
	for (int i = 0; i < DICE_CAPCITY; i++)
	{
		_inventory[i]->Disable();
	}

	for (int i = 0; i < 2; i++)
	{
		_curtain[i]->Disable();
	}

	// ��ų���̽� �ʱ�ȭ
	for (int i = 0; i < 5; i++)
	{
		_skillDice[i]->Disable();
	}

	uiPlayerSkillLever->Disable();
}

void UIController::OnRelease()
{

}

void UIController::ReRollSkill()
{
	std::random_device rd;

	// 3~5�� ������ � �ɷ� ���� ����
	int skillSize = 0;
	std::mt19937 gen(rd());
	std::uniform_int_distribution<int> dis(3, 5);
	skillSize = dis(gen);

	int diceIndexArray[5] = { -1, -1, -1, -1, -1 };

	// 11���� �ֻ��� �� � ���� �������� ����
	for (int i = 0; i < skillSize; i++)
	{
		std::mt19937 gen2(rd());
		std::uniform_int_distribution<int> dis2(0, 10);
		diceIndexArray[i] = dis2(gen2);
		for (int j = 0; j < i; j++)
		{
			if (diceIndexArray[j] == diceIndexArray[i])
			{
				i--;
				break;
			}
		}
	}

	DiceController* diceController = (DiceController*)(engineptr->GetObjectptr(L"DiceController"));

	for (int i = 0; i < 5; i++)
	{
		if (diceIndexArray[i] != -1)
		{
			_skillDice[i]->stateNumber = diceController->_dicePool[diceIndexArray[i]]->GetDiceNumber();
		}
		else
		{
			_skillDice[i]->stateNumber = 7;
		}
	}
	for (int i = 0; i < 5; i++)
	{
		for (int j = 4; j > i; j--)
		{
			if (_skillDice[j - 1]->stateNumber > _skillDice[j]->stateNumber)
			{
				int temp = _skillDice[j - 1]->stateNumber;
				_skillDice[j - 1]->stateNumber = _skillDice[j]->stateNumber;
				_skillDice[j]->stateNumber = temp;
			}
		}
	}
	//_isReRoll = false;
}

void UIController::SetReRollState(bool rollstate)
{
	_isReRoll = rollstate;
}

int UIController::GetSkillDiceNumber(int index)
{
	return _skillDice[index]->stateNumber;
}
