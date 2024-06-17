#pragma once
#include <map>

namespace dod
{
	class GameObject;
	class GameEngine;
	class RenderSprite;
};

class GameEmblem
{
public:
	GameEmblem();
	~GameEmblem();

	void Emblemview();
	void InitializeScene(dod::GameEngine* engine, SceneManager* sceneManager);
	void Disabler();

private:
	SceneManager* sceneManager;
	dod::GameEngine* _engineptr;
	dod::GameObject* _emblemObejct;
	dod::GameObject* _Blanker;

	double timer;
	float Transparency = 1;

	dod::RenderSprite* _pBlackBaox;
	dod::RenderSprite* _plogo;
	std::map<int, int> _blackBoxResourceMap;

	// 미리 출력용
	dod::GameObject* _pBossBreath;
	dod::GameObject* _pBoss;
	dod::GameObject* _pArmL;
	dod::GameObject* _pArmR;
	dod::RenderSprite* _pBossBreathSprite;
	std::map<int, int> _bossBreathSpriteMap;
	dod::RenderSprite* _pBossSprite;
	std::map<int, int> _bossSpriteMap;
	dod::RenderSprite* _pArmLSprite;
	std::map<int, int> _bossArmLMap;
	dod::RenderSprite* _pArmRSprite;
	std::map<int, int> _bossArmRMap;
};

