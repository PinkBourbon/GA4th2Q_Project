#pragma once


 // �ش� ���̺귯�� �ʿ��ϴٴ� ��

#define BGM_SIZE 2
#define SFX_SIZE 1



class Sound
{

public:
	Sound();
	~Sound();


	int Sound_CreateSound(); //���� ����
	int Sound_PlaySound(int soundName); //���� ���
	void Sound_SoundPause(int soundname); //������� �Ͻ�����
	void Sound_SoundPauseRelease(int soundname); //������� �Ͻ�����
	void Sound_SFXAllPause();
	void Sound_BGMAllPause();
	//void Sound_SFXAllPauseRelease();
	void Sound_BGMUpCtl(); //������� ũ�� ����
	void Sound_BGMDownCtl();
	void Sound_SFXUpCtl(); //ȿ���� ũ�� ����
	void Sound_SFXDownCtl();
	void Sound_AllPlay();


public:

	//bool Sound
	bool SFXSoundPlay;
	bool BGMSoundPlay;

	typedef enum SoundName
	{
		NON,
		TITLE_BGM,
	};

};