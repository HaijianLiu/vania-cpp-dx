
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

	unsigned int selected = 0;

	SceneTitle();
	~SceneTitle();

	void Start();
	void Update();

};

#endif
