
#include "Engine.h"

/*------------------------------------------------------------------------------
< Constructor >
------------------------------------------------------------------------------*/
SceneGameOver::SceneGameOver() {
	// UIObject
	this->uiGameOverText = new UIObject(0,0,64,16);

	// Get GameObject && Get Collider && reset
	Scene::SetScene();
}


/*------------------------------------------------------------------------------
< Destructor >
------------------------------------------------------------------------------*/
SceneGameOver::~SceneGameOver() {
	delete this->uiGameOverText;
}


/*------------------------------------------------------------------------------
< Start >
------------------------------------------------------------------------------*/
void SceneGameOver::Start() {
	this->uiGameOverText->sprite->texture = this->sceneManager->player->resources->texUIGameOverText;

	// Start GameObject && Start Collider (_DEBUG)
	Scene::Start();
}


/*------------------------------------------------------------------------------
< Update >
------------------------------------------------------------------------------*/
void SceneGameOver::Update() {
	this->uiGameOverText->sprite->Flash();
	if (this->sceneManager->player->time->currentTime > this->sceneManager->player->lastGameOver + this->restartDelay * 1000.0f) {
		this->sceneManager->SetActiveScene(this->sceneManager->checkPoint);
	}
	// if (this->sceneManager->resources->audSceneBGM->Playing()) {
	// 	this->sceneManager->resources->audSceneBGM->Stop();
	// }
	// Check Switch Scene

	// Update
	Scene::Update();
}
