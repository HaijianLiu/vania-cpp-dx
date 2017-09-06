
#include "Engine.h"

/*------------------------------------------------------------------------------
< Constructor >
------------------------------------------------------------------------------*/
Scene23::Scene23() {
	// Set Map path
	this->cameraPath = "map/scene_Scene23-Camera.csv";
	this->rangePath = "map/scene_Scene23-Range.csv";
	this->ghostPath = "map/scene_Scene23-Ghost.csv";
	this->orbPath = "map/scene_Scene23-Orb.csv";
	this->groundPath = "map/scene_Scene23-Ground.csv";
	this->backGroundPath = "map/scene_Scene23-BackGround.csv";

	// Get GameObject && Get Collider && reset
	Scene::SetScene();
}


/*------------------------------------------------------------------------------
< Destructor >
------------------------------------------------------------------------------*/
Scene23::~Scene23() {

}


/*------------------------------------------------------------------------------
< Start >
------------------------------------------------------------------------------*/
void Scene23::Start() {

	// Start GameObject && Start Collider (_DEBUG)
	Scene::Start();
}


/*------------------------------------------------------------------------------
< Update >
------------------------------------------------------------------------------*/
void Scene23::Update() {
	// Check Switch Scene
	if (this->sceneManager->player->transform->position.x > this->range[0]->transform->position.x) {
		this->sceneManager->SetActiveScene(22);
	}
	if (this->sceneManager->player->transform->position.y > this->range[1]->transform->position.y) {
		this->sceneManager->SetActiveScene(14);
	}

	// Update
	Scene::Update();
}
