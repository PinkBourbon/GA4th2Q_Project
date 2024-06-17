#pragma once

namespace dod
{
	class GameObject;
	struct Transform;
	struct KeyComponent;
	class RenderSprite;
}

class ImageViewer;

class StartCutScene
{
public:
	StartCutScene();
	~StartCutScene();
public:
	void CutScene();
	void InitializeScene(dod::GameEngine* engine, SceneManager* sceneManager);

	bool activecheck;
private:

	SceneManager* sceneManager;
	dod::GameEngine* _engineptr;

	ImageViewer* imageViewer;

	dod::RenderSprite* _pCutSceneSprite;
	std::map<int, int> _pCutSceneSpriteMap;
};

