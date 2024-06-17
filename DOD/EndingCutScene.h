#pragma once
#include <map>

namespace dod
{
	class GameEngine;
	class GameObject;
	struct Transform;
	struct KeyComponent;
	class RenderSprite;
}

class ImageViewer;
class SceneManager;
class TitleScene;

class EndingCutScene
{
public:
	EndingCutScene();
	~EndingCutScene();
public:
	void CutScene();
	void InitializeScene(dod::GameEngine* engine, SceneManager* sceneManager);

	bool activecheck;
private:

	SceneManager* sceneManager;
	dod::GameEngine* _engineptr;

	ImageViewer* imageViewer;

	dod::RenderSprite* _pCutSceneSprite;
	//std::map<int, int> _pCutSceneSpriteMap;
};