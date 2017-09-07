
#include "Engine.h"

/*------------------------------------------------------------------------------
< Constructor >
------------------------------------------------------------------------------*/
Scene07::Scene07() {
	// Set Map path
	this->cameraPath = "map/scene_Scene07-Camera.csv";
	this->rangePath = "map/scene_Scene07-Range.csv";
	this->jumperPath = "map/scene_Scene07-Jumper.csv";
	this->flyerPath = "map/scene_Scene07-Flyer.csv";
	this->orbPath = "map/scene_Scene07-Orb.csv";
	this->blockPath = "map/scene_Scene07-Block.csv";
	this->damageZonePath = "map/scene_Scene07-DamageZone.csv";
	this->groundPath = "map/scene_Scene07-Ground.csv";
	this->backGroundPath = "map/scene_Scene07-BackGround.csv";
	this->backGround2Path = "map/scene_Scene07-BackGround2.csv";

	// Get GameObject && Get Collider && reset
	Scene::SetScene();
}


/*------------------------------------------------------------------------------
< Destructor >
------------------------------------------------------------------------------*/
Scene07::~Scene07() {

}


/*------------------------------------------------------------------------------
< Start >
------------------------------------------------------------------------------*/
void Scene07::Start() {

	// Start GameObject && Start Collider (_DEBUG)
	Scene::Start();
}


/*------------------------------------------------------------------------------
< Update >
------------------------------------------------------------------------------*/
void Scene07::Update() {
	// Check Switch Scene
	if (this->sceneManager->player->transform->position.y > this->range[3]->transform->position.y) {
		this->sceneManager->SetActiveScene(6);
	}
	if (this->sceneManager->player->transform->position.x > this->range[2]->transform->position.x) {
		this->sceneManager->SetActiveScene(8);
	}
	if (this->sceneManager->player->transform->position.y < this->range[0]->transform->position.y) {
		this->sceneManager->SetActiveScene(12);
	}

	// Update
	Scene::Update();
}
