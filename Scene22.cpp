
#include "Engine.h"

/*------------------------------------------------------------------------------
< Constructor >
------------------------------------------------------------------------------*/
Scene22::Scene22() {
	// Set Map path
	this->cameraPath = "map/scene_Scene22-Camera.csv";
	this->rangePath = "map/scene_Scene22-Range.csv";
	this->groundPath = "map/scene_Scene22-Ground.csv";
	this->backGroundPath = "map/scene_Scene22-BackGround.csv";

	// Get GameObject && Get Collider && reset
	Scene::SetScene();
}


/*------------------------------------------------------------------------------
< Destructor >
------------------------------------------------------------------------------*/
Scene22::~Scene22() {

}


/*------------------------------------------------------------------------------
< Start >
------------------------------------------------------------------------------*/
void Scene22::Start() {

	// Start GameObject && Start Collider (_DEBUG)
	Scene::Start();
}


/*------------------------------------------------------------------------------
< Update >
------------------------------------------------------------------------------*/
void Scene22::Update() {
	// Check Switch Scene
	if (this->sceneManager->player->transform->position.x > this->range[0]->transform->position.x) {
		this->sceneManager->SetActiveScene(21);
	}
	if (this->sceneManager->player->transform->position.y > this->range[2]->transform->position.y) {
		this->sceneManager->SetActiveScene(15);
	}

	// Update
	Scene::Update();
}
