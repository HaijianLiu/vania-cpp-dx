
#include "Engine.h"

/*------------------------------------------------------------------------------
< Constructor >
------------------------------------------------------------------------------*/
Scene03::Scene03() {
	// Set Map path
	this->cameraPath = "map/scene_Scene03-Camera.csv";
	this->rangePath = "map/scene_Scene03-Range.csv";
	this->crabPath = "map/scene_Scene03-Crab.csv";
	this->aiPath = "map/scene_Scene03-AI.csv";
	this->orbPath = "map/scene_Scene03-Orb.csv";
	this->blockPath = "map/scene_Scene03-Block.csv";
	this->groundPath = "map/scene_Scene03-Ground.csv";
	this->backGroundPath = "map/scene_Scene03-BackGround.csv";

	// Get GameObject && Get Collider && reset
	Scene::SetScene();
}


/*------------------------------------------------------------------------------
< Destructor >
------------------------------------------------------------------------------*/
Scene03::~Scene03() {

}


/*------------------------------------------------------------------------------
< Start >
------------------------------------------------------------------------------*/
void Scene03::Start() {

	// Start GameObject && Start Collider (_DEBUG)
	Scene::Start();
}


/*------------------------------------------------------------------------------
< Update >
------------------------------------------------------------------------------*/
void Scene03::Update() {
	// Update
	Scene::Update();

	// Check Switch Scene
	if (this->sceneManager->player->transform->position.x > this->range[1]->transform->position.x) {
		this->sceneManager->SetActiveScene(2);
	}
}
