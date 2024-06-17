#include <windows.h>
#include "GameProcess.h"

#pragma comment(lib,"DODd2d.lib")
#pragma comment(lib,"DODutil.lib")
#pragma comment(lib, "DODengine.lib")

int main()
{
	// 게임 진행 클래스
	// 내부에서 윈도 생성과 메시지 콜백을 처리한다.
	// 또한 그래픽스 엔진 등을 포함한다.

	//g = new GameProcess();
	GameProcess* gameProcess = new GameProcess();
	gameProcess->Initialize();
	gameProcess->Loop();
	gameProcess->Finalize();

	return 0; // (int)msg.wParam;
}