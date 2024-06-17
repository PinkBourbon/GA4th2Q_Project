#include "KeyManager.h"
#include "Macro.h"


dod::KeyManager::KeyManager(HWND hWnd) :
	YetKeyState(false), _hWnd(hWnd), _mousePoint{ 0 }
{
	InitializeKeyMapping();
	//std::function<void(int)> onKeyDown = [](int) {}; //당장 필요 없음 모양만 눈에 익히기
	//std::function<void(int)> onKeyUp = [](int) {};
	//std::function<void(int)> onKeyStay = [](int) {}; 
	// 테스트 쪽 보면 람다식으로 있음 외부에서 선언하고 가져올 예정
}

dod::KeyManager::~KeyManager()
{

}

void dod::KeyManager::KeyInput()
{
	MouseClick();
	KeyCheck<VK_UP>();
	KeyCheck<VK_DOWN>();
	KeyCheck<VK_LEFT>();
	KeyCheck<VK_RIGHT>();
	KeyCheck<VK_SPACE>();
	KeyCheck<VK_LCONTROL>();
	KeyCheck<0x30>();
}

void dod::KeyManager::StickMoveCheck(XINPUT_STATE& padState)
{
	constexpr int DeadZone = 4500000;
	int tempX = padState.Gamepad.sThumbLX;
	int tempY = padState.Gamepad.sThumbLY;

	KeyInfo keyInfo(eButtonCode::PAD_L_JOYSTICKMOVE);
	if (tempX * tempX + tempY * tempY > DeadZone)
	{

		keyInfo.x = padState.Gamepad.sThumbLX;
		keyInfo.y = padState.Gamepad.sThumbLY;
		InputCallBack<eButtonCode::PAD_L_JOYSTICKMOVE>(keyInfo ,true);
	}
	else
	{
		InputCallBack<eButtonCode::PAD_L_JOYSTICKMOVE>(keyInfo, false);
	}

	tempX = padState.Gamepad.sThumbRX;
	tempY = padState.Gamepad.sThumbRY;
	keyInfo.code = eButtonCode::PAD_R_JOYSTICKMOVE;
	if (tempX * tempX + tempY * tempY > DeadZone)
	{
		keyInfo.x = padState.Gamepad.sThumbRX;
		keyInfo.y = padState.Gamepad.sThumbRY;

		InputCallBack<eButtonCode::PAD_R_JOYSTICKMOVE>(keyInfo, true);
	}
	else
	{
		InputCallBack<eButtonCode::PAD_R_JOYSTICKMOVE>(keyInfo, false);
	}
}

void dod::KeyManager::TriggerClickCheck(XINPUT_STATE& padState)
{
	constexpr int DeadZone = 50;
	int temp = padState.Gamepad.bLeftTrigger;

	KeyInfo keyInfo(eButtonCode::PAD_L_TRIGGER);
	if (temp > DeadZone)
	{
		keyInfo.y = padState.Gamepad.bLeftTrigger;
		InputCallBack<eButtonCode::PAD_L_TRIGGER>(keyInfo, true);
	}
	else
	{
		InputCallBack<eButtonCode::PAD_L_TRIGGER>(keyInfo, false);
	}

	temp = padState.Gamepad.bRightTrigger;
	keyInfo.code = eButtonCode::PAD_R_TRIGGER;

	if (temp > DeadZone)
	{
		keyInfo.y = padState.Gamepad.bRightTrigger;
		InputCallBack<eButtonCode::PAD_R_TRIGGER>(keyInfo, true);
	}
	else
	{
		InputCallBack<eButtonCode::PAD_R_TRIGGER>(keyInfo, false);
	}
}

void dod::KeyManager::MouseClick()
{
	GetMousePos();
	MouseCheck(VK_LBUTTON, _mousePoint);
}

void dod::KeyManager::GetMousePos()
{
	if (GetCursorPos(&_mousePoint))
	{
		ScreenToClient(_hWnd, &_mousePoint);
		//std::cout << mousePoint.x << ", " << mousePoint.y << std::endl;
	}
}

