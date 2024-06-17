#include <windows.h>
#include <iostream>
#include <conio.h>
#include "Macro.h"
#include "SoundManager.h"




dod::SoundManager::SoundManager() :_SFXSoundPlay(false), _BGMSoundPlay(false), SoundSystem(nullptr), volumeSize(1)
{

}

dod::SoundManager::~SoundManager()
{

}

void dod::SoundManager::Sound_Initalation()
{
	FMOD_RESULT result = FMOD::System_Create(&SoundSystem);	// �ý��� ��ü ����
	Assert(result == FMOD_OK, "�ý��� ���� ����");
	result = SoundSystem->init(40, FMOD_INIT_NORMAL, NULL); // �ý��� �ʱ�ȭ : chaneel 40������ ����ϰڴ�.
	Assert(result == FMOD_OK, "�ý��� �ʱ�ȭ ����");
}
/// <summary>
/// ���带 ����� �����
/// </summary>
/// <param name="soundName">����ϰ��� �ϴ� ������ enum��</param>
/// <returns>�ش� ���ϰ����� Ư�� ���¸� Ȯ���ϴ� �÷��� ���·� ���</returns>
int dod::SoundManager::Sound_CreateBGMSound(const char* soundName, eSoundName SoundType)
{
	//BMG ��Ʈ �� 3��
	//Assert(_sound[(int)SoundType] == nullptr, "Sound�� ������� �Ұ����մϴ�."); //������ ������ �ٽ� nullptr�� �ٲ���� �Ѵ�.
	FMOD_RESULT result = SoundSystem->createSound(soundName, FMOD_LOOP_NORMAL, nullptr, &_sound[(int)SoundType]); // MP3 ���Ϸκ��� sound ����, ���⼭ ���� �޾ƿ´�.
	Assert(result == FMOD_OK, "Sound ���� ����");
	return result;
}

int dod::SoundManager::Sound_CreateSFXSound(const char* soundName, eSoundName SoundType)
{
	//Assert(_sound[(int)SoundType] == nullptr, "Sound�� ������� �Ұ����մϴ�."); //������ ������ �ٽ� nullptr�� �ٲ���� �Ѵ�.
	FMOD_RESULT result = SoundSystem->createSound(soundName, FMOD_LOOP_OFF, nullptr, &_sound[(int)SoundType]); // MP3 ���Ϸκ��� sound ����, ���⼭ ���� �޾ƿ´�.
	Assert(result == FMOD_OK, "Sound ���� ����");
	return result;
}

int dod::SoundManager::Sound_PlaySound(eSoundName soundName)
{
	FMOD_RESULT result = SoundSystem->playSound(_sound[soundName], nullptr, false, &_channel[soundName]);
	Assert(result == FMOD_OK, "���� ��� ����");
	_channel[soundName]->setVolume(volumeSize);
	//_channel[soundName]->getVolume(&volumeSize);
	
	return 0;	
}


void dod::SoundManager::Sound_SoundPause(int soundname) //������� �Ͻ����� ��Ʈ, BGM : 3��, SFX : 36�� 
{
	_channel[soundname]->setPaused(true);
}

void dod::SoundManager::Sound_SoundPauseRelease(int soundname)
{
	_channel[soundname]->setPaused(false);
}
void dod::SoundManager::Sound_SFXAllPause() //ȿ���� �Ͻ����� ��Ʈ
{
	if (_SFXSoundPlay != 0)
	{
		for (int i = BGM_SIZE + 1; i < (BGM_SIZE + SFX_SIZE + 1); i++)
		{
			_channel[i]->setPaused(false);
		}
		_SFXSoundPlay = false;
	}
	else
	{
		for (int i = BGM_SIZE + 1; i < (BGM_SIZE + SFX_SIZE + 1); i++)
		{
			_channel[i]->setPaused(true);
		}
		_SFXSoundPlay = true;
	}
}

void dod::SoundManager::Sound_BGMAllPause() // BGM �Ͻ����� ��Ʈ
{
	if (_BGMSoundPlay != 0)
	{
		for (int i = 0; i < BGM_SIZE + 1; i++)
		{
			_channel[i]->setPaused(false);
		}
		_BGMSoundPlay = false;
	}
	else
	{
		for (int i = 0; i < BGM_SIZE + 1; i++)
		{
			_channel[i]->setPaused(true);
		}
		_BGMSoundPlay = true;
	}
}

void dod::SoundManager::Sound_BGMUpCtl(eSoundName soundName) //����� ���� ��Ʈ
{
	//float volumeSize = 0.6f;
	//volumeSize += 0.2f;
	//for (int i = 0; i < BGM_SIZE; i++)
	//{
	//	_channel[i]->setVolume(volumeSize);
	//	_channel[i]->getVolume(&volumeSize);
	//}

	float volumeSize = 0.8f;
	//volumeSize += 0.2f;
	_channel[(int)soundName]->setVolume(volumeSize);
	_channel[(int)soundName]->getVolume(&volumeSize);
}
void dod::SoundManager::Sound_BGMDownCtl(eSoundName soundName) //����� ���� ��Ʈ
{
	/*float volumeSize = 0.6f;
	volumeSize -= 0.2f;
	for (int i = 0; i < BGM_SIZE; i++)
	{
		_channel[i]->setVolume(volumeSize);
		_channel[i]->getVolume(&volumeSize);
	}*/

	float volumeSize = 0.8f;
	//volumeSize -= 0.2f;
	_channel[(int)soundName]->setVolume(volumeSize);
	_channel[(int)soundName]->getVolume(&volumeSize);
}

void dod::SoundManager::Sound_SFXUpCtl() //ȿ���� ���� ��Ʈ
{
	float volumeSize = 0.6f;
	volumeSize += 0.2f;
	for (int i = BGM_SIZE; i < BGM_SIZE + SFX_SIZE; i++) //ȿ������ ���� ��Ʈ
	{
		_channel[i]->setVolume(volumeSize);
		_channel[i]->getVolume(&volumeSize);
	}
}

void dod::SoundManager::Sound_SFXDownCtl() //ȿ���� ���� ��Ʈ
{
	float volumeSize = 0.6f;
	volumeSize -= 0.2f;
	for (int i = BGM_SIZE; i < BGM_SIZE + SFX_SIZE; i++) //ȿ������ ���� ��Ʈ
	{
		_channel[i]->setVolume(volumeSize);
		_channel[i]->getVolume(&volumeSize);
	}
}

void dod::SoundManager::Sound_AllMute()
{
	float volumeSize = 0;
	for (int i = 0; i < BGM_SIZE + SFX_SIZE; i++)
	{
		_channel[i]->setVolume(volumeSize);
	}
}

void dod::SoundManager::Sound_AllPlay() //���� ���۽� ��� ���带 �÷���
{
	Sound_PlaySound(MAINLOBBY_BGM);
	Sound_SoundPause(MAINLOBBY_BGM);
}

void dod::SoundManager::SoundRelease()
{
	FMOD_RESULT result = SoundSystem->release();
	Assert(result == FMOD_OK, "�ý��� Release ����");
}

void dod::SoundManager::Sound_BGMpause(eSoundName soundName)
{
	//static bool isSoundPause = false;
	//if (isSoundPause == false)
	//{
	//}
	_channel[(int)soundName]->setPaused(true);

}

void dod::SoundManager::Sound_SFXpause(eSoundName soundName)
{

}
