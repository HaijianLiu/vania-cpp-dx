
#include "Engine.h"

/*------------------------------------------------------------------------------
< Constructor >
------------------------------------------------------------------------------*/
SceneTitle::SceneTitle() {
	// UIObject

	this->uiTitleStart = new UIObject(0,54,64,8);
	this->uiTitleCredits = new UIObject(0,64,64,8);
	this->uiTitleOption = new UIObject(0,74,64,8);
	this->uiTitleCreditsText = new UIObject(0,0,400,250);
	this->uiTitleCreditsText->draw = false;
	this->uiTitleOptionText = new UIObject(0,0,400,250);
	this->uiTitleOptionText->draw = false;
	this->uiTitlePress = new UIObject(0,88,88,7);
	this->uiTitlePress->draw = false;

	this->uiTitle = new UIObject(0,0,400,250);
	this->uiTitleBG = new UIObject(0,0,400,250);


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
	delete this->uiTitle;
	delete this->uiTitleBG;
	delete this->uiTitleStart;
	delete this->uiTitleCredits;
	delete this->uiTitleOption;
	delete this->uiTitleCreditsText;
	delete this->uiTitleOptionText;
}


/*------------------------------------------------------------------------------
< Start >
------------------------------------------------------------------------------*/
void SceneTitle::Start() {
	this->uiTitle->sprite->texture = this->sceneManager->player->resources->texUITitle;
	this->uiTitleBG->sprite->texture = this->sceneManager->player->resources->texUITitleStar;
	this->uiTitleStart->sprite->texture = this->sceneManager->player->resources->texUITitleText;
	this->uiTitleCredits->sprite->texture = this->sceneManager->player->resources->texUITitleText;
	this->uiTitleOption->sprite->texture = this->sceneManager->player->resources->texUITitleText;
	this->uiTitleCreditsText->sprite->texture = this->sceneManager->player->resources->texUITitleCredits;
	this->uiTitleOptionText->sprite->texture = this->sceneManager->player->resources->texUITitleOption;
	this->uiTitlePress->sprite->texture = this->sceneManager->player->resources->texUITitlePress;


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
	this->uiTitleBG->sprite->SetColor(this->counter/2,this->counter/2,this->counter/2,255);
	if (this->counter < 510) {
		this->counter ++ ;
	}
	this->uiTitleBG->offset.x += 0.05f * sin(this->time->currentTime /2000.0f);
	this->uiTitleBG->offset.y += 0.02f * cos(this->time->currentTime /1000.0f);
	if (!this->enter) {
		if (GetKeyboardTrigger(DIK_DOWN)) {
			this->sceneManager->resources->audCurser->Play();
			this->selected ++;
			if (this->selected > 2) {
				this->selected = 2;
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
			this->enter = true;
			switch (this->selected) {
				case 0:
					this->sceneManager->resources->audStart->Play();
					this->lastEnter = this->time->currentTime;
					this->uiTitleStart->sprite->Flash();
					break;
				case 1:
					this->uiTitleCredits->draw = false;
					this->uiTitleStart->draw = false;
					this->uiTitleOption->draw = false;
					this->uiTitle->draw = false;
					this->uiTitleCreditsText->draw = true;
					this->uiTitlePress->draw = true;
					this->sceneManager->resources->audSelect->Play();
					break;
				case 2:
					this->uiTitleCredits->draw = false;
					this->uiTitleStart->draw = false;
					this->uiTitleOption->draw = false;
					this->uiTitle->draw = false;
					this->uiTitleOptionText->draw = true;
					this->uiTitlePress->draw = true;
					this->sceneManager->resources->audSelect->Play();
					break;
			}
		}
	}
	else {
		this->uiTitlePress->sprite->Flash();
		if (this->selected == 0) {
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
		else {
			if (GetKeyboardTrigger(DIK_RETURN)) {
				this->uiTitleCredits->draw = true;
				this->uiTitleStart->draw = true;
				this->uiTitleOption->draw = true;
				this->uiTitle->draw = true;
				this->uiTitleCreditsText->draw = false;
				this->uiTitleOptionText->draw = false;
				this->uiTitlePress->draw = false;
				this->enter = false;
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
