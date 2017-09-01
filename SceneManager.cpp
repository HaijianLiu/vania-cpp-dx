
#include "Engine.h"

/*------------------------------------------------------------------------------
< Constructor >
------------------------------------------------------------------------------*/
SceneManager::SceneManager() {
	// Camera
	this->camera = GetCamera();
	// Resources
	this->resources = GetResources();

	// UIObject
	this->uiEnergy = new UIObject(-200.0f + 6.5f + 49.5f, -120.0f + 19.5f,100.0f,1.0f);
	this->uiEnergyBG = new UIObject(-144.0f,-104.0f,112.0f,32.0f);
	// GameObject
	this->player = new Player();
	this->player->uiEnergy = this->uiEnergy;
	// Scene
	scenes.push_back(new Scene00());
	scenes.push_back(new Scene01());
	scenes.push_back(new Scene02());
	scenes.push_back(new Scene03());
	scenes.push_back(new Scene04());

	// active Scene
	SceneManager::SetActiveScene(0);
}


/*------------------------------------------------------------------------------
< Destructor >
------------------------------------------------------------------------------*/
SceneManager::~SceneManager() {
	// UIObject
	delete this->uiEnergy;
	delete this->uiEnergyBG;
	// Player
	delete this->player;
	// Scene
	for (unsigned int i = 0; i < this->scenes.size(); i++) {
		delete this->scenes[i];
	}
}


/*------------------------------------------------------------------------------
< Start >
------------------------------------------------------------------------------*/
void SceneManager::Start() {
	// set SceneManager in scene
	for (unsigned int i = 0; i < this->scenes.size(); i++) {
		this->scenes[i]->sceneManager = this;
	}
	// Camera target
	this->camera->target = this->player;

	// Resources
	this->uiEnergy->sprite->texture = this->resources->texDefault;
	this->uiEnergyBG->sprite->texture = this->resources->texUIEnergyBG;

	// Scene Start
	// this->resources->audSceneBGM->Play();
	for (unsigned int i = 0; i < this->scenes.size(); i++) {
		this->scenes[i]->Start();
	}
}


/*------------------------------------------------------------------------------
< Update >
------------------------------------------------------------------------------*/
void SceneManager::Update() {
	this->scenes[this->activeScene]->Update();
}


/*------------------------------------------------------------------------------
< Draw >
------------------------------------------------------------------------------*/
void SceneManager::Draw() {
	this->scenes[this->activeScene]->Draw();
}


/*------------------------------------------------------------------------------
< Functions >
------------------------------------------------------------------------------*/
void SceneManager::SetActiveScene(unsigned int i) {
	this->activeScene = i;
	this->camera->activeRange = i;
	this->scenes[this->activeScene]->ReSet();
}
