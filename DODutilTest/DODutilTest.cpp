#include <iostream>
#include "KeyManager.h"
#include "Sound.h"
#include "GameObject.h"

#pragma comment(lib,"DODutil.lib")


int main()
{
	HWND consoleHWND = GetConsoleWindow();
	Sound* testsound = new Sound();

	dod::KeyManager* keymanager = new dod::KeyManager(consoleHWND);
	dod::KeyComponent* keycomponent = new dod::KeyComponent();
	dod::KeyComponent* soundkeycomponent = new dod::KeyComponent();
	keycomponent->onKeyDown = [](const dod::KeyInfo& key, const dod::GameObject& thisObject) {std::cout << "KeyDown " << key.key << "x " << key.x << ", y" << key.y << std::endl; };
	keycomponent->onKeyStay = [](const dod::KeyInfo& key, const dod::GameObject& thisObject) {std::cout << "KeyStay " << key.key << "x " << key.x << ", y" << key.y << std::endl; };
	keycomponent->onKeyUp = [](const dod::KeyInfo& key, const dod::GameObject& thisObject) {std::cout << "KeyUp " << key.key << "x " << key.x << ", y" << key.y << std::endl; };

	soundkeycomponent->onKeyDown = [&](const dod::KeyInfo& key, const dod::GameObject& thisObject) // 콜백에 뭐할지 정의해주는 놈이다.
	{
		if (key.key == VK_LEFT)
		{
			testsound->Sound_BGMAllPause();
		}
		else if(key.key == VK_RIGHT)
		{
			testsound->Sound_SFXAllPause();
		}
	};
	
	keymanager->EnrollComponent(soundkeycomponent); //이 녀석이 등록을 받는 놈이다
	keymanager->EnrollComponent(keycomponent);

	testsound->Sound_CreateSound();
	//testsound->Sound_PlaySound(1);
	//testsound->Sound_PlaySound(2);
	testsound->Sound_PlaySound(3);
	
	while (true)
	{		
	
		keymanager->PadInput();
		Sleep(13);


	}
}