void dod::KeyManager::MouseCheck(int check, POINT mousePoint)
{
	bool isDownState = GetAsyncKeyState(check) & 0x8001;
	eButtonCode code = (*(_keyMapping.find(check + 0x8000))).second;
	KeyInfo key(code, mousePoint.x, mousePoint.y);

	if (isDownState == true && YetKeyState == true)
	{
		YetKeyState = true;
		for (const auto& e : _keyComponentSet)
		{
			if (e == nullptr) continue;
			e->onKeyStay(key, *(e->GetObject()));

		}

	}
	else if (isDownState == true && YetKeyState == false)
	{
		YetKeyState = true;
		for (const auto& e : _keyComponentSet)
		{
			if (e == nullptr) continue;
			e->onKeyDown(key, *(e->GetObject()));
		}
	}
	else if (isDownState == false && YetKeyState == true)
	{
		YetKeyState = false;
		for (const auto& e : _keyComponentSet)
		{
			if (e == nullptr) continue;
			e->onKeyUp(key, *(e->GetObject()));
		}
	}
}

void dod::KeyManager::InitializeKeyMapping()
{
	_keyMapping.insert({ XINPUT_GAMEPAD_LEFT_THUMB, eButtonCode::PAD_L_JOYSTICKCLICK });
	_keyMapping.insert({ XINPUT_GAMEPAD_RIGHT_THUMB, eButtonCode::PAD_R_JOYSTICKCLICK });
	//_keyMapping.insert({ VK_PAD_LTRIGGER, eButtonCode::PAD_L_TRIGGER});
	//_keyMapping.insert({ VK_PAD_RTRIGGER, eButtonCode::PAD_R_TRIGGER});
	_keyMapping.insert({ XINPUT_GAMEPAD_LEFT_SHOULDER, eButtonCode::PAD_L_SHOULDER });
	_keyMapping.insert({ XINPUT_GAMEPAD_RIGHT_SHOULDER, eButtonCode::PAD_R_SHOULDER });
	_keyMapping.insert({ XINPUT_GAMEPAD_DPAD_UP, eButtonCode::PAD_DPAD_UP });
	_keyMapping.insert({ XINPUT_GAMEPAD_DPAD_DOWN, eButtonCode::PAD_DPAD_DOWN });
	_keyMapping.insert({ XINPUT_GAMEPAD_DPAD_LEFT, eButtonCode::PAD_DPAD_LEFT });
	_keyMapping.insert({ XINPUT_GAMEPAD_DPAD_RIGHT, eButtonCode::PAD_DPAD_RIGHT });
	_keyMapping.insert({ XINPUT_GAMEPAD_A, eButtonCode::PAD_DPAD_A });
	_keyMapping.insert({ XINPUT_GAMEPAD_B, eButtonCode::PAD_DPAD_B });
	_keyMapping.insert({ XINPUT_GAMEPAD_X, eButtonCode::PAD_DPAD_X });
	_keyMapping.insert({ XINPUT_GAMEPAD_Y, eButtonCode::PAD_DPAD_Y });
	_keyMapping.insert({ XINPUT_GAMEPAD_START, eButtonCode::PAD_DPAD_START });
	_keyMapping.insert({ XINPUT_GAMEPAD_BACK, eButtonCode::PAD_DPAD_BACK });
	_keyMapping.insert({ 0x8000 + VK_UP, eButtonCode::KEY_UP });
	_keyMapping.insert({ 0x8000 + VK_DOWN, eButtonCode::KEY_DOWN });
	_keyMapping.insert({ 0x8000 + VK_LEFT, eButtonCode::KEY_LEFT });
	_keyMapping.insert({ 0x8000 + VK_RIGHT, eButtonCode::KEY_RIGHT });
	_keyMapping.insert({ 0x8000 + VK_SPACE, eButtonCode::KEY_SPACE });
	_keyMapping.insert({ 0x8000 + VK_LCONTROL, eButtonCode::KEY_LCRTL });
	_keyMapping.insert({ 0x8000 + VK_RCONTROL, eButtonCode::KEY_RCTRL });
	_keyMapping.insert({ 0x8000 + VK_LMENU, eButtonCode::KEY_LALT });
	_keyMapping.insert({ 0x8000 + VK_RMENU, eButtonCode::KEY_RALT });
	_keyMapping.insert({ 0x8000 + VK_LSHIFT, eButtonCode::KEY_LSHIFT });
	_keyMapping.insert({ 0x8000 + VK_RSHIFT, eButtonCode::KEY_RSHIFT });
	_keyMapping.insert({ 0x8000 + VK_TAB, eButtonCode::KEY_TAB });
	_keyMapping.insert({ 0x8000 + VK_RETURN, eButtonCode::KEY_ENTER });
	_keyMapping.insert({ 0x8000 + VK_ESCAPE, eButtonCode::KEY_ESC });
	_keyMapping.insert({ 0x8000 + 0x41, eButtonCode::KEY_A });
	_keyMapping.insert({ 0x8000 + 0x42, eButtonCode::KEY_B });
	_keyMapping.insert({ 0x8000 + 0x43, eButtonCode::KEY_C });
	_keyMapping.insert({ 0x8000 + 0x44, eButtonCode::KEY_D });
	_keyMapping.insert({ 0x8000 + 0x45, eButtonCode::KEY_E });
	_keyMapping.insert({ 0x8000 + 0x46, eButtonCode::KEY_F });
	_keyMapping.insert({ 0x8000 + 0x47, eButtonCode::KEY_G });
	_keyMapping.insert({ 0x8000 + 0x48, eButtonCode::KEY_H });
	_keyMapping.insert({ 0x8000 + 0x49, eButtonCode::KEY_I });
	_keyMapping.insert({ 0x8000 + 0x4A, eButtonCode::KEY_J });
	_keyMapping.insert({ 0x8000 + 0x4B, eButtonCode::KEY_K });
	_keyMapping.insert({ 0x8000 + 0x4C, eButtonCode::KEY_L });
	_keyMapping.insert({ 0x8000 + 0x4D, eButtonCode::KEY_M });
	_keyMapping.insert({ 0x8000 + 0x4E, eButtonCode::KEY_N });
	_keyMapping.insert({ 0x8000 + 0x4F, eButtonCode::KEY_O });
	_keyMapping.insert({ 0x8000 + 0x50, eButtonCode::KEY_P });
	_keyMapping.insert({ 0x8000 + 0x51, eButtonCode::KEY_Q });
	_keyMapping.insert({ 0x8000 + 0x52, eButtonCode::KEY_R });
	_keyMapping.insert({ 0x8000 + 0x53, eButtonCode::KEY_S });
	_keyMapping.insert({ 0x8000 + 0x54, eButtonCode::KEY_T });
	_keyMapping.insert({ 0x8000 + 0x55, eButtonCode::KEY_U });
	_keyMapping.insert({ 0x8000 + 0x56, eButtonCode::KEY_V });
	_keyMapping.insert({ 0x8000 + 0x57, eButtonCode::KEY_W });
	_keyMapping.insert({ 0x8000 + 0x58, eButtonCode::KEY_X });
	_keyMapping.insert({ 0x8000 + 0x59, eButtonCode::KEY_Y });
	_keyMapping.insert({ 0x8000 + 0x5A, eButtonCode::KEY_Z });
	_keyMapping.insert({ 0x8000 + 0x30, eButtonCode::KEY_0 });
	_keyMapping.insert({ 0x8000 + 0x31, eButtonCode::KEY_1 });
	_keyMapping.insert({ 0x8000 + 0x32, eButtonCode::KEY_2 });
	_keyMapping.insert({ 0x8000 + 0x33, eButtonCode::KEY_3 });
	_keyMapping.insert({ 0x8000 + 0x34, eButtonCode::KEY_4 });
	_keyMapping.insert({ 0x8000 + 0x35, eButtonCode::KEY_5 });
	_keyMapping.insert({ 0x8000 + 0x36, eButtonCode::KEY_6 });
	_keyMapping.insert({ 0x8000 + 0x37, eButtonCode::KEY_7 });
	_keyMapping.insert({ 0x8000 + 0x38, eButtonCode::KEY_8 });
	_keyMapping.insert({ 0x8000 + 0x39, eButtonCode::KEY_9 });
	_keyMapping.insert({ 0x8000 + VK_NUMPAD0, eButtonCode::KEY_NUM0 });
	_keyMapping.insert({ 0x8000 + VK_NUMPAD1, eButtonCode::KEY_NUM1 });
	_keyMapping.insert({ 0x8000 + VK_NUMPAD2, eButtonCode::KEY_NUM2 });
	_keyMapping.insert({ 0x8000 + VK_NUMPAD3, eButtonCode::KEY_NUM3 });
	_keyMapping.insert({ 0x8000 + VK_NUMPAD4, eButtonCode::KEY_NUM4 });
	_keyMapping.insert({ 0x8000 + VK_NUMPAD5, eButtonCode::KEY_NUM5 });
	_keyMapping.insert({ 0x8000 + VK_NUMPAD6, eButtonCode::KEY_NUM6 });
	_keyMapping.insert({ 0x8000 + VK_NUMPAD7, eButtonCode::KEY_NUM7 });
	_keyMapping.insert({ 0x8000 + VK_NUMPAD8, eButtonCode::KEY_NUM8 });
	_keyMapping.insert({ 0x8000 + VK_NUMPAD9, eButtonCode::KEY_NUM9 });
	_keyMapping.insert({ 0x8000 + VK_LBUTTON, eButtonCode::MOUSE_LBUTTON });
	_keyMapping.insert({ 0x8000 + VK_RBUTTON, eButtonCode::MOUSE_RBUTTON });
}

