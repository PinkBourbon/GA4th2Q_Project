#include <windows.h>
#include <iostream>
#include <conio.h>
#include "Sound.h" 
#include "fmod.hpp" 

FMOD::System* SoundSystem(nullptr);

FMOD::Sound* g_sound[20]; //사운드 배열, 총 갯수

FMOD::Channel* g_channel[20]; //sound의 갯수와 같다.

FMOD_RESULT    result;

unsigned int   version;

Sound::Sound():SFXSoundPlay(false), BGMSoundPlay(false)
{

}

Sound::~Sound()
{

}

/// <summary>
/// 사운드를 만들고 재생함
/// </summary>
/// <param name="soundName">출력하고자 하는 사운드의 enum값</param>
/// <returns>해당 리턴값으로 특정 상태를 확인하는 플래그 형태로 사용</returns>
int Sound::Sound_CreateSound()
{

	result = FMOD::System_Create(&SoundSystem);	// 시스템 객체 생성
	if (result != FMOD_OK) return -1; // 문제 생길시 return -1로 종료 
	result = SoundSystem->init(32, FMOD_INIT_NORMAL, NULL); // 시스템 초기화 : chaneel 32개까지 사용하겠다.
	if (result != FMOD_OK) return -1;
	result = SoundSystem->createSound("TitleMusic.mp3", FMOD_LOOP_NORMAL, nullptr, &g_sound[TITLE_BGM]); // MP3 파일로부터 sound 생성, 여기서 파일 받아온다.
	if (result != FMOD_OK) return -1; //위 사운드를 만드는 코드를 참고하여 새 사운드를 만들 수 있다.
	result = SoundSystem->createSound("TunnelMusic.mp3", FMOD_LOOP_NORMAL, nullptr, &g_sound[2]); // MP3 파일로부터 sound 생성, 여기서 파일 받아온다.
	if (result != FMOD_OK) return -1; //위 사운드를 만드는 코드를 참고하여 새 사운드를 만들 수 있다.
	result = SoundSystem->createSound("BossMusic.mp3", FMOD_LOOP_NORMAL, nullptr, &g_sound[3]); // MP3 파일로부터 sound 생성, 여기서 파일 받아온다.
	if (result != FMOD_OK) return -1; //위 사운드를 만드는 코드를 참고하여 새 사운드를 만들 수 있다.
}

int Sound::Sound_PlaySound(int soundName)
{
	switch (soundName) //재생 파트, 아래 PlatSound를 추가 하면 새 사운드를 재생 할 수 있다.
	{
		case TITLE_BGM: //추가 가능
			result = SoundSystem->playSound(g_sound[TITLE_BGM], nullptr, false, &g_channel[TITLE_BGM]); //soundName에 따라 재생, 채널을 이용하므로 동시 재생도 가능
			break;	
		case 2: //추가 가능
			result = SoundSystem->playSound(g_sound[2], nullptr, false, &g_channel[2]); //soundName에 따라 재생, 채널을 이용하므로 동시 재생도 가능
			break;	
		case 3: //추가 가능
			result = SoundSystem->playSound(g_sound[3], nullptr, false, &g_channel[3]); //soundName에 따라 재생, 채널을 이용하므로 동시 재생도 가능
			break;
		default:
			break;
	}
	// TODO:SATA - 들어올 일이 없을 것 같은데.. 처리 해야 함
	return -1;
}


void Sound::Sound_SoundPause(int soundname) //배경음악 일시정지 파트, BGM : 4개, SFX : 14개 
{
	g_channel[soundname]->setPaused(true);
}
//void Sound_SoundStop(int soundname) //배경음악 일시정지 파트, BGM : 4개, SFX : 14개 
//{
//	g_channel[soundname]->stop();
//}
void Sound::Sound_SoundPauseRelease(int soundname) //
{
	g_channel[soundname]->setPaused(false);
}
void Sound::Sound_SFXAllPause() //효과음 일시정지 파트
{
	if (SFXSoundPlay != 0)
	{
		for (int i = BGM_SIZE+1; i < (BGM_SIZE + SFX_SIZE+1); i++)
		{
			g_channel[i]->setPaused(false);
		}
		SFXSoundPlay = false;
	}
	else
	{
		for (int i = BGM_SIZE+1; i < (BGM_SIZE + SFX_SIZE+1); i++)
		{
			g_channel[i]->setPaused(true);
		}
		SFXSoundPlay = true;
	}
}

void Sound::Sound_BGMAllPause() 
{
	if (BGMSoundPlay != 0)
	{
		for (int i = 0; i < BGM_SIZE+1; i++)
		{
			g_channel[i]->setPaused(false);
		}
			BGMSoundPlay = false;
	}
	else
	{	
		for (int i = 0; i < BGM_SIZE+1; i++)
		{
			g_channel[i]->setPaused(true);
		}
			BGMSoundPlay = true;
	}
}

//void Sound::Sound_SFXAllPauseRelease() //효과음 일시정지 파트
//{
//	
//}

void Sound::Sound_BGMUpCtl() //볼륨 조절 파트
{
	float volumeSize = 0.6f;
	volumeSize += 0.2f;
	for (int i = 0; i < BGM_SIZE; i++)
	{
		g_channel[i]->setVolume(volumeSize);
		g_channel[i]->getVolume(&volumeSize);
	}
}
void Sound::Sound_BGMDownCtl() //볼륨 조절 파트
{
	float volumeSize = 0.6f;
	volumeSize -= 0.2f;
	for (int i = 0; i < BGM_SIZE; i++)
	{
		g_channel[i]->setVolume(volumeSize);
		g_channel[i]->getVolume(&volumeSize);
	}
}

void Sound::Sound_SFXUpCtl() //효과음 조절 파트
{
	float volumeSize = 0.6f;
	volumeSize += 0.2f;
	for (int i = BGM_SIZE; i < BGM_SIZE + SFX_SIZE; i++) //효과음만 조절 파트
	{
		g_channel[i]->setVolume(volumeSize);
		g_channel[i]->getVolume(&volumeSize);
	}
}

void Sound::Sound_SFXDownCtl() //효과음 조절 파트
{
	float volumeSize = 0.6f;
	volumeSize -= 0.2f;
	for (int i = BGM_SIZE; i < BGM_SIZE + SFX_SIZE; i++) //효과음만 조절 파트
	{
		g_channel[i]->setVolume(volumeSize);
		g_channel[i]->getVolume(&volumeSize);
	}
}

void Sound::Sound_AllPlay() //게임 시작시 모든 사운드를 플레이
{
	Sound_PlaySound(TITLE_BGM);
	Sound_SoundPause(TITLE_BGM);
}


