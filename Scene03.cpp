
#include "Engine.h"

/*------------------------------------------------------------------------------
< Constructor >
------------------------------------------------------------------------------*/
Scene03::Scene03() {
	// Set Map path
	this->cameraPath = "map/scene_Scene03-Camera.csv";
	this->rangePath = "map/scene_Scene03-Range.csv";
	this->flyerPath = "map/scene_Scene03-Flyer.csv";
	this->crabPath = "map/scene_Scene03-Crab.csv";
	this->aiPath = "map/scene_Scene03-AI.csv";
	this->orbPath = "map/scene_Scene03-Orb.csv";
	this->blockPath = "map/scene_Scene03-Block.csv";
	this->groundPath = "map/scene_Scene03-Ground.csv";
	this->backGroundPath = "map/scene_Scene03-BackGround.csv";
	this->backGround2Path = "map/scene_Scene03-BackGround2.csv";

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
	// Link Texture
	this->backGround2nd->sprite->texture = this->sceneManager->resources->texBackGround2nd;
	this->backGround4th->sprite->texture = this->sceneManager->resources->texBackGround4th;

	// Start GameObject && Start Collider (_DEBUG)
	Scene::Start();
}


/*------------------------------------------------------------------------------
< Update >
------------------------------------------------------------------------------*/
void Scene03::Update() {
	// Check Switch Scene
	if (this->sceneManager->player->transform->position.x > this->range[1]->transform->position.x) {
		this->sceneManager->SetActiveScene(2);
	}
	if (this->sceneManager->player->transform->position.x < this->range[0]->transform->position.x) {
		this->sceneManager->SetActiveScene(4);
	}

	// Update
	Scene::Update();
}
