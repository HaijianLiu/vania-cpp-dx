
#include "Engine.h"

/*------------------------------------------------------------------------------
< Constructor >
------------------------------------------------------------------------------*/
Scene09::Scene09() {
	// Set Map path
	this->cameraPath = "map/scene_Scene09-Camera.csv";
	this->rangePath = "map/scene_Scene09-Range.csv";
	this->itemPath = "map/scene_Scene09-Item.csv";
	this->groundPath = "map/scene_Scene09-Ground.csv";
	this->backGroundPath = "map/scene_Scene09-BackGround.csv";

	// Get GameObject && Get Collider && reset
	Scene::SetScene();
}


/*------------------------------------------------------------------------------
< Destructor >
------------------------------------------------------------------------------*/
Scene09::~Scene09() {

}


/*------------------------------------------------------------------------------
< Start >
------------------------------------------------------------------------------*/
void Scene09::Start() {
	this->items[0]->status->tag = "sliver";
	// Link Texture
	this->backGround2nd->sprite->texture = this->sceneManager->resources->texBackGround2ndShip;
	this->backGround4th->active = false;

	// Start GameObject && Start Collider (_DEBUG)
	Scene::Start();
}


/*------------------------------------------------------------------------------
< Update >
------------------------------------------------------------------------------*/
void Scene09::Update() {
	// Check Switch Scene
	if (this->sceneManager->player->transform->position.x < this->range[0]->transform->position.x) {
		this->sceneManager->SetActiveScene(8);
	}
	if (this->sceneManager->player->transform->position.y > this->range[1]->transform->position.y) {
		this->sceneManager->SetActiveScene(5);
	}

	// Update
	Scene::Update();
}
