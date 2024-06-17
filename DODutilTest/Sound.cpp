#include <windows.h>
#include <iostream>
#include <conio.h>
#include "Sound.h" 
#include "fmod.hpp" 

FMOD::System* SoundSystem(nullptr);

FMOD::Sound* g_sound[20]; //���� �迭, �� ����

FMOD::Channel* g_channel[20]; //sound�� ������ ����.

FMOD_RESULT    result;

unsigned int   version;

Sound::Sound():SFXSoundPlay(false), BGMSoundPlay(false)
{

}

Sound::~Sound()
{

}

/// <summary>
/// ���带 ����� �����
/// </summary>
/// <param name="soundName">����ϰ��� �ϴ� ������ enum��</param>
/// <returns>�ش� ���ϰ����� Ư�� ���¸� Ȯ���ϴ� �÷��� ���·� ���</returns>
int Sound::Sound_CreateSound()
{

	result = FMOD::System_Create(&SoundSystem);	// �ý��� ��ü ����
	if (result != FMOD_OK) return -1; // ���� ����� return -1�� ���� 
	result = SoundSystem->init(32, FMOD_INIT_NORMAL, NULL); // �ý��� �ʱ�ȭ : chaneel 32������ ����ϰڴ�.
	if (result != FMOD_OK) return -1;
	result = SoundSystem->createSound("TitleMusic.mp3", FMOD_LOOP_NORMAL, nullptr, &g_sound[TITLE_BGM]); // MP3 ���Ϸκ��� sound ����, ���⼭ ���� �޾ƿ´�.
	if (result != FMOD_OK) return -1; //�� ���带 ����� �ڵ带 �����Ͽ� �� ���带 ���� �� �ִ�.
	result = SoundSystem->createSound("TunnelMusic.mp3", FMOD_LOOP_NORMAL, nullptr, &g_sound[2]); // MP3 ���Ϸκ��� sound ����, ���⼭ ���� �޾ƿ´�.
	if (result != FMOD_OK) return -1; //�� ���带 ����� �ڵ带 �����Ͽ� �� ���带 ���� �� �ִ�.
	result = SoundSystem->createSound("BossMusic.mp3", FMOD_LOOP_NORMAL, nullptr, &g_sound[3]); // MP3 ���Ϸκ��� sound ����, ���⼭ ���� �޾ƿ´�.
	if (result != FMOD_OK) return -1; //�� ���带 ����� �ڵ带 �����Ͽ� �� ���带 ���� �� �ִ�.
}

int Sound::Sound_PlaySound(int soundName)
{
	switch (soundName) //��� ��Ʈ, �Ʒ� PlatSound�� �߰� �ϸ� �� ���带 ��� �� �� �ִ�.
	{
		case TITLE_BGM: //�߰� ����
			result = SoundSystem->playSound(g_sound[TITLE_BGM], nullptr, false, &g_channel[TITLE_BGM]); //soundName�� ���� ���, ä���� �̿��ϹǷ� ���� ����� ����
			break;	
		case 2: //�߰� ����
			result = SoundSystem->playSound(g_sound[2], nullptr, false, &g_channel[2]); //soundName�� ���� ���, ä���� �̿��ϹǷ� ���� ����� ����
			break;	
		case 3: //�߰� ����
			result = SoundSystem->playSound(g_sound[3], nullptr, false, &g_channel[3]); //soundName�� ���� ���, ä���� �̿��ϹǷ� ���� ����� ����
			break;
		default:
			break;
	}
	// TODO:SATA - ���� ���� ���� �� ������.. ó�� �ؾ� ��
	return -1;
}


void Sound::Sound_SoundPause(int soundname) //������� �Ͻ����� ��Ʈ, BGM : 4��, SFX : 14�� 
{
	g_channel[soundname]->setPaused(true);
}
//void Sound_SoundStop(int soundname) //������� �Ͻ����� ��Ʈ, BGM : 4��, SFX : 14�� 
//{
//	g_channel[soundname]->stop();
//}
void Sound::Sound_SoundPauseRelease(int soundname) //
{
	g_channel[soundname]->setPaused(false);
}
void Sound::Sound_SFXAllPause() //ȿ���� �Ͻ����� ��Ʈ
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

//void Sound::Sound_SFXAllPauseRelease() //ȿ���� �Ͻ����� ��Ʈ
//{
//	
//}

void Sound::Sound_BGMUpCtl() //���� ���� ��Ʈ
{
	float volumeSize = 0.6f;
	volumeSize += 0.2f;
	for (int i = 0; i < BGM_SIZE; i++)
	{
		g_channel[i]->setVolume(volumeSize);
		g_channel[i]->getVolume(&volumeSize);
	}
}
void Sound::Sound_BGMDownCtl() //���� ���� ��Ʈ
{
	float volumeSize = 0.6f;
	volumeSize -= 0.2f;
	for (int i = 0; i < BGM_SIZE; i++)
	{
		g_channel[i]->setVolume(volumeSize);
		g_channel[i]->getVolume(&volumeSize);
	}
}

void Sound::Sound_SFXUpCtl() //ȿ���� ���� ��Ʈ
{
	float volumeSize = 0.6f;
	volumeSize += 0.2f;
	for (int i = BGM_SIZE; i < BGM_SIZE + SFX_SIZE; i++) //ȿ������ ���� ��Ʈ
	{
		g_channel[i]->setVolume(volumeSize);
		g_channel[i]->getVolume(&volumeSize);
	}
}

void Sound::Sound_SFXDownCtl() //ȿ���� ���� ��Ʈ
{
	float volumeSize = 0.6f;
	volumeSize -= 0.2f;
	for (int i = BGM_SIZE; i < BGM_SIZE + SFX_SIZE; i++) //ȿ������ ���� ��Ʈ
	{
		g_channel[i]->setVolume(volumeSize);
		g_channel[i]->getVolume(&volumeSize);
	}
}

void Sound::Sound_AllPlay() //���� ���۽� ��� ���带 �÷���
{
	Sound_PlaySound(TITLE_BGM);
	Sound_SoundPause(TITLE_BGM);
}


