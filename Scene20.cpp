
#include "Engine.h"

/*------------------------------------------------------------------------------
< Constructor >
------------------------------------------------------------------------------*/
Scene20::Scene20() {
	// Set Map path
	this->cameraPath = "map/scene_Scene20-Camera.csv";
	this->rangePath = "map/scene_Scene20-Range.csv";
	this->blockPath = "map/scene_Scene20-Block.csv";
	this->groundPath = "map/scene_Scene20-Ground.csv";
	this->backGroundPath = "map/scene_Scene20-BackGround.csv";

	// Get GameObject && Get Collider && reset
	Scene::SetScene();
}


/*------------------------------------------------------------------------------
< Destructor >
------------------------------------------------------------------------------*/
Scene20::~Scene20() {

}


/*------------------------------------------------------------------------------
< Start >
------------------------------------------------------------------------------*/
void Scene20::Start() {

	// Start GameObject && Start Collider (_DEBUG)
	Scene::Start();
}


/*------------------------------------------------------------------------------
< Update >
------------------------------------------------------------------------------*/
void Scene20::Update() {
	// Check Switch Scene
	if (this->sceneManager->player->transform->position.x > this->range[1]->transform->position.x) {
		this->sceneManager->SetActiveScene(19);
	}
	// if (this->sceneManager->player->transform->position.y > this->range[1]->transform->position.y) {
	// 	this->sceneManager->SetActiveScene(18);
	// }

	// Update
	Scene::Update();
}
