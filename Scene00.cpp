
#include "Engine.h"

/*------------------------------------------------------------------------------
< Constructor >
------------------------------------------------------------------------------*/
Scene00::Scene00() {
	// Set Map path
	this->cameraPath = "map/scene_Scene00-Camera.csv";
	this->rangePath = "map/scene_Scene00-Range.csv";
	this->crabPath = "map/scene_Scene00-Crab.csv";
	this->aiPath = "map/scene_Scene00-AI.csv";
	this->orbPath = "map/scene_Scene00-Orb.csv";
	this->blockPath = "map/scene_Scene00-Block.csv";
	this->playerPath = "map/scene_Scene00-Player.csv";
	this->groundPath = "map/scene_Scene00-Ground.csv";
	this->backGroundPath = "map/scene_Scene00-BackGround.csv";
	this->backGround2Path = "map/scene_Scene00-BackGround2.csv";

	// Item test
	// this->itemPath = "map/scene_Scene00-Item.csv";

	// Get GameObject && Get Collider && reset
	Scene::SetScene();
}


/*------------------------------------------------------------------------------
< Destructor >
------------------------------------------------------------------------------*/
Scene00::~Scene00() {

}


/*------------------------------------------------------------------------------
< Start >
------------------------------------------------------------------------------*/
void Scene00::Start() {
	// Link Texture
	this->backGround2nd->sprite->texture = this->sceneManager->resources->texBackGround2nd;
	this->backGround4th->sprite->texture = this->sceneManager->resources->texBackGround4th;
	this->bgm = this->sceneManager->resources->audSceneBGMBasic;

	// this->items[0]->status->tag = "gold";
	// this->items[1]->status->tag = "sliver";
	// this->items[2]->status->tag = "bronze";
	// this->items[3]->status->tag = "dark";

	// Start GameObject && Start Collider (_DEBUG)
	Scene::Start();
}


/*------------------------------------------------------------------------------
< Update >
------------------------------------------------------------------------------*/
void Scene00::Update() {
	// Check Switch Scene
	if (this->sceneManager->player->transform->position.x > this->range[1]->transform->position.x) {
		this->sceneManager->SetActiveScene(1);
	}
	if (this->sceneManager->player->transform->position.x < this->range[0]->transform->position.x) {
		this->sceneManager->SetActiveScene(12);
	}
	// Update
	Scene::Update();
}
