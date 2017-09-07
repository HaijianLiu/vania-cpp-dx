
#include "Engine.h"

/*------------------------------------------------------------------------------
< Constructor >
------------------------------------------------------------------------------*/
Scene12::Scene12() {
	// Set Map path
	this->cameraPath = "map/scene_Scene12-Camera.csv";
	this->rangePath = "map/scene_Scene12-Range.csv";
	this->ballPath = "map/scene_Scene12-Ball.csv";
	this->aiPath = "map/scene_Scene12-AI.csv";
	this->blockPath = "map/scene_Scene12-Block.csv";
	this->orbPath = "map/scene_Scene12-Orb.csv";
	this->itemPath = "map/scene_Scene12-Item.csv";
	this->groundPath = "map/scene_Scene12-Ground.csv";
	this->backGroundPath = "map/scene_Scene12-BackGround.csv";
	this->backGround2Path = "map/scene_Scene12-BackGround2.csv";

	// Get GameObject && Get Collider && reset
	Scene::SetScene();
}


/*------------------------------------------------------------------------------
< Destructor >
------------------------------------------------------------------------------*/
Scene12::~Scene12() {

}


/*------------------------------------------------------------------------------
< Start >
------------------------------------------------------------------------------*/
void Scene12::Start() {
	this->items[0]->status->tag = "bronze";

	// Start GameObject && Start Collider (_DEBUG)
	Scene::Start();
}


/*------------------------------------------------------------------------------
< Update >
------------------------------------------------------------------------------*/
void Scene12::Update() {
	// Check Switch Scene
	if (this->sceneManager->player->transform->position.y > this->range[1]->transform->position.y) {
		this->sceneManager->SetActiveScene(7);
	}
	if (this->sceneManager->player->transform->position.x > this->range[0]->transform->position.x) {
		this->sceneManager->SetActiveScene(0);
	}

	// Update
	Scene::Update();
}