void dod::KeyManager::EnrollComponent(KeyComponent* keycomponent)
{
	//std::unordered_set<> _set;
	_keyComponentSet.insert(keycomponent);
}

void dod::KeyManager::DisenrollComponent(KeyComponent* keycomponent)
{
	_keyComponentSet.erase(keycomponent);
}

void dod::KeyManager::PadInput()
{


	//PadCheck<VK_PAD_A, XINPUT_KEYSTROKE_KEYDOWN>(); // 패드의 a를 눌렀다는 뜻
	PadCheck(); // 패드의 a를 눌렀다는 뜻

	//PadCheck<VK_PAD_A, XINPUT_KEYSTROKE_KEYUP>(); // 패드의 a를 떼었다는 뜻
	//PadCheck<VK_PAD_B, XINPUT_KEYSTROKE_KEYUP>(); // 패드의 a를 떼었다는 뜻
	//PadCheck<VK_PAD_X, XINPUT_KEYSTROKE_KEYUP>(); // 패드의 a를 떼었다는 뜻
	//PadCheck<VK_PAD_Y, XINPUT_KEYSTROKE_KEYUP>(); // 패드의 a를 떼었다는 뜻

}



void dod::KeyManager::PadState()
{
	DWORD dwResult;
	for (DWORD i = 0; i < XUSER_MAX_COUNT; i++)
	{
		XINPUT_STATE state;
		ZeroMemory(&state, sizeof(XINPUT_STATE));

		// Simply get the state of the controller from XInput.
		dwResult = XInputGetState(i, &state);

		if (dwResult == ERROR_SUCCESS)
		{

		}
		else
		{
			// Controller is not connected
		}
	}
}

