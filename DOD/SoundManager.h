#pragma once
#include "..\\DOD\\core\\inc\\fmod.hpp" 

#define BGM_SIZE 3
#define SFX_SIZE 36

namespace dod
{
	enum eSoundName
	{
		MAINLOBBY_BGM,
		STAGE_BGM,
		ENDING_BGM,
		TITLE_BGM,

		WORK_SFX,
		ROLLING_SFX,
		RENDING_SFX,
		PLAYER_HIT_SFX,
		DICE_CAPTURE_SFX,
		PLAYER_NORMALATTACK_SFX,
		PLAYER_SKILL_3COST_SFX,
		PLAYER_SKILL_4COST_SFX,
		PLAYER_SKILL_5COST_FIRST_SFX,
		PLAYER_SKILL_5COST_SECEND_SFX,
		PLAYER_DEAD_SFX,
		BOSS_START_SFX,
		BOSS_ATTACK_SUNKEN_FIRST_SFX,
		BOSS_ATTACK_SUNKEN_SECOND_SFX,
		BOSS_ATTACK_SWING_FIRST_SFX,
		BOSS_ATTACK_BREATH_FIRST_SFX,
		BOSS_ATTACK_BREATH_SECOND_SFX,
		BOSS_ATTACK_BREATH_THIRD_SFX,
		BOSS_ATTACK_STONE_FIRST_SFX,
		BOSS_ATTACK_STONE_SECOND_SFX,
		BOSS_ATTACK_STONE_THIRD_SFX,
		BOSS_NORMAL_HIT_SFX,
		BOSS_SKILL_HIT_SFX,
		DICE_DISTROY_SFX,
		DICE_ROLLING_SFX,
		DICE_DROP_SFX,
		SLOTMACHINE_STAT_SFX,
		MAINLOBBY_SETTING_SFX,
		RETRY_UI_MAKE_SFX,
		RETRY_UI_SELECT_SFX,

	};

	class SoundManager
	{
	public:
		SoundManager();
		~SoundManager();
	public:
		void Sound_Initalation();
		int Sound_CreateBGMSound(const char* soundName, eSoundName SoundType); //���� ����
		int Sound_CreateSFXSound(const char* soundName, eSoundName SoundType); //���� ����
		int Sound_PlaySound(eSoundName soundName); //���� ���
		void Sound_SoundPause(int soundname); //������� �Ͻ�����
		void Sound_SoundPauseRelease(int soundname); //������� �Ͻ�����
		void Sound_SFXAllPause();
		void Sound_BGMAllPause();
		void Sound_BGMUpCtl(eSoundName soundName); //������� ũ�� ����
		void Sound_BGMDownCtl(eSoundName soundName);
		void Sound_SFXUpCtl(); //ȿ���� ũ�� ����
		void Sound_SFXDownCtl();
		void Sound_AllMute();
		void Sound_AllPlay();
		void SoundRelease();
		void Sound_BGMpause(eSoundName soundName);
		void Sound_SFXpause(eSoundName soundName);
		
	public:

		bool _SFXSoundPlay;
		bool _BGMSoundPlay;

		float volumeSize;

	private:

		FMOD::System* SoundSystem;
		FMOD::Sound* _sound[40]; //���� �迭, �� ����
		FMOD::Channel* _channel[40]; //sound�� ������ ����.
	};


};
