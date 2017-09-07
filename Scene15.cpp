
#include "Engine.h"

/*------------------------------------------------------------------------------
< Constructor >
------------------------------------------------------------------------------*/
Scene15::Scene15() {
	// Set Map path
	this->cameraPath = "map/scene_Scene15-Camera.csv";
	this->rangePath = "map/scene_Scene15-Range.csv";
	this->aiPath = "map/scene_Scene15-AI.csv";
	this->jumperPath = "map/scene_Scene15-Jumper.csv";
	this->crabPath = "map/scene_Scene15-Crab.csv";
	this->blockPath = "map/scene_Scene15-Block.csv";
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
	// Link Texture
	this->backGround2nd->sprite->texture = this->sceneManager->resources->texBackGround2ndTissue;
	this->backGround4th->active = false;

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
	if (this->sceneManager->player->transform->position.x > this->range[2]->transform->position.x) {
		this->sceneManager->SetActiveScene(16);
	}
	if (this->sceneManager->player->transform->position.y < this->range[0]->transform->position.y) {
		this->sceneManager->SetActiveScene(22);
	}


	// Update
	Scene::Update();
}
