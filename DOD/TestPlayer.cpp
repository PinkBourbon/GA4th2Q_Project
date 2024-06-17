#include "GameEngine.h"
#include "IComponent.h"
#include "RenderComponent.h"
#include "RenderText.h"
#include "RenderCircle.h"
#include "RenderRect.h"
#include "RenderSprite.h"
#include "KeyComponent.h"
#include "Transform.h"
#include "PhysicsComponent.h"
#include "Circle.h"
#include "Rectangle.h"
#include "TestDice.h"
#include "TitleScene.h"
#include "SceneManager.h"
#include "MainGame.h"
#include "KeyManager.h"
#include "TestPlayer.h"
#include "Vector3.h"
#include "SoundManager.h"
#include "StartCutScene.h"
#include "Path.h"
#include "BossArmCoverage.h"
#include "Boss.h"

TestPlayer::TestPlayer()
	: _diceSubsets(), _diceNumber(), _DiceNumberPrinter(), _HaveDicePrinter(), _isDied(false), _pNoPrinter(), _pYesPrinter()
	, _psceneManager(nullptr), _retryPicker(0), _initSpeed(300), _dashSpeed(600)
	, _subsetCount(0), HP(6), _dashed(false), _hitPlayer(false), _specialAttack(false), _hitable(true), _controlable(true), _pSpritePrint(nullptr)
	, _pYesPrinterSprite(nullptr), _pNoPrinterSprite(nullptr), _isDeadSoundPlay(false), _isDashCoolDown(false)
{
	_diceCount = 0;
	_speed = _initSpeed;
	_pRetryPrinter = nullptr;
	_pNamePrinter = nullptr;
	_pHPPrinter = nullptr;
	_direction.x = 0;
	_direction.y = 0;
	_direction.z = 0;
}

TestPlayer::~TestPlayer()
{
}

