
#ifdef _DEBUG

#ifndef _DEBUG_H_
#define _DEBUG_H_

class Debug {
private:
	LPD3DXFONT font = NULL;

public:
	Scene* scene;
	Time* time;

	Debug(Scene* scene);
	~Debug();

	void Start();
	void Draw();
};

#endif

#endif
