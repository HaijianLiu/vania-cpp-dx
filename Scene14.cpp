
#include "Engine.h"

/*------------------------------------------------------------------------------
< Constructor >
------------------------------------------------------------------------------*/
Scene14::Scene14() {
	// Set Map path
	this->cameraPath = "map/scene_Scene14-Camera.csv";
	this->rangePath = "map/scene_Scene14-Range.csv";
	this->ghostPath = "map/scene_Scene14-Ghost.csv";
	this->playerPath = "map/scene_Scene14-Player.csv";
	this->groundPath = "map/scene_Scene14-Ground.csv";
	this->backGroundPath = "map/scene_Scene14-BackGround.csv";
	this->backGround2Path = "map/scene_Scene14-BackGround2.csv";

	// Get GameObject && Get Collider && reset
	Scene::SetScene();
}


/*------------------------------------------------------------------------------
< Destructor >
------------------------------------------------------------------------------*/
Scene14::~Scene14() {

}


/*------------------------------------------------------------------------------
< Start >
------------------------------------------------------------------------------*/
void Scene14::Start() {
	// Link Texture
	this->backGround2nd->sprite->texture = this->sceneManager->resources->texBackGround2ndTissue;
	this->backGround4th->active = false;
	this->bgm = this->sceneManager->resources->audSceneBGMMars;

	// Start GameObject && Start Collider (_DEBUG)
	Scene::Start();
}


/*------------------------------------------------------------------------------
< Update >
------------------------------------------------------------------------------*/
void Scene14::Update() {
	// Check Switch Scene
	if (this->sceneManager->player->transform->position.x < this->range[2]->transform->position.x) {
		this->sceneManager->SetActiveScene(13);
	}
	if (this->sceneManager->player->transform->position.x > this->range[1]->transform->position.x) {
		this->sceneManager->SetActiveScene(15);
	}

	// Update
	Scene::Update();
}
