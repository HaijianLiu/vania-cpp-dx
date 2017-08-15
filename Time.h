
#ifndef _TIME_H_
#define _TIME_H_

class Time {
private:
	DWORD lastTime = 0;
	DWORD currentTime = 0;
	// FPS debug
	DWORD lastFPSTime = 0;
	DWORD frameCounter = 0;


public:
	float deltaTime = 0;
	// FPS debug
	int countFPS = 0;

	Time();
	~Time();
	void Start();
	void SetTime();
	void Update();
	bool CheckFPS(int frameRate);
};


#endif
