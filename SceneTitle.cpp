
#include "Engine.h"

/*------------------------------------------------------------------------------
< Constructor >
------------------------------------------------------------------------------*/
SceneTitle::SceneTitle() {
	// UIObject
	this->uiTitleBG = new UIObject(0,0,400,250);
	this->uiTitleStart = new UIObject(0,54,64,8);
	this->uiTitleCredits = new UIObject(0,64,64,8);
	this->uiTitleOption = new UIObject(0,74,64,8);

	this->uiTitleStart->sprite->slice = Slice(0,0,0,64,8);
	this->uiTitleCredits->sprite->slice = Slice(0,0,8,64,8);
	this->uiTitleCredits->sprite->SetColor(100,100,100,255);
	this->uiTitleOption->sprite->slice = Slice(0,0,16,64,8);
	this->uiTitleOption->sprite->SetColor(100,100,100,255);

	// Get GameObject && Get Collider && reset
	Scene::SetScene();
}


/*------------------------------------------------------------------------------
< Destructor >
------------------------------------------------------------------------------*/
SceneTitle::~SceneTitle() {
	delete this->uiTitleBG;
	delete this->uiTitleStart;
	delete this->uiTitleCredits;
	delete this->uiTitleOption;
}


/*------------------------------------------------------------------------------
< Start >
------------------------------------------------------------------------------*/
void SceneTitle::Start() {
	this->uiTitleBG->sprite->texture = this->sceneManager->player->resources->texUITitle;
	this->uiTitleStart->sprite->texture = this->sceneManager->player->resources->texUITitleText;
	this->uiTitleCredits->sprite->texture = this->sceneManager->player->resources->texUITitleText;
	this->uiTitleOption->sprite->texture = this->sceneManager->player->resources->texUITitleText;

	// Start GameObject && Start Collider (_DEBUG)
	Scene::Start();
}


/*------------------------------------------------------------------------------
< Update >
------------------------------------------------------------------------------*/
void SceneTitle::Update() {
	if (GetKeyboardTrigger(DIK_DOWN)) {
		this->selected ++;
		if (this->selected > 3) {
			this->selected = 3;
		}
	}
	if (GetKeyboardTrigger(DIK_UP)) {
		this->selected --;
		if (this->selected < 0) {
			this->selected = 0;
		}
	}
	switch (this->selected) {
		case 0:
			this->uiTitleStart->sprite->SetColor(255,255,255,255);
			this->uiTitleCredits->sprite->SetColor(100,100,100,255);
			this->uiTitleOption->sprite->SetColor(100,100,100,255);
			break;
		case 1:
			this->uiTitleStart->sprite->SetColor(100,100,100,255);
			this->uiTitleCredits->sprite->SetColor(255,255,255,255);
			this->uiTitleOption->sprite->SetColor(100,100,100,255);
			break;
		case 2:
			this->uiTitleStart->sprite->SetColor(100,100,100,255);
			this->uiTitleCredits->sprite->SetColor(100,100,100,255);
			this->uiTitleOption->sprite->SetColor(255,255,255,255);
			break;
	}

	// this->camera->target = this->sceneManager->player;
	// this->uiGameOverText->sprite->Flash();
	// if (this->sceneManager->player->time->currentTime > this->sceneManager->player->lastGameOver + this->restartDelay * 1000.0f) {
	// 	this->sceneManager->SetActiveScene(this->sceneManager->checkPoint);
	// }
	// if (this->sceneManager->resources->audSceneBGM->Playing()) {
	// 	this->sceneManager->resources->audSceneBGM->Stop();
	// }
	// Check Switch Scene

	// Update
	Scene::Update();
}
