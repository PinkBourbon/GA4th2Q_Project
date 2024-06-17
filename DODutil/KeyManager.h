#pragma once
#include <windows.h>
#include <unordered_set>
#include <unordered_map>
#include <xinput.h>
#include "KeyComponent.h"
 // 패드 연결용 전처리

#pragma comment(lib, "xinput.lib")
//#include "KeyData.h"
//#include "Transform.h"


// 싱글톤 패턴 : 단일 객체 관리 방법
// - 인스턴스를 호출 시 처음 호출 하는 경우 인스턴스를 생성하고 생성 된 인스턴스를 반환 한다.
// - 인스턴스를 호출 시 이전에 호출되어 생성이 되어 있는 경우 그 생성 되어 있는 인스턴스를 반환 한다.

namespace dod {

	
	class KeyManager
	{
	public:
		KeyManager(HWND hWnd);
		~KeyManager();

		// 모든 키값을 다 받아오고 아래 함수의 bool 값으로 

		void KeyInput(); // 외부에서 키입력을 체크할때 호출할 함수

		//게임 매니저의 컴포넌트를 등록할때 사용하는 함수 (콜백함수가 들어있는 클래스)
		void EnrollComponent(KeyComponent* keycomponent); 
		//위를 해제할때
		void DisenrollComponent(KeyComponent* keycomponent); 

		// 패드 입력 부분
		void PadInput();

		void PadState();

		void PadWave();

	private:
		template<int KEYVALUE>
		void KeyCheck();
		
		void PadCheck();

		void StickMoveCheck(XINPUT_STATE& padState);

		void TriggerClickCheck(XINPUT_STATE& padState);

		template<eButtonCode code> void InputCallBack(KeyInfo& keyInfo, bool isDown);

		void MouseClick();
		void GetMousePos();
		void MouseCheck(int check, POINT mousePoint);

		void InitializeKeyMapping();
	private:

		bool YetKeyState;

		POINT _mousePoint;

		HWND _hWnd;

		std::unordered_set<KeyComponent*> _keyComponentSet;
		std::unordered_map<unsigned int,eButtonCode> _keyMapping;

	};

	template<eButtonCode code>
	void dod::KeyManager::InputCallBack(KeyInfo& keyInfo, bool isDown)
	{
		static bool isButtonDown = false;
		if (isDown)
		{
			if (isButtonDown == false)
			{
				for (const auto& e : _keyComponentSet)
				{
					e->onKeyDown(keyInfo, *(e->GetObject()));
				}
				isButtonDown = true;
			}
			else
			{
				for (const auto& e : _keyComponentSet)
				{
					e->onKeyStay(keyInfo, *(e->GetObject()));
				}
			}
		}
		else
		{
			if (isButtonDown == true)
			{
				for (const auto& e : _keyComponentSet)
				{
					e->onKeyUp(keyInfo, *(e->GetObject()));
				}
				isButtonDown = false;
			}
		}
	}

	template<int KEYVALUE>
	void dod::KeyManager::KeyCheck()
	{
		bool isDownState = GetAsyncKeyState(KEYVALUE) & 0x8001; // 현재 키 입력을 저장
		static bool isYetKeyDown = false;
		eButtonCode code = (*(_keyMapping.find(KEYVALUE + 0x8000))).second; //0x8000을 더하는 이유는 패드에서의 겹치는 값을 피해기 위한 매직 넘버를 더함.
		KeyInfo key(code); // 기본생성자가 없기 때문에 생성자를 호출 할 수 있도록 알맞은 매개변수를 전달

		if (isDownState == true && isYetKeyDown == true)
		{
			isYetKeyDown = true;
			for (const auto& e : _keyComponentSet) // 컨테이너를 순회하면서 
			{
				if (e == nullptr) continue;
				e->onKeyStay(key, *(e->GetObject())); // 각 요소 e에 대해 onKeyStay를 콜백해줌
			}
			// 이후에 각 컴포넌트를 넣어주는 방법을 알아봐야함 검색하면 관련 std 나옴
		}
		else if (isDownState == true && isYetKeyDown == false)
		{
			isYetKeyDown = true;
			for (const auto& e : _keyComponentSet)
			{
				if (e == nullptr) continue;
				e->onKeyDown(key, *(e->GetObject()));
				// 입력할 때 무조건 stay를 넣고 싶다면 여기서 합치면 된다.
			}
		}
		else if (isDownState == false && isYetKeyDown == true)
		{
			isYetKeyDown = false;
			for (const auto& e : _keyComponentSet)
			{
				if (e == nullptr) continue;
				e->onKeyUp(key, *(e->GetObject()));
			}
		}
	}

}