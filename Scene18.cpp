
#include "Engine.h"

/*------------------------------------------------------------------------------
< Constructor >
------------------------------------------------------------------------------*/
Scene18::Scene18() {
	// Set Map path
	this->cameraPath = "map/scene_Scene18-Camera.csv";
	this->rangePath = "map/scene_Scene18-Range.csv";
	this->blockPath = "map/scene_Scene18-Block.csv";
	this->groundPath = "map/scene_Scene18-Ground.csv";
	this->backGroundPath = "map/scene_Scene18-BackGround.csv";

	// Get GameObject && Get Collider && reset
	Scene::SetScene();
}


/*------------------------------------------------------------------------------
< Destructor >
------------------------------------------------------------------------------*/
Scene18::~Scene18() {

}


/*------------------------------------------------------------------------------
< Start >
------------------------------------------------------------------------------*/
void Scene18::Start() {

	// Start GameObject && Start Collider (_DEBUG)
	Scene::Start();
}


/*------------------------------------------------------------------------------
< Update >
------------------------------------------------------------------------------*/
void Scene18::Update() {
	// Check Switch Scene
	if (this->sceneManager->player->transform->position.y > this->range[2]->transform->position.y) {
		this->sceneManager->SetActiveScene(17);
	}

	// Update
	Scene::Update();
}
