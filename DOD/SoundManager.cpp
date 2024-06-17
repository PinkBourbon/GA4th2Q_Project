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
	FMOD_RESULT result = FMOD::System_Create(&SoundSystem);	// 시스템 객체 생성
	Assert(result == FMOD_OK, "시스템 생성 실패");
	result = SoundSystem->init(40, FMOD_INIT_NORMAL, NULL); // 시스템 초기화 : chaneel 40개까지 사용하겠다.
	Assert(result == FMOD_OK, "시스템 초기화 실패");
}
/// <summary>
/// 사운드를 만들고 재생함
/// </summary>
/// <param name="soundName">출력하고자 하는 사운드의 enum값</param>
/// <returns>해당 리턴값으로 특정 상태를 확인하는 플래그 형태로 사용</returns>
int dod::SoundManager::Sound_CreateBGMSound(const char* soundName, eSoundName SoundType)
{
	//BMG 파트 총 3개
	//Assert(_sound[(int)SoundType] == nullptr, "Sound는 재생성이 불가능합니다."); //릴리스 했을때 다시 nullptr로 바꿔줘야 한다.
	FMOD_RESULT result = SoundSystem->createSound(soundName, FMOD_LOOP_NORMAL, nullptr, &_sound[(int)SoundType]); // MP3 파일로부터 sound 생성, 여기서 파일 받아온다.
	Assert(result == FMOD_OK, "Sound 생성 실패");
	return result;
}

int dod::SoundManager::Sound_CreateSFXSound(const char* soundName, eSoundName SoundType)
{
	//Assert(_sound[(int)SoundType] == nullptr, "Sound는 재생성이 불가능합니다."); //릴리스 했을때 다시 nullptr로 바꿔줘야 한다.
	FMOD_RESULT result = SoundSystem->createSound(soundName, FMOD_LOOP_OFF, nullptr, &_sound[(int)SoundType]); // MP3 파일로부터 sound 생성, 여기서 파일 받아온다.
	Assert(result == FMOD_OK, "Sound 생성 실패");
	return result;
}

int dod::SoundManager::Sound_PlaySound(eSoundName soundName)
{
	FMOD_RESULT result = SoundSystem->playSound(_sound[soundName], nullptr, false, &_channel[soundName]);
	Assert(result == FMOD_OK, "사운드 재생 실패");
	_channel[soundName]->setVolume(volumeSize);
	//_channel[soundName]->getVolume(&volumeSize);
	
	return 0;	
}


void dod::SoundManager::Sound_SoundPause(int soundname) //배경음악 일시정지 파트, BGM : 3개, SFX : 36개 
{
	_channel[soundname]->setPaused(true);
}

void dod::SoundManager::Sound_SoundPauseRelease(int soundname)
{
	_channel[soundname]->setPaused(false);
}
void dod::SoundManager::Sound_SFXAllPause() //효과음 일시정지 파트
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

void dod::SoundManager::Sound_BGMAllPause() // BGM 일시정지 파트
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

void dod::SoundManager::Sound_BGMUpCtl(eSoundName soundName) //배경음 조절 파트
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
void dod::SoundManager::Sound_BGMDownCtl(eSoundName soundName) //배경음 조절 파트
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

void dod::SoundManager::Sound_SFXUpCtl() //효과음 조절 파트
{
	float volumeSize = 0.6f;
	volumeSize += 0.2f;
	for (int i = BGM_SIZE; i < BGM_SIZE + SFX_SIZE; i++) //효과음만 조절 파트
	{
		_channel[i]->setVolume(volumeSize);
		_channel[i]->getVolume(&volumeSize);
	}
}

void dod::SoundManager::Sound_SFXDownCtl() //효과음 조절 파트
{
	float volumeSize = 0.6f;
	volumeSize -= 0.2f;
	for (int i = BGM_SIZE; i < BGM_SIZE + SFX_SIZE; i++) //효과음만 조절 파트
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

void dod::SoundManager::Sound_AllPlay() //게임 시작시 모든 사운드를 플레이
{
	Sound_PlaySound(MAINLOBBY_BGM);
	Sound_SoundPause(MAINLOBBY_BGM);
}

void dod::SoundManager::SoundRelease()
{
	FMOD_RESULT result = SoundSystem->release();
	Assert(result == FMOD_OK, "시스템 Release 실패");
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
