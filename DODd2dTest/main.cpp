#include <windows.h>
#include "GameProcess.h"

#pragma comment(lib,"DODd2d.lib")
#pragma comment(lib,"DODutil.lib")
#pragma comment(lib, "DODengine.lib")

int main()
{
	// ���� ���� Ŭ����
	// ���ο��� ���� ������ �޽��� �ݹ��� ó���Ѵ�.
	// ���� �׷��Ƚ� ���� ���� �����Ѵ�.

	//g = new GameProcess();
	GameProcess* gameProcess = new GameProcess();
	gameProcess->Initialize();
	gameProcess->Loop();
	gameProcess->Finalize();

	return 0; // (int)msg.wParam;
}