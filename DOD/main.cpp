#include <Windows.h>

#include "GameEngine.h"
#include "Macro.h"
#include "RenderCircle.h"
#include "RenderText.h"
#include "RenderRect.h"
#include "RenderLine.h"
#include "GameObject.h"
#include "Transform.h"
#include "KeyComponent.h"
#include "TestPlayer.h"
#include "TestDice.h"
#include "TestAttack.h"
#include "Boss.h"
#include "DiceController.h"
#include "SoundManager.h"
#include "SceneManager.h"
#include "MainCamera.h"

#pragma comment(lib, "fmod_vc.lib")


constexpr int WindowsLength = 1280;
constexpr int WindowsHeight = 720;

LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);

int APIENTRY wWinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance, _In_ LPWSTR    lpCmdLine, _In_ int       nCmdShow)
{
	WNDCLASSEXW wcex;

	wcex.cbSize = sizeof(WNDCLASSEX);

	wcex.style = CS_HREDRAW | CS_VREDRAW;
	wcex.lpfnWndProc = WndProc;
	wcex.cbClsExtra = 0;
	wcex.cbWndExtra = 0;
	wcex.hInstance = hInstance;
	wcex.hIcon = LoadIcon(hInstance, IDI_APPLICATION);
	wcex.hCursor = LoadCursor(nullptr, IDC_ARROW);
	wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
	wcex.lpszMenuName = NULL;
	wcex.lpszClassName = L"Die or Dice";
	wcex.hIconSm = NULL;

	RegisterClassExW(&wcex);


	///(그 윈도우를) 생성
	HWND hWnd = CreateWindowW(wcex.lpszClassName, L"Die or Dice", WS_OVERLAPPEDWINDOW,
		NULL, NULL, WindowsLength, WindowsHeight, nullptr, nullptr, hInstance, nullptr);

	Assert(hWnd, "윈도우 핸들을 제대로 만들지 못했음.");

	ShowWindow(hWnd, nCmdShow);
	UpdateWindow(hWnd);

	/// 게임엔진 생성
	dod::GameEngine* gameEngine = new dod::GameEngine();

	/// 그래픽엔진 초기화
	gameEngine->InitializeD2dEngine(hWnd, WindowsLength, WindowsHeight);
	gameEngine->InitializeKeyManger(hWnd);
	gameEngine->InitializePhysicsEngine();
	gameEngine->InitializeSoundManager();
	gameEngine->soundManager->Sound_Initalation();


	///무한루프(안에 메시지 루프와 게임 루프등이 포함됨)

	///메세지 루프
	MSG msg;

	
	//씬 매니저
	SceneManager sceneManager;
	sceneManager.InitializeSceneManager(gameEngine);

	// 카메라 생성
	auto mainCamera = gameEngine->RegisterGameObject<MainCamera>(L"Camera");
	gameEngine->SetCameraObject(mainCamera->ReturnTrasform());

	while (true)
	{
		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
		{
			if (msg.message == WM_QUIT)break;
			DispatchMessage(&msg);
		}
		else
		{
			sceneManager.SeceneManagement();
			gameEngine->GameLoop();	//게임루프 본문
		}
	}

	//카메라 해제하는 코드
	return 0;
}

LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message)
	{
		case WM_DESTROY:
			PostQuitMessage(0);
			break;
		default:
			return DefWindowProc(hWnd, message, wParam, lParam);
	}
	return 0;
}
