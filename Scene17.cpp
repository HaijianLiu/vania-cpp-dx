
#include "Engine.h"

/*------------------------------------------------------------------------------
< Constructor >
------------------------------------------------------------------------------*/
Scene17::Scene17() {
	// Set Map path
	this->cameraPath = "map/scene_Scene17-Camera.csv";
	this->rangePath = "map/scene_Scene17-Range.csv";
	this->groundPath = "map/scene_Scene17-Ground.csv";
	this->backGroundPath = "map/scene_Scene17-BackGround.csv";

	// Get GameObject && Get Collider && reset
	Scene::SetScene();
}


/*------------------------------------------------------------------------------
< Destructor >
------------------------------------------------------------------------------*/
Scene17::~Scene17() {

}


/*------------------------------------------------------------------------------
< Start >
------------------------------------------------------------------------------*/
void Scene17::Start() {

	// Start GameObject && Start Collider (_DEBUG)
	Scene::Start();
}


/*------------------------------------------------------------------------------
< Update >
------------------------------------------------------------------------------*/
void Scene17::Update() {
	// Check Switch Scene
	if (this->sceneManager->player->transform->position.x < this->range[2]->transform->position.x) {
		this->sceneManager->SetActiveScene(16);
	}
	if (this->sceneManager->player->transform->position.x > this->range[4]->transform->position.x) {
		this->sceneManager->SetActiveScene(10);
	}

	// Update
	Scene::Update();
}
