
#ifdef _DEBUG

#ifndef _DEBUG_H_
#define _DEBUG_H_

class Debug {
private:
	Scene* scene;
	Time* time;

	LPD3DXFONT font = NULL;
	RECT rect = {0,0,SCREEN_WIDTH,SCREEN_HEIGHT};

	std::stringstream sout;

public:
	Debug(Scene* scene);
	~Debug();

	void Start();
	void Draw();
};

#endif

#endif
