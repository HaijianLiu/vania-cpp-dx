
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
	this->backGround2Path = "map/scene_Scene06-BackGround2.csv";

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
	// Link Texture
	this->backGround2nd->sprite->texture = this->sceneManager->resources->texBackGround2nd;
	this->backGround4th->sprite->texture = this->sceneManager->resources->texBackGround4th;
	this->bgm = this->sceneManager->resources->audSceneBGMMap;

	// Start GameObject && Start Collider (_DEBUG)
	Scene::Start();
}


/*------------------------------------------------------------------------------
< Update >
------------------------------------------------------------------------------*/
void Scene06::Update() {
	// Check Switch Scene
	if (this->sceneManager->player->transform->position.x > this->range[2]->transform->position.x) {
		this->sceneManager->SetActiveScene(5);
	}
	if (this->sceneManager->player->transform->position.y < this->range[0]->transform->position.y) {
		this->sceneManager->SetActiveScene(7);
	}
	if (this->sceneManager->player->transform->position.x < this->range[1]->transform->position.x) {
		this->sceneManager->SetActiveScene(13);
	}

	// Update
	Scene::Update();
}
