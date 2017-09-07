
#include "Engine.h"

/*------------------------------------------------------------------------------
< Constructor >
------------------------------------------------------------------------------*/
Scene22::Scene22() {
	// Set Map path
	this->cameraPath = "map/scene_Scene22-Camera.csv";
	this->rangePath = "map/scene_Scene22-Range.csv";
	this->ghostPath = "map/scene_Scene22-Ghost.csv";
	this->flyerPath = "map/scene_Scene22-Flyer.csv";
	this->orbPath = "map/scene_Scene22-Orb.csv";
	this->groundPath = "map/scene_Scene22-Ground.csv";
	this->backGroundPath = "map/scene_Scene22-BackGround.csv";

	// Get GameObject && Get Collider && reset
	Scene::SetScene();
}


/*------------------------------------------------------------------------------
< Destructor >
------------------------------------------------------------------------------*/
Scene22::~Scene22() {

}


/*------------------------------------------------------------------------------
< Start >
------------------------------------------------------------------------------*/
void Scene22::Start() {
	// Link Texture
	this->backGround2nd->sprite->texture = this->sceneManager->resources->texBackGround2ndTissue;
	this->backGround4th->active = false;

	// Start GameObject && Start Collider (_DEBUG)
	Scene::Start();
}


/*------------------------------------------------------------------------------
< Update >
------------------------------------------------------------------------------*/
void Scene22::Update() {
	// Check Switch Scene
	if (this->sceneManager->player->transform->position.x > this->range[0]->transform->position.x) {
		this->sceneManager->SetActiveScene(21);
	}
	if (this->sceneManager->player->transform->position.y > this->range[2]->transform->position.y) {
		this->sceneManager->SetActiveScene(15);
	}
	if (this->sceneManager->player->transform->position.x < this->range[1]->transform->position.x) {
		this->sceneManager->SetActiveScene(23);
	}

	// Update
	Scene::Update();
}
