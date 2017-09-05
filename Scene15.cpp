
#include "Engine.h"

/*------------------------------------------------------------------------------
< Constructor >
------------------------------------------------------------------------------*/
Scene15::Scene15() {
	// Set Map path
	this->cameraPath = "map/scene_Scene15-Camera.csv";
	this->rangePath = "map/scene_Scene15-Range.csv";
	this->groundPath = "map/scene_Scene15-Ground.csv";
	this->backGroundPath = "map/scene_Scene15-BackGround.csv";

	// Get GameObject && Get Collider && reset
	Scene::SetScene();
}


/*------------------------------------------------------------------------------
< Destructor >
------------------------------------------------------------------------------*/
Scene15::~Scene15() {

}


/*------------------------------------------------------------------------------
< Start >
------------------------------------------------------------------------------*/
void Scene15::Start() {

	// Start GameObject && Start Collider (_DEBUG)
	Scene::Start();
}


/*------------------------------------------------------------------------------
< Update >
------------------------------------------------------------------------------*/
void Scene15::Update() {
	// Check Switch Scene
	if (this->sceneManager->player->transform->position.x < this->range[1]->transform->position.x) {
		this->sceneManager->SetActiveScene(14);
	}

	// Update
	Scene::Update();
}
