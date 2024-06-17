#include <vector>

#include "GameProcess.h"
#include "Id2d.h"
#include "GameEngine.h"

#include "MainCamera.h"

GameProcess::GameProcess()
	: _hWnd(NULL),
	_MSG(),
	_gameEngine(nullptr)
{
	
}

GameProcess::~GameProcess()
{
	delete _gameEngine;
}

HRESULT GameProcess::Initialize()
{
	/// Win32 관련
	// 윈도 클래스
	WNDCLASSEX wc
	{
		sizeof(WNDCLASSEX),
		CS_CLASSDC,
		WndProc,
		0L,
		0L,
		GetModuleHandle(NULL),
		NULL,
		NULL,
		NULL,
		NULL,
		L"KNTclass", // lpszClassName
		NULL
	};

	// 윈도 클래스 등록
	RegisterClassEx(&wc);

	// 윈도 생성
	_hWnd = CreateWindow(
		wc.lpszClassName,
		L"KNT",
		WS_OVERLAPPED | WS_BORDER | WS_SYSMENU,
		100, // 윈도우 좌측 상단의 x 좌표
		100, // 윈도우 좌측 상단의 y 좌표
		_screenWidth, _screenHeight, // 윈도우 가로 방향 해상도		
		NULL,
		NULL,
		wc.hInstance,
		NULL
	);

	if (!_hWnd) return S_FALSE;

	// 생성된 윈도를 화면에 표시
	ShowWindow(_hWnd, SW_SHOWNORMAL);
	UpdateWindow(_hWnd);


	//외부클래스 생성


	/// 그래픽스 엔진 관련

	// 비트맵
	_spritePool.clear();

	_gameEngine = new dod::GameEngine();
	_gameEngine->InitializeD2dEngine(_hWnd, _screenWidth, _screenHeight);
	_gameEngine->InitializeKeyManger(_hWnd);
	_gameEngine->InitializePhysicsEngine();
	
	_rectComponenet = new dod::RenderRect(0, 0, 200, 200, 2);
	_circleComponent1 = new dod::RenderCircle(300, 2);
	_ameText = new dod::RenderText(0, 0, 2);
	_backGround = new dod::RenderSprite(0, 0, 0);
	_imageResourceManagerMap.insert({ eImageList::STARTBACKGROUND, _backGround->PushBackImageDataVector(L"..\\..\\..\\4_Resources\\Reference\\sample2.jpg")});
	_imageResourceManagerMap.insert({ eImageList::MAINBACKGROUND, _backGround->PushBackImageDataVector(L"..\\..\\..\\4_Resources\\Reference\\sample4.jpg")});
	_player = new dod::RenderSprite(0, 0, 1);
	_imageResourceManagerMap.insert({ eImageList::PLAYERMAIN, _player->PushBackImageDataVector(L"..\\..\\..\\4_Resources\\Sprite\\Player\\Sheet\\player_Idle.png") });
	_imageResourceManagerMap.insert({ eImageList::PLAYERDIE, _player->PushBackImageDataVector(L"..\\..\\..\\4_Resources\\Sprite\\Player\\Sheet\\player_Death.png", 0.1) });
	_imageResourceManagerMap.insert({ eImageList::PLAYERATTACK, _player->PushBackImageDataVector(L"..\\..\\..\\4_Resources\\Sprite\\Player\\Sheet\\player_Attack.png") });
	_imageResourceManagerMap.insert({ eImageList::PLAYERHIT, _player->PushBackImageDataVector(L"..\\..\\..\\4_Resources\\Sprite\\Player\\Sheet\\player_Hit.png", 0.06) });
	_imageResourceManagerMap.insert({ eImageList::PLAYERJUMP, _player->PushBackImageDataVector(L"..\\..\\..\\4_Resources\\Sprite\\Player\\Sheet\\player_Jump.png") });
	_imageResourceManagerMap.insert({ eImageList::PLAYERWALK, _player->PushBackImageDataVector(L"..\\..\\..\\4_Resources\\Sprite\\Player\\Sheet\\player_Walk.png") });
	_imageResourceManagerMap.insert({ eImageList::PLAYERROLLING, _player->PushBackImageDataVector(L"..\\..\\..\\4_Resources\\Sprite\\Player\\Sheet\\player_Roll.png") });
	_dice = new dod::RenderSprite(0, 0, 1);
	_imageResourceManagerMap.insert({ eImageList::DICE1, _dice->PushBackImageDataVector(L"..\\..\\..\\4_Resources\\UI\\Dice\\dice_Sheet1.png") });
	_imageResourceManagerMap.insert({ eImageList::DICEROLLING, _dice->PushBackImageDataVector(L"..\\..\\..\\4_Resources\\UI\\Dice\\dice_Rolling.png") });

	_obj = _gameEngine->RegisterGameObject<dod::GameObject>(L"test");
	_obj->AddComponent(_rectComponenet);
	_obj1 = _gameEngine->RegisterGameObject<dod::GameObject>(L"test1");
	_obj1->AddComponent(_circleComponent1);
	_obj2 = _gameEngine->RegisterGameObject<dod::GameObject>(L"test2");
	_obj2->AddComponent(_ameText);
	_obj3 = _gameEngine->RegisterGameObject<dod::GameObject>(L"test3");
	_obj3->AddComponent(_backGround);
	_obj4 = _gameEngine->RegisterGameObject<dod::GameObject>(L"test4");
	_obj4->AddComponent(_player);
	_obj5 = _gameEngine->RegisterGameObject<dod::GameObject>(L"test5");
	_obj5->AddComponent(_dice);

// 	_cameraTR.scale.x = 1.0f;
// 	_cameraTR.scale.y = 1.0f;
// 	_cameraTR.position.x = 800.0f;
// 	_cameraTR.position.y = 600.0f;
// 	_cameraTR.rotation = 0.0f;
	_camera = _gameEngine->RegisterGameObject<MainCamera>(L"Camera");
	_gameEngine->SetCameraObject(_camera->ReturnTrasform());
	

	_allTR.scale.x = 1.0f;
	_allTR.scale.y = 1.0f;
	_allTR.position.x = 0.0f;
	_allTR.position.y = 0.0f;
	_allTR.rotation = 0.0f;

	_rectComponenet->SetTransform(&_allTR);
	_circleComponent1->SetTransform(&_allTR);
	_ameText->SetTransform(&_allTR);
	_backGround->SetTransform(&_allTR);

	//_playerTR = _cameraTR;
	_playerTR.scale.x = 5.f;
	_playerTR.scale.y = 5.f;

	//_playerTR2 = _cameraTR;
	_playerTR2.scale.x = 5.f;
	_playerTR2.scale.y = 5.f;
 	_playerTR2.position.x = 300.0f;
 	_playerTR2.position.y = 100.0f;
	
	_dice->SetTransform(&_playerTR);
	_player->SetTransform(&_playerTR2);


	_obj->Enable();
	_obj1->Enable();
	_obj2->Enable();
	_obj3->Enable();
	_obj4->Enable();
	

	//키입력
	_keyComponenet = new dod::KeyComponent();
	_keyComponenet->onKeyDown = [&](const dod::KeyInfo& key, const dod::GameObject& obj)
	{
		if (key.code == dod::eButtonCode::PAD_DPAD_RIGHT)
		{
			_playerTR.position.x += 5;
		}

		if (key.code == dod::eButtonCode::PAD_DPAD_LEFT)
		{
			_playerTR.position.x -= 5;
		}

		if (key.code == dod::eButtonCode::PAD_DPAD_UP)
		{
			_playerTR.position.y += 5;
		}

		if (key.code == dod::eButtonCode::PAD_DPAD_DOWN)
		{
			_playerTR.position.y -= 5;
		}
	};
	_obj5->AddComponent(_keyComponenet);
	_obj5->Enable();
	// 오브젝트 초기화
	
	return S_OK;
}

