#pragma once

enum eKeyCode //버튼 종류를 열거체로 쵸현
{

	// 방향키 입력값
	UP,
	DOWN,
	LEFT,
	RIGHT,

	// 공격 입력값
	SPACE,

	// 마우스 입력값 => 추가 예정


	MAX_KEY
};

const int vk_Count = 0xFF;

enum KeyState
{
	NONE,
	PUSHED,
	PUSING,
	POPPEND
};

//typedef struct tagKeyState // 버튼의 입력을 저장할 구조체 keystate
//{
//	short sKey;
//	bool Pushed; // 키를 누르는 순간만 True
//	bool Pusing; // 키가 눌려있는 상태에서 True 반환
//	bool Popped; // 키를 떼는 순간만 반환
//	struct tagKeyState() : sKey(0), Pushed(false), Pusing(false), Popped(false){}
//
//}KEYSTATE;