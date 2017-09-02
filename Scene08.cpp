
#include "Engine.h"

/*------------------------------------------------------------------------------
< Constructor >
------------------------------------------------------------------------------*/
Scene08::Scene08() {
	// Set Map path
	this->cameraPath = "map/scene_Scene08-Camera.csv";
	this->rangePath = "map/scene_Scene08-Range.csv";
	this->damageZonePath = "map/scene_Scene08-DamageZone.csv";
	this->groundPath = "map/scene_Scene08-Ground.csv";
	this->backGroundPath = "map/scene_Scene08-BackGround.csv";

	// Get GameObject && Get Collider && reset
	Scene::SetScene();
}


/*------------------------------------------------------------------------------
< Destructor >
------------------------------------------------------------------------------*/
Scene08::~Scene08() {

}


/*------------------------------------------------------------------------------
< Start >
------------------------------------------------------------------------------*/
void Scene08::Start() {

	// Start GameObject && Start Collider (_DEBUG)
	Scene::Start();
}


/*------------------------------------------------------------------------------
< Update >
------------------------------------------------------------------------------*/
void Scene08::Update() {
	// Check Switch Scene
	if (this->sceneManager->player->transform->position.x < this->range[0]->transform->position.x) {
		this->sceneManager->SetActiveScene(7);
	}
	// if (this->sceneManager->player->transform->position.x > this->range[0]->transform->position.x) {
	// 	this->sceneManager->SetActiveScene(8);
	// }

	// Update
	Scene::Update();
}
