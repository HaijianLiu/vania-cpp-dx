
#include "Engine.h"

#ifdef _DEBUG

Debug::Debug(SceneManager* sceneManager) {
	this->sceneManager = sceneManager;
	this->time = GetTime();
}
Debug::~Debug() {
	if (this->font != NULL) this->font->Release();
}

void Debug::Start() {
	D3DXCreateFont(GetDevice(),
		18,0,0,0,FALSE,
		ANSI_CHARSET,OUT_DEFAULT_PRECIS,DEFAULT_QUALITY,DEFAULT_PITCH,
		_T("Courier New"),
		&this->font);
}

void Debug::Draw() {
	/*------------------------------------------------------------------------------
	< Debug Log >
	------------------------------------------------------------------------------*/
	this->sout
	<< "FPS: " << this->time->countFPS << "\n"
	<< "Delta Time: " << this->time->deltaTime << "\n"
	<< "Camera Position: " << this->sceneManager->camera->position.x << ", " << this->sceneManager->camera->position.y << "\n"
	<< "Player Position: " << this->sceneManager->player->transform->position.x << ", " << this->sceneManager->player->transform->position.y << "\n"
	<< "Player Move: " << this->sceneManager->player->move << "\n"
	<< "Player Air: " << this->sceneManager->player->air << "\n"
	<< "Player Duck: " << this->sceneManager->player->duck << "\n"
	<< "GameObjects: " << this->sceneManager->scene->gameObjects.size() << "\n"
	<< "Colliders: " << this->sceneManager->scene->colliders.size() << "\n";

	// Draw
	this->font->DrawText(NULL,this->sout.str().c_str(),-1,&this->rect,DT_LEFT,D3DCOLOR_RGBA(0xff,0xff,0xff,0xff));
	this->sout.str(std::string());
}

#endif
