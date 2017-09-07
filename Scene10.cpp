
#include "Engine.h"

/*------------------------------------------------------------------------------
< Constructor >
------------------------------------------------------------------------------*/
Scene10::Scene10() {
	// Set Map path
	this->cameraPath = "map/scene_Scene10-Camera.csv";
	this->rangePath = "map/scene_Scene10-Range.csv";
	this->ballPath = "map/scene_Scene10-Ball.csv";
	this->aiPath = "map/scene_Scene10-AI.csv";
	this->groundPath = "map/scene_Scene10-Ground.csv";
	this->backGroundPath = "map/scene_Scene10-BackGround.csv";

	// Get GameObject && Get Collider && reset
	Scene::SetScene();
}


/*------------------------------------------------------------------------------
< Destructor >
------------------------------------------------------------------------------*/
Scene10::~Scene10() {

}


/*------------------------------------------------------------------------------
< Start >
------------------------------------------------------------------------------*/
void Scene10::Start() {
	this->backGround2nd->sprite->texture = this->sceneManager->resources->texBackGround2ndShip;
	this->backGround4th->active = false;

	// Start GameObject && Start Collider (_DEBUG)
	Scene::Start();
}


/*------------------------------------------------------------------------------
< Update >
------------------------------------------------------------------------------*/
void Scene10::Update() {
	// Check Switch Scene
	if (this->sceneManager->player->transform->position.x > this->range[0]->transform->position.x) {
		this->sceneManager->SetActiveScene(11);
	}
	if (this->sceneManager->player->transform->position.x < this->range[1]->transform->position.x) {
		this->sceneManager->SetActiveScene(17);
	}

	// Update
	Scene::Update();
}
