#pragma once


 // 해당 라이브러리 필요하다는 뜻

#define BGM_SIZE 2
#define SFX_SIZE 1



class Sound
{

public:
	Sound();
	~Sound();


	int Sound_CreateSound(); //사운드 생성
	int Sound_PlaySound(int soundName); //사운드 출력
	void Sound_SoundPause(int soundname); //배경음악 일시정지
	void Sound_SoundPauseRelease(int soundname); //배경음악 일시정지
	void Sound_SFXAllPause();
	void Sound_BGMAllPause();
	//void Sound_SFXAllPauseRelease();
	void Sound_BGMUpCtl(); //배경음악 크기 조절
	void Sound_BGMDownCtl();
	void Sound_SFXUpCtl(); //효과음 크기 조절
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