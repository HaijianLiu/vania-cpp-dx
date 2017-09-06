
#ifndef _SCENE_GAME_OVER_H_
#define _SCENE_GAME_OVER_H_

class SceneGameOver : public Scene {
private:

public:
	// UIObject
	UIObject* uiGameOverText;

	float restartDelay = 3.0f;

	SceneGameOver();
	~SceneGameOver();

	void Start();
	void Update();

};

#endif
