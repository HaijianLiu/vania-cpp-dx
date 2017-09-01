
#include "Engine.h"

/*------------------------------------------------------------------------------
< Constructor >
------------------------------------------------------------------------------*/
Scene05::Scene05() {
	// Set Map path
	this->cameraPath = "map/scene_Scene05-Camera.csv";
	this->rangePath = "map/scene_Scene05-Range.csv";
	this->orbPath = "map/scene_Scene05-Orb.csv";
	this->groundPath = "map/scene_Scene05-Ground.csv";
	this->backGroundPath = "map/scene_Scene05-BackGround.csv";

	// Get GameObject && Get Collider && reset
	Scene::SetScene();
}


/*------------------------------------------------------------------------------
< Destructor >
------------------------------------------------------------------------------*/
Scene05::~Scene05() {

}


/*------------------------------------------------------------------------------
< Start >
------------------------------------------------------------------------------*/
void Scene05::Start() {

	// Start GameObject && Start Collider (_DEBUG)
	Scene::Start();
}


/*------------------------------------------------------------------------------
< Update >
------------------------------------------------------------------------------*/
void Scene05::Update() {
	// Check Switch Scene
	if (this->sceneManager->player->transform->position.x > this->range[1]->transform->position.x) {
		this->sceneManager->SetActiveScene(4);
	}

	// Update
	Scene::Update();
}