void TestPlayer::OnCreate()
{
	dod::KeyComponent* playerKeyComponenet = new dod::KeyComponent(); //
	AddComponent(playerKeyComponenet);								  // Ű������Ʈ�� �����ؼ� ����ϴ� ���

	// 	AddComponent(new dod::RenderCircle(16, 0));		  // ���� ������Ʈ�� �����ؼ� ����ϴ� ���

	_pSpritePrint = new dod::RenderSprite(0, 0, 5);
	_imageResourceManagerMap.insert({ ePlayerImageList::PLAYERMAIN, _pSpritePrint->PushBackImageDataVector(IMAGE_PATH(Sprite\\Player\\Sheet\\player_Idle.png)) });
	_imageResourceManagerMap.insert({ ePlayerImageList::PLAYERDIE, _pSpritePrint->PushBackImageDataVector(IMAGE_PATH(Sprite\\Player\\Sheet\\player_Death.png), 0.1) });
	_imageResourceManagerMap.insert({ ePlayerImageList::PLAYERATTACK, _pSpritePrint->PushBackImageDataVector(IMAGE_PATH(Sprite\\Player\\Sheet\\player_Attack.png)) });
	_imageResourceManagerMap.insert({ ePlayerImageList::PLAYERHIT, _pSpritePrint->PushBackImageDataVector(IMAGE_PATH(Sprite\\Player\\Sheet\\player_Hit.png), 0.06) });
	_imageResourceManagerMap.insert({ ePlayerImageList::PLAYERJUMP, _pSpritePrint->PushBackImageDataVector(IMAGE_PATH(Sprite\\Player\\Sheet\\player_Jump.png)) });
	_imageResourceManagerMap.insert({ ePlayerImageList::PLAYERWALK, _pSpritePrint->PushBackImageDataVector(IMAGE_PATH(Sprite\\Player\\Sheet\\player_Walk.png)) });
	_imageResourceManagerMap.insert({ ePlayerImageList::PLAYERROLLING, _pSpritePrint->PushBackImageDataVector(IMAGE_PATH(Sprite\\Player\\Sheet\\player_Roll.png)) });
	_imageResourceManagerMap.insert({ ePlayerImageList::PLAYERSKILL, _pSpritePrint->PushBackImageDataVector(IMAGE_PATH(Sprite\\Player\\Sheet\\player_Skill.png)) });
	AddComponent(_pSpritePrint);

	/// �̹��� ��Ʈ ���� ���
	//_pSpritePrint->SetImageIndex(_imageResourceManagerMap.find(ePlayerImageList::PLAYERWALK)->second); //�̿� ���� ������� �������ǹ� �ȿ� ���ٸ� �߰����ָ��

	dod::Rectangle* pPhysCom = new dod::Rectangle(48.f, 48.f);	//
	AddComponent(pPhysCom);											// ������ ������Ʈ�� ����ϴ� ���
	pPhysCom->onCollisionEnter = [](dod::GameObject* thisObject, dod::GameObject* otherObject)
	{
		TestPlayer* thisTestPlayer = (TestPlayer*)thisObject;
		int damage = 0;
		if (otherObject->objectName == L"BossArmCoverage")
		{
			damage = 2;
			thisTestPlayer->_hitPlayer = true;
			thisTestPlayer->_pSpritePrint->SetImageIndex(thisTestPlayer->_imageResourceManagerMap.find(ePlayerImageList::PLAYERHIT)->second);
		}
		else if (otherObject->objectName == L"ThornObject")
		{
			damage = 2;
			thisTestPlayer->_hitPlayer = true;
			thisTestPlayer->_pSpritePrint->SetImageIndex(thisTestPlayer->_imageResourceManagerMap.find(ePlayerImageList::PLAYERHIT)->second);
		}
		else if (otherObject->objectName == L"StoneObject")
		{
			damage = 1;
			thisTestPlayer->_hitPlayer = true;
			thisTestPlayer->_pSpritePrint->SetImageIndex(thisTestPlayer->_imageResourceManagerMap.find(ePlayerImageList::PLAYERHIT)->second);
		}
		else if (otherObject->objectName == L"GameButton")
		{
			((TestPlayer*)thisObject)->_psceneManager->gameScene = SceneManager::eGameScene::StartCutscene;
			((TestPlayer*)thisObject)->_psceneManager->title->Disabler();
			((TestPlayer*)thisObject)->_psceneManager->startCutScene->activecheck = true;
		}
		else if (otherObject->objectName == L"CreditButton")
		{
			((TestPlayer*)thisObject)->_psceneManager->gameScene = SceneManager::eGameScene::CreditScene;
			((TestPlayer*)thisObject)->_psceneManager->title->Disabler();
			((TestPlayer*)thisObject)->_psceneManager->startCutScene->activecheck = true;
		}
		else
		{
			return;
		}

		((TestPlayer*)thisObject)->AdjustHP(damage);
		return;
	};

	dod::Transform* transform = GetComponent<dod::Transform>();

	transform->position.x = 633.6f;
	transform->position.y = 501.6f;
	transform->scale.x = 3;	// �������� ����
	transform->scale.y = 3;	// +2
	for (int i = 0; i < 10; i++)	// ���� �ֻ��� �κ����� �ʱ�ȭ
	{
		_diceSubsets[i].Reset();
	}

	///�� ���� ���� ������Ʈ�� �������ִ� �κ�

	// ��Ʈ����â�� ����� ������Ʈ
	_pRetryPrinter = engineptr->RegisterGameObject<dod::GameObject>(L"RetryPrinter");
	dod::RenderSprite* retryPrinter = new dod::RenderSprite(0, 0, 8);
	retryPrinter->PushBackImageDataVector(IMAGE_PATH(UI\\popup\\retrypopup.png));
	_pRetryPrinter->GetComponent<dod::Transform>()->position.x = 960;
	_pRetryPrinter->GetComponent<dod::Transform>()->position.y = 540;
	_pRetryPrinter->AddComponent(retryPrinter);

	_pYesPrinter = engineptr->RegisterGameObject<dod::GameObject>(L"YesButton");
	_pYesPrinterSprite = new dod::RenderSprite(0, 0, 9);
	_yesButtonResourceManagerMap.insert({ 0, _pYesPrinterSprite->PushBackImageDataVector(IMAGE_PATH(UI\\popup\\retry_yes.png)) });
	_yesButtonResourceManagerMap.insert({ 1, _pYesPrinterSprite->PushBackImageDataVector(IMAGE_PATH(UI\\popup\\retry_yes_click.png)) });
	_pYesPrinter->GetComponent<dod::Transform>()->position.x = 960;
	_pYesPrinter->GetComponent<dod::Transform>()->position.y = 540;
	_pYesPrinter->AddComponent(_pYesPrinterSprite);

	_pNoPrinter = engineptr->RegisterGameObject<dod::GameObject>(L"NoButton");
	_pNoPrinterSprite = new dod::RenderSprite(0, 0, 9);
	_noButtonResourceManagerMap.insert({ 0, _pNoPrinterSprite->PushBackImageDataVector(IMAGE_PATH(UI\\popup\\retry_no.png)) });
	_noButtonResourceManagerMap.insert({ 1, _pNoPrinterSprite->PushBackImageDataVector(IMAGE_PATH(UI\\popup\\retry_no_click.png)) });
	_pNoPrinter->GetComponent<dod::Transform>()->position.x = 960;
	_pNoPrinter->GetComponent<dod::Transform>()->position.y = 540;
	_pNoPrinter->AddComponent(_pNoPrinterSprite);

	// ������Ʈ�� �̸��� ����� ������Ʈ
	_pNamePrinter = engineptr->RegisterGameObject<dod::GameObject>(L"namePrinter");
	_pNamePrinter->AddComponent(new dod::RenderText(0, -35, 0));
	_pNamePrinter->GetComponent<dod::Transform>()->SetParent(_pRetryPrinter->GetComponent<dod::Transform>());

	// ������Ʈ�� ü���� ����� ������Ʈ
	_pHPPrinter = engineptr->RegisterGameObject<dod::GameObject>(L"HPPrinter");
	_pHPPrinter->AddComponent(new dod::RenderText(0, -45, 0));
	_pHPPrinter->GetComponent<dod::Transform>()->SetParent(_pNamePrinter->GetComponent<dod::Transform>());


	///�� ���� �ݹ��Լ��� ���� �κ�
	// �ݹ��Լ��� ���� Ű������Ʈ�� �޾ƿ´�
	dod::KeyComponent* keyComponent = GetComponent<dod::KeyComponent>();
	keyComponent->onKeyDown = [this](const dod::KeyInfo& keyinfo, const dod::GameObject& thisObject) //���� Ű�� �����ٸ� ȣ��
	{
		TestPlayer* pTestplayer = (TestPlayer*)&thisObject;
		if (keyinfo.code == dod::eButtonCode::KEY_0)
		{
			pTestplayer->HP = 9999;
		}
		if (keyinfo.code == dod::eButtonCode::PAD_DPAD_B)
		{
			if (pTestplayer->_isDied == false && pTestplayer->_hitPlayer == false)
			{
				if (_isDashCoolDown == false)
				{
					pTestplayer->_dashed = true;
					pTestplayer->_pSpritePrint->SetImageIndex(pTestplayer->_imageResourceManagerMap.find(ePlayerImageList::PLAYERROLLING)->second);
					pTestplayer->_isDashCoolDown = true;
				}
			}
			else
			{
				if (pTestplayer->_retryPicker == 1) //Yes ��
				{
					pTestplayer->_psceneManager->inGame->Disabler();
					pTestplayer->_psceneManager->inGame->enterFirst = false;
					pTestplayer->_psceneManager->title->activecheck = true;
					pTestplayer->_isDied = false;
					pTestplayer->HP = 6;
					_isDeadSoundPlay = false;
				}
				else if (pTestplayer->_retryPicker == 2) //No ��
				{
					pTestplayer->_psceneManager->gameScene = SceneManager::eGameScene::Title;
					pTestplayer->_psceneManager->inGame->Disabler();
					pTestplayer->_psceneManager->title->activecheck = true;
					pTestplayer->_isDied = false;
					pTestplayer->HP = 6;
					_isDeadSoundPlay = false;
				}

				pTestplayer->engineptr->timer.SetTimeScale(1.0);
			}
		}
		if (keyinfo.code == dod::eButtonCode::PAD_L_JOYSTICKMOVE)
		{
			if (pTestplayer->_isDied == true)
			{
				for (int i = 0; i < 5; i++)
				{
					_diceNumber[i] = 0;
				}
				_diceCount = 0;
				if (keyinfo.x < -2000.0f)
				{
					pTestplayer->_retryPicker++;
					if (pTestplayer->_retryPicker > 2)
					{
						pTestplayer->_retryPicker = 1;
					}
				}

				else if (keyinfo.x > 2000.0f)
				{
					pTestplayer->_retryPicker--;
					if (pTestplayer->_retryPicker < 1)
					{
						pTestplayer->_retryPicker = 2;
					}
				}
			}
		}
	};

	keyComponent->onKeyStay = [](const dod::KeyInfo& keyinfo, const dod::GameObject& thisObject) //���� Űī �������¸� ȣ��
	{
		TestPlayer* pTestplayer = (TestPlayer*)&thisObject;
		if (pTestplayer->_controlable == true)
		{
			if (keyinfo.code == dod::eButtonCode::PAD_L_JOYSTICKMOVE)
			{
				pTestplayer->_direction.x = keyinfo.x / 32767.0f;
				pTestplayer->_direction.y = -keyinfo.y / 32767.0f;
				if (pTestplayer->_hitPlayer == false)
				{
					pTestplayer->_pSpritePrint->SetImageIndex(pTestplayer->_imageResourceManagerMap.find(ePlayerImageList::PLAYERWALK)->second);
				}


				auto transform = pTestplayer->GetComponent<dod::Transform>();
				if (pTestplayer->_direction.x < 0)
				{
					if (transform->scale.x > 0)
					{
						transform->scale.x *= -1.f;
					}
				}
				else
				{
					if (transform->scale.x < 0)
					{
						transform->scale.x *= -1.f;
					}
				}
				// 				dod::Transform* _transform = thisObject.GetComponent<dod::Transform>();
				// 
				// 				TestPlayer* ptr = (TestPlayer*)(thisObject._engineptr->GetObjectptr(L"Tester"));
				// 				_transform->position.x += tempVec.x * ptr->_speed;
				// 				_transform->position.y += tempVec.y * ptr->_speed;
			}
		}


	};

	keyComponent->onKeyUp = [](const dod::KeyInfo& keyinfo, const dod::GameObject& thisObject) //���� Űī �������¸� ȣ��
	{
		TestPlayer* pTestplayer = (TestPlayer*)&thisObject;
		if (pTestplayer->_controlable == false)
		{
			return;
		}

		if (keyinfo.code == dod::eButtonCode::PAD_L_JOYSTICKMOVE)
		{
			pTestplayer->_pSpritePrint->SetImageIndex(pTestplayer->_imageResourceManagerMap.find(ePlayerImageList::PLAYERMAIN)->second);
			pTestplayer->_direction.x = 0;
			pTestplayer->_direction.y = 0;
		}
	};
}

