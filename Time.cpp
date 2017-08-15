
#include "Engine.h"

Time::Time() {

}

Time::~Time() {

}

void Time::Start() {
	timeBeginPeriod(1);
	this->lastTime = timeGetTime();
	// FPS debug
	this->lastFPSTime = this->lastTime;
}

// in a game loop but not in FPS check loop
void Time::SetTime() {
	this->currentTime = timeGetTime();
	// FPS debug
	// reset frame counter
	if ((this->currentTime - this->lastFPSTime) >= 1000) {
		this->countFPS = (this->frameCounter * 1000) / (this->currentTime - this->lastFPSTime);
		this->lastFPSTime = this->currentTime;
		this->frameCounter = 0;
	}
}


// in FPS check loop
void Time::Update() {
	this->deltaTime = ((float)this->currentTime - (float)this->lastTime) / 1000;
	this->lastTime = this->currentTime;
	// FPS debug
	this->frameCounter ++;
}


bool Time::CheckFPS(int frameRate) {
	if (this->currentTime - this->lastTime >= (unsigned)(1000.0f / (float)frameRate)) {
		return true;
	}
	else {
		return false;
	}
}
