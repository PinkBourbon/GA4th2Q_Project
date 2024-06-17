#pragma once
#include <windows.h>
#include <unordered_set>
#include <unordered_map>
#include <xinput.h>
#include "KeyComponent.h"
 // �е� ����� ��ó��

#pragma comment(lib, "xinput.lib")
//#include "KeyData.h"
//#include "Transform.h"


// �̱��� ���� : ���� ��ü ���� ���
// - �ν��Ͻ��� ȣ�� �� ó�� ȣ�� �ϴ� ��� �ν��Ͻ��� �����ϰ� ���� �� �ν��Ͻ��� ��ȯ �Ѵ�.
// - �ν��Ͻ��� ȣ�� �� ������ ȣ��Ǿ� ������ �Ǿ� �ִ� ��� �� ���� �Ǿ� �ִ� �ν��Ͻ��� ��ȯ �Ѵ�.

namespace dod {

	
	class KeyManager
	{
	public:
		KeyManager(HWND hWnd);
		~KeyManager();

		// ��� Ű���� �� �޾ƿ��� �Ʒ� �Լ��� bool ������ 

		void KeyInput(); // �ܺο��� Ű�Է��� üũ�Ҷ� ȣ���� �Լ�

		//���� �Ŵ����� ������Ʈ�� ����Ҷ� ����ϴ� �Լ� (�ݹ��Լ��� ����ִ� Ŭ����)
		void EnrollComponent(KeyComponent* keycomponent); 
		//���� �����Ҷ�
		void DisenrollComponent(KeyComponent* keycomponent); 

		// �е� �Է� �κ�
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
		bool isDownState = GetAsyncKeyState(KEYVALUE) & 0x8001; // ���� Ű �Է��� ����
		static bool isYetKeyDown = false;
		eButtonCode code = (*(_keyMapping.find(KEYVALUE + 0x8000))).second; //0x8000�� ���ϴ� ������ �е忡���� ��ġ�� ���� ���ر� ���� ���� �ѹ��� ����.
		KeyInfo key(code); // �⺻�����ڰ� ���� ������ �����ڸ� ȣ�� �� �� �ֵ��� �˸��� �Ű������� ����

		if (isDownState == true && isYetKeyDown == true)
		{
			isYetKeyDown = true;
			for (const auto& e : _keyComponentSet) // �����̳ʸ� ��ȸ�ϸ鼭 
			{
				if (e == nullptr) continue;
				e->onKeyStay(key, *(e->GetObject())); // �� ��� e�� ���� onKeyStay�� �ݹ�����
			}
			// ���Ŀ� �� ������Ʈ�� �־��ִ� ����� �˾ƺ����� �˻��ϸ� ���� std ����
		}
		else if (isDownState == true && isYetKeyDown == false)
		{
			isYetKeyDown = true;
			for (const auto& e : _keyComponentSet)
			{
				if (e == nullptr) continue;
				e->onKeyDown(key, *(e->GetObject()));
				// �Է��� �� ������ stay�� �ְ� �ʹٸ� ���⼭ ��ġ�� �ȴ�.
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