void dod::KeyManager::PadCheck()
{
	XINPUT_STATE padState;
	DWORD errCode = XInputGetState(0, &padState);

	if (errCode == ERROR_DEVICE_NOT_CONNECTED)
	{
		//Assert(false, "니 패드 뒤짐");
		return;
	}

	// 먼저 스틱이 움직여져 있는지 확인하고 콜백을 한다.
	StickMoveCheck(padState);
	TriggerClickCheck(padState);

	KeyInfo keyInfo(eButtonCode::PAD_DPAD_UP);
	InputCallBack<eButtonCode::PAD_DPAD_UP>(keyInfo, padState.Gamepad.wButtons & XINPUT_GAMEPAD_DPAD_UP);
	keyInfo.code = eButtonCode::PAD_DPAD_DOWN;
	InputCallBack<eButtonCode::PAD_DPAD_DOWN>(keyInfo, padState.Gamepad.wButtons & XINPUT_GAMEPAD_DPAD_DOWN);
	keyInfo.code = eButtonCode::PAD_DPAD_LEFT;
	InputCallBack < eButtonCode::PAD_DPAD_LEFT> (keyInfo, padState.Gamepad.wButtons & XINPUT_GAMEPAD_DPAD_LEFT);
	keyInfo.code = eButtonCode::PAD_DPAD_RIGHT;
	InputCallBack < eButtonCode::PAD_DPAD_RIGHT>(keyInfo, padState.Gamepad.wButtons & XINPUT_GAMEPAD_DPAD_RIGHT);
	keyInfo.code = eButtonCode::PAD_DPAD_START;
	InputCallBack < eButtonCode::PAD_DPAD_START>(keyInfo, padState.Gamepad.wButtons & XINPUT_GAMEPAD_START);
	keyInfo.code = eButtonCode::PAD_DPAD_BACK;
	InputCallBack < eButtonCode::PAD_DPAD_BACK>(keyInfo, padState.Gamepad.wButtons & XINPUT_GAMEPAD_BACK);
	keyInfo.code = eButtonCode::PAD_L_JOYSTICKCLICK;
	InputCallBack < eButtonCode::PAD_L_JOYSTICKCLICK>(keyInfo, padState.Gamepad.wButtons & XINPUT_GAMEPAD_LEFT_THUMB);
	keyInfo.code = eButtonCode::PAD_R_JOYSTICKCLICK;
	InputCallBack < eButtonCode::PAD_R_JOYSTICKCLICK>(keyInfo, padState.Gamepad.wButtons & XINPUT_GAMEPAD_RIGHT_THUMB);
	keyInfo.code = eButtonCode::PAD_L_SHOULDER;
	InputCallBack < eButtonCode::PAD_L_SHOULDER>(keyInfo, padState.Gamepad.wButtons & XINPUT_GAMEPAD_LEFT_SHOULDER);
	keyInfo.code = eButtonCode::PAD_R_SHOULDER;
	InputCallBack < eButtonCode::PAD_R_SHOULDER>(keyInfo, padState.Gamepad.wButtons & XINPUT_GAMEPAD_RIGHT_SHOULDER);
	keyInfo.code = eButtonCode::PAD_DPAD_A;
	InputCallBack < eButtonCode::PAD_DPAD_A>(keyInfo, padState.Gamepad.wButtons & XINPUT_GAMEPAD_A);
	keyInfo.code = eButtonCode::PAD_DPAD_B;
	InputCallBack < eButtonCode::PAD_DPAD_B>(keyInfo, padState.Gamepad.wButtons & XINPUT_GAMEPAD_B);
	keyInfo.code = eButtonCode::PAD_DPAD_X;
	InputCallBack < eButtonCode::PAD_DPAD_X>(keyInfo, padState.Gamepad.wButtons & XINPUT_GAMEPAD_X);
	keyInfo.code = eButtonCode::PAD_DPAD_Y;
	InputCallBack < eButtonCode::PAD_DPAD_Y>(keyInfo, padState.Gamepad.wButtons & XINPUT_GAMEPAD_Y);
	//XINPUT_KEYSTROKE keyStroke; 

	//DWORD retval = XInputGetKeystroke(0, 0, &keyStroke);
	//DWORD currKey = keyStroke.VirtualKey;
	//static DWORD beforeKey = 0;
	//if (retval == ERROR_EMPTY)
	//{
	//	currKey = beforeKey;
	//}
	//else
	//{
	//	beforeKey = currKey;
	//}

	//DWORD flag = keyStroke.Flags;

	//if (retval == ERROR_DEVICE_NOT_CONNECTED)
	//{
	//	Assert(false, "니 패드 뒤짐");
	//}

	//if (currKey == 0)
	//{
	//	return;
	//}
	//
	//if (keyStroke.Flags == XINPUT_KEYSTROKE_KEYDOWN) // 패드를 눌렀을때
	//{
	//	for (const auto& e : _keyComponentSet)
	//	{
	//		if (e == nullptr) continue;
	//		e->onKeyDown(currKey, *(e->GetObject()));
	//	}
	//
	//}
	//else if(keyStroke.Flags == XINPUT_KEYSTROKE_KEYUP) // 패드를 뗐을때
	//{

	//	for (const auto& e : _keyComponentSet)
	//	{
	//		if (e == nullptr) continue;
	//		e->onKeyUp(currKey, *(e->GetObject()));
	//	}
	//	beforeKey = 0;
	//}
	//else if (keyStroke.Flags == 5 || retval == ERROR_EMPTY) // 누르고 있을 경우의 flags 값이 정의 되지 않은 5가 되어있음. 대신 키 값은 0이 아니라서 stay 판별이 가능함.
	//{	
	//	for (const auto& e : _keyComponentSet)
	//	{
	//		if (e == nullptr) continue;
	//		e->onKeyStay(currKey, *(e->GetObject()));
	//	}
	//}
}

void dod::KeyManager::PadWave() // 진동
{
	XINPUT_VIBRATION  vibration = { 0 };
	vibration.wLeftMotorSpeed = 60000; // 진동 강도 좌우 따로 넣어줘야함
	vibration.wRightMotorSpeed = 60000;
	XInputSetState(0, &vibration); // 진동 값을 연결된 컨트롤러로 보냄 (컨트롤러 인덱스, 진동 정보)
}
