
#include "Engine.h"

/*------------------------------------------------------------------------------
< Constructor >
------------------------------------------------------------------------------*/
Scene06::Scene06() {
	// Set Map path
	this->cameraPath = "map/scene_Scene06-Camera.csv";
	this->rangePath = "map/scene_Scene06-Range.csv";
	this->jumperPath = "map/scene_Scene06-Jumper.csv";
	this->flyerPath = "map/scene_Scene06-Flyer.csv";
	this->crabPath = "map/scene_Scene06-Crab.csv";
	this->blockPath = "map/scene_Scene06-Block.csv";
	this->groundPath = "map/scene_Scene06-Ground.csv";
	this->backGroundPath = "map/scene_Scene06-BackGround.csv";

	// Get GameObject && Get Collider && reset
	Scene::SetScene();
}


/*------------------------------------------------------------------------------
< Destructor >
------------------------------------------------------------------------------*/
Scene06::~Scene06() {

}


/*------------------------------------------------------------------------------
< Start >
------------------------------------------------------------------------------*/
void Scene06::Start() {

	// Start GameObject && Start Collider (_DEBUG)
	Scene::Start();
}


/*------------------------------------------------------------------------------
< Update >
------------------------------------------------------------------------------*/
void Scene06::Update() {
	// Check Switch Scene
	if (this->sceneManager->player->transform->position.x > this->range[1]->transform->position.x) {
		this->sceneManager->SetActiveScene(5);
	}

	// Update
	Scene::Update();
}
