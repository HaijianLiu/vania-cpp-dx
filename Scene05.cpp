
#include "Engine.h"

/*------------------------------------------------------------------------------
< Constructor >
------------------------------------------------------------------------------*/
Scene05::Scene05() {
	// Set Map path
	this->cameraPath = "map/scene_Scene05-Camera.csv";
	this->rangePath = "map/scene_Scene05-Range.csv";
	this->orbPath = "map/scene_Scene05-Orb.csv";
	this->playerPath = "map/scene_Scene05-Player.csv";
	this->groundPath = "map/scene_Scene05-Ground.csv";
	this->backGroundPath = "map/scene_Scene05-BackGround.csv";
	this->backGround2Path = "map/scene_Scene05-BackGround2.csv";

	// Get GameObject && Get Collider && reset
	Scene::SetScene();
}


/*------------------------------------------------------------------------------
< Destructor >
------------------------------------------------------------------------------*/
Scene05::~Scene05() {

}


/*------------------------------------------------------------------------------
< Start >
------------------------------------------------------------------------------*/
void Scene05::Start() {
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
void Scene05::Update() {
	// Check Switch Scene
	if (this->sceneManager->player->transform->position.x > this->range[1]->transform->position.x) {
		this->sceneManager->SetActiveScene(4);
	}
	if (this->sceneManager->player->transform->position.x < this->range[0]->transform->position.x) {
		this->sceneManager->SetActiveScene(6);
	}
	if (this->sceneManager->player->transform->position.y > this->range[2]->transform->position.y) {
		this->sceneManager->SetActiveScene(10);
	}

	// Update
	Scene::Update();
}
