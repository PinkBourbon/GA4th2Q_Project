#pragma once

enum eKeyCode //��ư ������ ����ü�� ����
{

	// ����Ű �Է°�
	UP,
	DOWN,
	LEFT,
	RIGHT,

	// ���� �Է°�
	SPACE,

	// ���콺 �Է°� => �߰� ����


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

//typedef struct tagKeyState // ��ư�� �Է��� ������ ����ü keystate
//{
//	short sKey;
//	bool Pushed; // Ű�� ������ ������ True
//	bool Pusing; // Ű�� �����ִ� ���¿��� True ��ȯ
//	bool Popped; // Ű�� ���� ������ ��ȯ
//	struct tagKeyState() : sKey(0), Pushed(false), Pusing(false), Popped(false){}
//
//}KEYSTATE;