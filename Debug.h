
#ifdef _DEBUG

#ifndef _DEBUG_H_
#define _DEBUG_H_

class Debug {
private:
	SceneManager* sceneManager;
	Time* time;

	LPD3DXFONT font = NULL;
	RECT rect = {0,0,SCREEN_WIDTH,SCREEN_HEIGHT};

	std::stringstream sout;

public:
	Debug(SceneManager* sceneManager);
	~Debug();

	void Start();
	void Draw();
};

#endif

#endif
