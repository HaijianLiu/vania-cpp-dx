
#include "Engine.h"

/*------------------------------------------------------------------------------
< Constructor >
------------------------------------------------------------------------------*/
Scene21::Scene21() {
	// Set Map path
	this->cameraPath = "map/scene_Scene21-Camera.csv";
	this->rangePath = "map/scene_Scene21-Range.csv";
	this->groundPath = "map/scene_Scene21-Ground.csv";
	this->backGroundPath = "map/scene_Scene21-BackGround.csv";

	// Get GameObject && Get Collider && reset
	Scene::SetScene();
}


/*------------------------------------------------------------------------------
< Destructor >
------------------------------------------------------------------------------*/
Scene21::~Scene21() {

}


/*------------------------------------------------------------------------------
< Start >
------------------------------------------------------------------------------*/
void Scene21::Start() {
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
void Scene21::Update() {
	// Check Switch Scene
	if (this->sceneManager->player->transform->position.y > this->range[1]->transform->position.y) {
		this->sceneManager->SetActiveScene(16);
	}
	if (this->sceneManager->player->transform->position.x < this->range[0]->transform->position.x) {
		this->sceneManager->SetActiveScene(22);
	}

	// Update
	Scene::Update();
}
