
#include "Engine.h"

/*------------------------------------------------------------------------------
< Constructor >
------------------------------------------------------------------------------*/
Scene11::Scene11() {
	// Set Map path
	this->cameraPath = "map/scene_Scene11-Camera.csv";
	this->rangePath = "map/scene_Scene11-Range.csv";
	this->bossPath = "map/scene_Scene11-Boss.csv";
	this->orbPath = "map/scene_Scene11-Orb.csv";
	this->groundPath = "map/scene_Scene11-Ground.csv";
	this->backGroundPath = "map/scene_Scene11-BackGround.csv";

	// Get GameObject && Get Collider && reset
	Scene::SetScene();
}


/*------------------------------------------------------------------------------
< Destructor >
------------------------------------------------------------------------------*/
Scene11::~Scene11() {

}


/*------------------------------------------------------------------------------
< Start >
------------------------------------------------------------------------------*/
void Scene11::Start() {

	// Start GameObject && Start Collider (_DEBUG)
	Scene::Start();
}


/*------------------------------------------------------------------------------
< Update >
------------------------------------------------------------------------------*/
void Scene11::Update() {
	// Check Switch Scene
	// if (this->sceneManager->player->transform->position.x > this->range[0]->transform->position.x) {
	// 	this->sceneManager->SetActiveScene(11);
	// }
	// if (this->sceneManager->player->transform->position.x > this->range[0]->transform->position.x) {
	// 	this->sceneManager->SetActiveScene(8);
	// }

	// Update
	Scene::Update();
}
