
#include "Engine.h"

/*------------------------------------------------------------------------------
< Constructor >
------------------------------------------------------------------------------*/
Scene04::Scene04() {
	// Set Map path
	this->cameraPath = "map/scene_Scene04-Camera.csv";
	this->rangePath = "map/scene_Scene04-Range.csv";
	this->jumperPath = "map/scene_Scene04-Jumper.csv";
	this->flyerPath = "map/scene_Scene04-Flyer.csv";
	this->orbPath = "map/scene_Scene04-Orb.csv";
	this->blockPath = "map/scene_Scene04-Block.csv";
	this->itemPath = "map/scene_Scene04-Item.csv";
	this->groundPath = "map/scene_Scene04-Ground.csv";
	this->backGroundPath = "map/scene_Scene04-BackGround.csv";
	this->backGround2Path = "map/scene_Scene04-BackGround2.csv";

	// Get GameObject && Get Collider && reset
	Scene::SetScene();
}


/*------------------------------------------------------------------------------
< Destructor >
------------------------------------------------------------------------------*/
Scene04::~Scene04() {

}


/*------------------------------------------------------------------------------
< Start >
------------------------------------------------------------------------------*/
void Scene04::Start() {
	this->items[0]->status->tag = "gold";

	// Start GameObject && Start Collider (_DEBUG)
	Scene::Start();
}


/*------------------------------------------------------------------------------
< Update >
------------------------------------------------------------------------------*/
void Scene04::Update() {
	// Check Switch Scene
	if (this->sceneManager->player->transform->position.x > this->range[0]->transform->position.x) {
		this->sceneManager->SetActiveScene(3);
	}
	if (this->sceneManager->player->transform->position.x < this->range[2]->transform->position.x) {
		this->sceneManager->SetActiveScene(5);
	}

	// Update
	Scene::Update();
}
