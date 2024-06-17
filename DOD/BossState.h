#pragma once


namespace dod
{
	enum class eBossState
	{
		BOSSSTART,
		BOSSIDLE,
		BOSSSTONE,
		BOSSSUNKEN,
		BOSSSWIGATTACK,
		BOSSBREATH,
		BOSSHIT,
		BOSSDIE
	};

	enum class eBossPattern
	{
		IDLE,
		ATTACK,
		ATTACKL,
		ATTACKR,
		BREATHE,
	};
}