void TestPlayer::OnEnable()
{
	for (int i = 0; i < DICE_CAPCITY; i++)
	{
		_HaveDicePrinter[i]->Enable();
		_DiceNumberPrinter[i]->Enable();
		_diceNumber[i] = 0;
	}
	_diceCount = 0;
	dod::Transform* transform = GetComponent<dod::Transform>();		// Ʈ�������� �޾ƿɴϴ�.

	_dashed = false;
	_direction.x = 0;
	_direction.y = 0;
	_speed = _initSpeed;

	transform->position.x = 960.f;
	transform->position.y = 760.f;
	transform->scale.x = 3;	// �������� ����
	transform->scale.y = 3;	// +2
	_pSpritePrint->SetImageIndex(_imageResourceManagerMap.find(ePlayerImageList::PLAYERMAIN)->second);

	_diceCount = 0;
	for (auto& diceNum : _diceNumber)
	{
		diceNum = 0;
	}

	//_pRetryPrinter->Enable();
	_pNamePrinter->Enable();
	_pHPPrinter->Enable();
}

void TestPlayer::OnUpdate()
{
	static bool isSoundCreate = false;
	static bool isSoundCreateRetry = false;
	static bool isSoundPlayRetry = false;
	static bool isSoundPlaySelectY = false;
	static bool isSoundPlaySelectN = false;

	dod::Transform* transform = GetComponent<dod::Transform>();
	dod::PhysicsComponent* physics = GetComponent<dod::PhysicsComponent>();

	// ��ų ���� �ش� ��������Ʈ ���
	if (_specialAttack == true)
	{
		_pSpritePrint->SetImageIndex(_imageResourceManagerMap.find(ePlayerImageList::PLAYERSKILL)->second);
	}

	float deltaSpeed = (float)engineptr->timer.GetDeltaTime() * _speed;
	// �ӵ� ���
	if (fabs(_direction.x) < 0.1f)
	{
		_direction.x = 0;
	}
	if (fabs(_direction.y) < 0.1f)
	{
		_direction.y = 0;
	}

	physics->SetVelocity(_direction.x * deltaSpeed, _direction.y * deltaSpeed);
	if (isSoundCreateRetry == false) // 
	{
		engineptr->soundManager->Sound_CreateSFXSound(SOUND_PATH(SFX\\Retry_Yes.wav), dod::RETRY_UI_SELECT_SFX);
		engineptr->soundManager->Sound_CreateSFXSound(SOUND_PATH(SFX\\Retry_Popup.wav), dod::RETRY_UI_MAKE_SFX);
		isSoundCreateRetry = true;
	}

	//������Ʈ�� ��ġ�� ���
	if (HP <= 0)
	{
		if (isSoundCreate == false)
		{
			engineptr->soundManager->Sound_CreateSFXSound(SOUND_PATH(SFX\\Player_Death.ogg), dod::PLAYER_DEAD_SFX);

			isSoundCreate = true;
		}
		if (_isDeadSoundPlay == false)
		{
			engineptr->soundManager->Sound_PlaySound(dod::PLAYER_DEAD_SFX);
			engineptr->soundManager->Sound_PlaySound(dod::RETRY_UI_MAKE_SFX);
			_isDeadSoundPlay = true;
		}

		_isDied = true;
		_psceneManager->inGame->isSoundPlayStage = false;
		engineptr->timer.SetTimeScale(0.0f);
		_pRetryPrinter->Enable();
		_pYesPrinter->Enable();
		_pNoPrinter->Enable();
		//_bossArmCoverageL->Disable();
		//_bossArmCoverageR->Disable();

		// ���� �ֻ��� �ʱ�ȭ
		for (int i = 0; i < DICE_CAPCITY; i++)
		{
			_diceNumber[i] = 0;
		}
	}

	if (_retryPicker == 1)
	{
		if (isSoundPlaySelectY == false)
		{
			engineptr->soundManager->Sound_PlaySound(dod::RETRY_UI_SELECT_SFX);
			isSoundPlaySelectY = true;
			isSoundPlaySelectN = false;
		}
		_pYesPrinterSprite->SetImageIndex(_yesButtonResourceManagerMap.find(1)->second);
		_pNoPrinterSprite->SetImageIndex(_noButtonResourceManagerMap.find(0)->second);
	}

	else if (_retryPicker == 2)
	{
		if (isSoundPlaySelectN == false)
		{
			engineptr->soundManager->Sound_PlaySound(dod::RETRY_UI_SELECT_SFX);
			isSoundPlaySelectN = true;
			isSoundPlaySelectY = false;
		}
		_pYesPrinterSprite->SetImageIndex(_yesButtonResourceManagerMap.find(0)->second);
		_pNoPrinterSprite->SetImageIndex(_noButtonResourceManagerMap.find(1)->second);
	}
	//������Ʈ�� �̸��� ���
	if (_pNamePrinter != nullptr)
	{
		((dod::RenderText*)(_pNamePrinter->GetComponent<dod::RenderComponent>()))->SetString(L"%.3llf, %.3llf", engineptr->timer.GetDeltaTime(), engineptr->timer.GetFrameTime());
	}

	//������Ʈ�� ü���� ���
	if (_pHPPrinter != nullptr)
	{
		((dod::RenderText*)(_pHPPrinter->GetComponent<dod::RenderComponent>()))->SetString(L"HP : %d", HP);
	}

	//�÷��̾ ���� ������ ����� ���ϵ��� �ϴ� �κ�
	if (transform->position.x < 180.0f)
	{
		transform->position.x = 180.f;
	}

	if (transform->position.x > 1720.f)
	{
		transform->position.x = 1720.f;
	}

	if (transform->position.y > 800.f)
	{
		transform->position.y = 800.f;
	}

	if (transform->position.y < 350.f)
	{
		transform->position.y = 350.f;
	}

	if (_psceneManager->gameScene == SceneManager::eGameScene::Title)
	{
		if (transform->position.y < 400.f)
		{
			transform->position.y = 400.f;
		}
	}

	if (_dashed == true)
	{
		Dash();
	}

	if (_hitPlayer == true)
	{
		HitPlayer();
	}

	if (_specialAttack == true)
	{
		SpecialAttack();
	}

	//�뽬 ��Ÿ�� ����� ���� ����
	static double dashCoolTime = 0;
	if (_isDashCoolDown == true)
	{
		if (dashCoolTime > 1.0)
		{
			_isDashCoolDown = false;
			dashCoolTime = 0;
		}
		dashCoolTime += engineptr->timer.GetDeltaTime();
	}

}

