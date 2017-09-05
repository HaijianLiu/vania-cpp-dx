
#include "Engine.h"

/*------------------------------------------------------------------------------
< Constructor >
------------------------------------------------------------------------------*/
Scene19::Scene19() {
	// Set Map path
	this->cameraPath = "map/scene_Scene19-Camera.csv";
	this->rangePath = "map/scene_Scene19-Range.csv";
	this->groundPath = "map/scene_Scene19-Ground.csv";
	this->backGroundPath = "map/scene_Scene19-BackGround.csv";

	// Get GameObject && Get Collider && reset
	Scene::SetScene();
}


/*------------------------------------------------------------------------------
< Destructor >
------------------------------------------------------------------------------*/
Scene19::~Scene19() {

}


/*------------------------------------------------------------------------------
< Start >
------------------------------------------------------------------------------*/
void Scene19::Start() {

	// Start GameObject && Start Collider (_DEBUG)
	Scene::Start();
}


/*------------------------------------------------------------------------------
< Update >
------------------------------------------------------------------------------*/
void Scene19::Update() {
	// Check Switch Scene
	if (this->sceneManager->player->transform->position.y > this->range[1]->transform->position.y) {
		this->sceneManager->SetActiveScene(18);
	}

	// Update
	Scene::Update();
}
