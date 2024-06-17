#pragma once
#include "GameObject.h"
#include "Subset.h"
#include "Vector3.h"
#include "map"

#define DICE_CAPCITY 6

class TitleScene;
class SceneManager;
class TestDice;
class StartCutScene;
class MainGame;
class BossArmCoverage;

namespace dod
{
	class RenderSprite;
}

enum class ePlayerImageList
{
	PLAYERMAIN,
	PLAYERWALK,
	PLAYERJUMP,
	PLAYERHIT,
	PLAYERDIE,
	PLAYERATTACK,
	PLAYERROLLING,
	PLAYERSKILL
};

class TestPlayer : public dod::GameObject
{
	friend class TestAttack;
	friend class UIController;
public:
	TestPlayer();
	~TestPlayer();
public:
	virtual void OnCreate();
	virtual void OnEnable();

	virtual void OnUpdate();

	virtual void OnDisable();
	virtual void OnRelease();

public:
	bool addDice(TestDice* dice);
	void DiceCut();
	void AdjustHP(int damage);
	bool GetControlable();
	void SetScene(SceneManager* sceneManager);
	int GetDiceNumber(int index);
	void SetDiceNumber(int index, int value);
	bool GetSpecialAttack();

	int HP;
private:
	void Dash();
	void HitPlayer();
	void SpecialAttack();
	void CreateDiceSubset();	// _diceNumber로 부터 주사위 부분집합을 만들고 _diceSubsets에 넣는 함수 -23.2.16.안준용
	void CleanMydice();			// _diceSubsets[10]에 빈 공간이 생기면 앞으로 당겨주는 함수

private:
	int _retryPicker;
	bool _isDied;

	bool _dashed;
	bool _hitPlayer;
	bool _specialAttack;
	bool _isDeadSoundPlay;
	bool _isDashCoolDown;

	bool _hitable;
	bool _controlable;
	int _diceCount;
	int _diceNumber[DICE_CAPCITY];
	int _speed;
	int _dashSpeed;
	int _initSpeed;
	int _subsetCount;

	dod::Vector3 _direction;
	dod::Subset _diceSubsets[10];
	GameObject* _pRetryPrinter;
	GameObject* _pYesPrinter;
	GameObject* _pNoPrinter;
	GameObject* _pNamePrinter;
	GameObject* _pHPPrinter;
	GameObject* _HaveDicePrinter[DICE_CAPCITY];
	GameObject* _DiceNumberPrinter[DICE_CAPCITY];
	dod::RenderSprite* _pSpritePrint;
	std::map<ePlayerImageList, int> _imageResourceManagerMap;

	//dod::RenderSprite* retryPrinter;
	dod::RenderSprite* _pYesPrinterSprite;
	dod::RenderSprite* _pNoPrinterSprite;
	std::map<int, int> _yesButtonResourceManagerMap;
	std::map<int, int> _noButtonResourceManagerMap;
	SceneManager* _psceneManager;

	BossArmCoverage* _bossArmCoverageL;
	BossArmCoverage* _bossArmCoverageR;
};