void TestPlayer::OnDisable()
{

	for (int i = 0; i < DICE_CAPCITY; i++)
	{
		_HaveDicePrinter[i]->Disable();
		_DiceNumberPrinter[i]->Disable();
	}

	_pRetryPrinter->Disable();
	_pNamePrinter->Disable();
	_pHPPrinter->Disable();
	_pNoPrinter->Disable();
	_pYesPrinter->Disable();
}\

void TestPlayer::OnRelease()
{

}


bool TestPlayer::addDice(TestDice* dice)
{
	if (_dashed == false)
	{
		_diceCount++;


		if (_diceCount <= DICE_CAPCITY)
		{
			_diceNumber[_diceCount - 1] = dice->GetDiceNumber();

			return true;
		}

		else
		{

			_diceCount = DICE_CAPCITY;
			return false;
		}
	}
	return false;
}

void TestPlayer::DiceCut()
{
	if (_diceCount > 0)
	{
		_diceCount--;
		return;
	}
	Assert(false, "�ֻ����� ���µ� �ҷ����.");
}

void TestPlayer::AdjustHP(int damage)
{
	static bool isSoundPlay = false;
	if (isSoundPlay == false)
	{
		engineptr->soundManager->Sound_CreateSFXSound(SOUND_PATH(SFX\\Player_Hit.ogg), dod::PLAYER_HIT_SFX);
		isSoundPlay = true;
	}
	engineptr->soundManager->Sound_PlaySound(dod::PLAYER_HIT_SFX);

	HP -= damage;
}

