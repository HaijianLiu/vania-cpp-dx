
#include "Engine.h"

/*------------------------------------------------------------------------------
< Constructor >
------------------------------------------------------------------------------*/
SceneGameOver::SceneGameOver() {
	// Set Map path

	// Get GameObject && Get Collider && reset
	Scene::SetScene();
}


/*------------------------------------------------------------------------------
< Destructor >
------------------------------------------------------------------------------*/
SceneGameOver::~SceneGameOver() {

}


/*------------------------------------------------------------------------------
< Start >
------------------------------------------------------------------------------*/
void SceneGameOver::Start() {

	// Start GameObject && Start Collider (_DEBUG)
	Scene::Start();
}


/*------------------------------------------------------------------------------
< Update >
------------------------------------------------------------------------------*/
void SceneGameOver::Update() {
	// if (this->sceneManager->resources->audSceneBGM->Playing()) {
	// 	this->sceneManager->resources->audSceneBGM->Stop();
	// }
	// Check Switch Scene

	// Update
	Scene::Update();
}
