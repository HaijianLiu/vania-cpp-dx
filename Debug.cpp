
#include "Engine.h"

#ifdef _DEBUG

Debug::Debug(Scene* scene) {
	this->scene = scene;
	this->time = GetTime();
}
Debug::~Debug() {
	if (this->font != NULL) this->font->Release();
}

void Debug::Start() {
	D3DXCreateFont(GetDevice(),
		18,0,0,0,FALSE,
		SHIFTJIS_CHARSET,OUT_DEFAULT_PRECIS,DEFAULT_QUALITY,DEFAULT_PITCH,
		_T("Terminal"),
		&this->font);
}

void Debug::Draw() {
	RECT rect = {0,0,SCREEN_WIDTH,SCREEN_HEIGHT};
	char str[256];
	sprintf(str,"FPS:%d\nDelta Time:%.3f", this->time->countFPS, this->time->deltaTime);
	this->font->DrawText(NULL,str,-1,&rect,DT_LEFT,D3DCOLOR_ARGB(0xff,0xff,0xff,0xff));
}

#endif
