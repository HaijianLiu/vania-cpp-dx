
#include "Engine.h"

/*------------------------------------------------------------------------------
< Constructor >
------------------------------------------------------------------------------*/
SceneManager::SceneManager() {
	// Camera
	this->camera = GetCamera();
	// Resources
	this->resources = GetResources();

	// GameObject
	this->player = new Player();
	// Scene
	scenes.push_back(new Scene00());
	scenes.push_back(new Scene01());
	scenes.push_back(new Scene02());
	scenes.push_back(new Scene03());
	scenes.push_back(new Scene04());
	scenes.push_back(new Scene05());
	scenes.push_back(new Scene06());
	scenes.push_back(new Scene07());
	scenes.push_back(new Scene08());
	scenes.push_back(new Scene09());
	scenes.push_back(new Scene10());
	scenes.push_back(new Scene11());
	scenes.push_back(new Scene12());
	scenes.push_back(new Scene13());
	scenes.push_back(new Scene14());
	scenes.push_back(new Scene15());
	scenes.push_back(new Scene16());
	scenes.push_back(new Scene17());
	scenes.push_back(new Scene18());
	scenes.push_back(new Scene19());
	scenes.push_back(new Scene20());
	scenes.push_back(new Scene21());
	scenes.push_back(new Scene22());
	scenes.push_back(new Scene23());
	scenes.push_back(new SceneTitle());
	scenes.push_back(new SceneGameOver());

	this->gameOverScene = this->scenes.size() - 1;
	this->titleScene = this->scenes.size() - 2;

	// set SceneManager in scene
	for (unsigned int i = 0; i < this->scenes.size(); i++) {
		this->scenes[i]->sceneManager = this;
		this->scenes[i]->checkPoint->sceneManager = this;
	}
	this->player->sceneManager = this;

	// active Scene
	// SceneManager::SetActiveScene(5);
	// SceneManager::SetActiveScene(14);
}


/*------------------------------------------------------------------------------
< Destructor >
------------------------------------------------------------------------------*/
SceneManager::~SceneManager() {
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
	// Camera target
	this->camera->target = this->player;
	SceneManager::SetActiveScene(this->titleScene);
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
	if (this->scenes[this->activeScene]->frameDelay) {
		this->scenes[this->activeScene]->frameDelay = false;
	}
	else{
		this->scenes[this->activeScene]->Draw();
	}
}


/*------------------------------------------------------------------------------
< Functions >
------------------------------------------------------------------------------*/
void SceneManager::SetActiveScene(unsigned int i) {
	if (this->scenes[this->activeScene]->bgm != nullptr && this->scenes[this->activeScene]->bgm->Playing()) {
		this->scenes[this->activeScene]->bgm->Stop();
	}
	this->activeScene = i;
	this->camera->activeRange = i;
	this->scenes[this->activeScene]->Reset();
	if (this->scenes[this->activeScene]->bgm != nullptr) {
		this->scenes[this->activeScene]->bgm->Play();
	}
}
