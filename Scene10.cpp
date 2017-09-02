
#include "Engine.h"

/*------------------------------------------------------------------------------
< Constructor >
------------------------------------------------------------------------------*/
Scene10::Scene10() {
	// Set Map path
	this->cameraPath = "map/scene_Scene10-Camera.csv";
	this->ballPath = "map/scene_Scene10-Ball.csv";
	this->aiPath = "map/scene_Scene10-AI.csv";
	this->groundPath = "map/scene_Scene10-Ground.csv";
	this->backGroundPath = "map/scene_Scene10-BackGround.csv";

	// Get GameObject && Get Collider && reset
	Scene::SetScene();
}


/*------------------------------------------------------------------------------
< Destructor >
------------------------------------------------------------------------------*/
Scene10::~Scene10() {

}


/*------------------------------------------------------------------------------
< Start >
------------------------------------------------------------------------------*/
void Scene10::Start() {

	// Start GameObject && Start Collider (_DEBUG)
	Scene::Start();
}


/*------------------------------------------------------------------------------
< Update >
------------------------------------------------------------------------------*/
void Scene10::Update() {
	// Check Switch Scene
	// if (this->sceneManager->player->transform->position.x < this->range[0]->transform->position.x) {
	// 	this->sceneManager->SetActiveScene(7);
	// }
	// if (this->sceneManager->player->transform->position.x > this->range[0]->transform->position.x) {
	// 	this->sceneManager->SetActiveScene(8);
	// }

	// Update
	Scene::Update();
}
