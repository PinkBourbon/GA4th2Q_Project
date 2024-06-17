#include <iostream>
#include <string>

 #include "GameEngine.h"
 #include "ObjectManager.h"
 #include "SampleTimer.h"

#pragma comment(lib, "DODengine.lib")

int main()
{
	dod::g_GameEngine.GameLoop();
}