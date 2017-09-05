
#include "Engine.h"

/*------------------------------------------------------------------------------
< Constructor >
------------------------------------------------------------------------------*/
Scene16::Scene16() {
	// Set Map path
	this->cameraPath = "map/scene_Scene16-Camera.csv";
	this->rangePath = "map/scene_Scene16-Range.csv";
	this->groundPath = "map/scene_Scene16-Ground.csv";
	this->backGroundPath = "map/scene_Scene16-BackGround.csv";

	// Get GameObject && Get Collider && reset
	Scene::SetScene();
}


/*------------------------------------------------------------------------------
< Destructor >
------------------------------------------------------------------------------*/
Scene16::~Scene16() {

}


/*------------------------------------------------------------------------------
< Start >
------------------------------------------------------------------------------*/
void Scene16::Start() {

	// Start GameObject && Start Collider (_DEBUG)
	Scene::Start();
}


/*------------------------------------------------------------------------------
< Update >
------------------------------------------------------------------------------*/
void Scene16::Update() {
	// Check Switch Scene
	if (this->sceneManager->player->transform->position.x < this->range[1]->transform->position.x) {
		this->sceneManager->SetActiveScene(15);
	}
	if (this->sceneManager->player->transform->position.x > this->range[0]->transform->position.x) {
		this->sceneManager->SetActiveScene(17);
	}

	// Update
	Scene::Update();
}
