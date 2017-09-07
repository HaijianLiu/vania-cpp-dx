
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

	this->uiTitleStart->sprite->flashTime = this->enterDelay;
	this->uiTitleCredits->sprite->flashTime = this->enterDelay;
	this->uiTitleOption->sprite->flashTime = this->enterDelay;

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

	this->sceneManager->player->uiEnergyBG->active = false;
	this->sceneManager->player->uiEnergy->active = false;
	this->sceneManager->player->score->active = false;

	// Link Texture
	this->backGround2nd->active = false;
	this->backGround4th->active = false;

	// Start GameObject && Start Collider (_DEBUG)
	Scene::Start();
}


/*------------------------------------------------------------------------------
< Update >
------------------------------------------------------------------------------*/
void SceneTitle::Update() {
	if (!this->enter) {
		if (GetKeyboardTrigger(DIK_DOWN)) {
			this->sceneManager->resources->audCurser->Play();
			this->selected ++;
			if (this->selected > 3) {
				this->selected = 3;
			}
		}
		if (GetKeyboardTrigger(DIK_UP)) {
			this->sceneManager->resources->audCurser->Play();
			this->selected --;
			if (this->selected < 0) {
				this->selected = 0;
			}
		}
		if (GetKeyboardTrigger(DIK_RETURN)) {
			this->sceneManager->resources->audStart->Play();
			this->enter = true;
			this->lastEnter = this->time->currentTime;
			switch (this->selected) {
				case 0:
					this->uiTitleStart->sprite->Flash();
					break;
				case 1:
					this->uiTitleCredits->sprite->Flash();
					break;
				case 2:
					this->uiTitleOption->sprite->Flash();
					break;
			}
		}
	}
	else {
		if (this->time->currentTime > this->lastEnter + this->enterDelay * 1000.0f) {
			switch (this->selected) {
				case 0:
					this->sceneManager->SetActiveScene(0);
					break;
				case 1:
					break;
				case 2:
					break;
			}
		}
	}

	// Draw
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

	// Update
	Scene::Update();
}