void GameProcess::Loop()
{
	while (true)
	{
		if (PeekMessage(&_MSG, NULL, 0, 0, PM_REMOVE))
		{
			if (_MSG.message == WM_QUIT) break;

			DispatchMessage(&_MSG);
		}
		else
		{
			_ame++;

			/// 카메라 조정
// 			if (_ame < 500)
// 			{
// 				_camera.ReturnTransform()->scale.x+= 0.001f;
// 				_camera.ReturnTransform()->scale.y+= 0.001f;
// // 				_cameraTR.scale.x += 0.001f;
// // 				_cameraTR.scale.y += 0.001f;
// 			}
// 			if (_ame > 200 && _ame < 500)
// 			{
// 				_cameraTR.position.x += 1.f;
// 			}
// 			if (_ame > 500 && _ame < 800)
// 			{
// 				_cameraTR.position.y += 1.f;
// 			}
// 			if (_ame > 800 && _ame < 1100)
// 			{
// 				_cameraTR.position.x -= 1.f;
// 			}
// 			if (_ame > 1100 && _ame < 1400)
// 			{
// 				_cameraTR.position.y -= 1.f;
// 			}
			
			_dice->SetTransform(&_playerTR);
			if (_ame == 200)
			{
				_obj1->Disable();
				_obj1->Release();
				_backGround->SetImageIndex(_imageResourceManagerMap.find(eImageList::MAINBACKGROUND)->second);
				_dice->SetImageIndex(_imageResourceManagerMap.find(eImageList::DICEROLLING)->second);
			}

			if (_ame == 100)
			{
				_player->SetImageIndex(_imageResourceManagerMap.find(eImageList::PLAYERATTACK)->second);
			}
			if (_ame == 400)
			{
				_player->SetImageIndex(_imageResourceManagerMap.find(eImageList::PLAYERJUMP)->second);
			}
			if (_ame == 600)
			{
				_player->SetImageIndex(_imageResourceManagerMap.find(eImageList::PLAYERWALK)->second);
			}
			if (_ame == 800)
			{
				_player->SetImageIndex(_imageResourceManagerMap.find(eImageList::PLAYERROLLING)->second);
			}
			if (_ame == 1000)
			{
				_player->SetImageIndex(_imageResourceManagerMap.find(eImageList::PLAYERHIT)->second);
			}
			if (_ame == 1200)
			{
				_player->SetImageIndex(_imageResourceManagerMap.find(eImageList::PLAYERDIE)->second);
			}
			if (_ame == 1400)
			{
				_backGround->ChangeLayer(2);
			}
			_gameEngine->GameLoop();			
			//UpdateAll();
			//RenderAll();
		}
	}
}

void GameProcess::Finalize()
{
	delete _gameEngine;
}

// 메시지 핸들러 (윈도 콜백)
LRESULT CALLBACK GameProcess::WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	HDC			hdc;
	PAINTSTRUCT ps;

	switch (message)
	{
		case WM_PAINT:
			hdc = BeginPaint(hWnd, &ps);
			EndPaint(hWnd, &ps);
			break;

		case WM_DESTROY:
			PostQuitMessage(0);
			break;
	}

	return DefWindowProc(hWnd, message, wParam, lParam);
}