bool TestPlayer::GetControlable()
{
	return _controlable;
}

void TestPlayer::SetScene(SceneManager* sceneManager)
{
	_psceneManager = sceneManager;
}

void TestPlayer::Dash()
{
	const double time = 0.45;
	static double num = 0;
	static bool isSoundPlay = false;


	num += engineptr->timer.GetDeltaTime();


	//if (isSoundPlay == false)
	//{
		//engineptr->soundManager->Sound_CreateSFXSound(SOUND_PATH(SFX\\Player_Walk.ogg",dod::ROLLING_SFX); //�뽬 �� �� ������ ȿ����
		//isSoundPlay = true;
	//}

	//_direction.x = dirX;
	//_direction.y = dirY;	if (num < time)

	if (num < time)
	{
		if (_controlable == true)
		{
			_direction = dod::Vector3::Normalize(_direction);
			_speed = _dashSpeed;
			_controlable = false;


			//	engineptr->soundManager->Sound_AllMute();
			if (isSoundPlay == false)
			{
				engineptr->soundManager->Sound_CreateSFXSound(SOUND_PATH(SFX\\Player_Roll.ogg), dod::ROLLING_SFX); //�뽬 �� �� ������ ȿ����
				isSoundPlay = true;
			}
			engineptr->soundManager->Sound_PlaySound(dod::ROLLING_SFX);
		}
	}
	else
	{
		_speed = _initSpeed;
		num = 0;
		_controlable = true;
		_dashed = false;
		_pSpritePrint->SetImageIndex(_imageResourceManagerMap.find(ePlayerImageList::PLAYERMAIN)->second);
		_direction.x = 0;
		_direction.y = 0;
	}
}

