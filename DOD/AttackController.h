#pragma once
#include "GameObject.h"
#include "TestAttack.h"

	class GameEngine;
	class TestAttack;
	class TestPlayer;
	class UIController;

	class AttackController : public dod::GameObject
	{
	public:
		AttackController();
		~AttackController();

	public:
		virtual void OnCreate();
		virtual void OnEnable();

		virtual void OnUpdate();

		virtual void OnDisable();
		virtual void OnRelease();

	public:
		eAttackType DecideAttackType();

	private:
		bool _isSkilled;

		TestAttack* _attackPool[5];
		TestPlayer* _player;
		UIController* _uiController;
		int _attackIndex;
	};

