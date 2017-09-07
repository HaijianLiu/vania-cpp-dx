
#ifndef _SCENE_TITLE_H_
#define _SCENE_TITLE_H_

class SceneTitle : public Scene {
private:

public:
	// UIObject
	UIObject* uiTitleBG;
	UIObject* uiTitleStart;
	UIObject* uiTitleOption;
	UIObject* uiTitleCredits;

	bool enter = false;
	int selected = 0;
	DWORD lastEnter = 0;
	float enterDelay = 2.0f;

	SceneTitle();
	~SceneTitle();

	void Start();
	void Update();

};

#endif