void TestPlayer::HitPlayer()
{
	const double time = 0.4;
	static double num = 0;
	_direction.x = 0;
	_direction.y = 0;

	num += engineptr->timer.GetDeltaTime();

	if (num < time)
	{
		if (_controlable == true)
		{
			_direction = dod::Vector3::Normalize(_direction);
			_controlable = false;
			_dashed = false;
			_specialAttack = false;
		}
	}
	else
	{
		num = 0;
		_controlable = true;
		_hitPlayer = false;
		_pSpritePrint->SetImageIndex(_imageResourceManagerMap.find(ePlayerImageList::PLAYERMAIN)->second);
	}
}

void TestPlayer::SpecialAttack()
{

}


void TestPlayer::CleanMydice()
{

	for (int i = 0; i < DICE_CAPCITY; ++i)
	{
		if (_diceNumber[i] != 0)
		{
			continue;
		}

		for (int j = i + 1; j < DICE_CAPCITY; ++j)
		{

			if (_diceNumber[j] != 0)
			{
				_diceNumber[i] = _diceNumber[j];
				_diceNumber[j] = 0;
				break;
			}
		}
	}
}

int TestPlayer::GetDiceNumber(int index)
{
	return _diceNumber[index];
}

void TestPlayer::SetDiceNumber(int index, int value)
{
	Assert(index < DICE_CAPCITY, "������ �ʰ��� �ε����� Set�õ�");
	_diceNumber[index] = value;
}

bool TestPlayer::GetSpecialAttack()
{
	return _specialAttack;
}
