
#include "Engine.h"

/*------------------------------------------------------------------------------
< Constructor >
------------------------------------------------------------------------------*/
Scene13::Scene13() {
	// Set Map path
	this->cameraPath = "map/scene_Scene13-Camera.csv";
	this->rangePath = "map/scene_Scene13-Range.csv";
	this->ghostPath = "map/scene_Scene13-Ghost.csv";
	this->orbPath = "map/scene_Scene13-Orb.csv";
	this->groundPath = "map/scene_Scene13-Ground.csv";
	this->backGroundPath = "map/scene_Scene13-BackGround.csv";
	this->backGround2Path = "map/scene_Scene13-BackGround2.csv";

	// Get GameObject && Get Collider && reset
	Scene::SetScene();
}


/*------------------------------------------------------------------------------
< Destructor >
------------------------------------------------------------------------------*/
Scene13::~Scene13() {

}


/*------------------------------------------------------------------------------
< Start >
------------------------------------------------------------------------------*/
void Scene13::Start() {
	// Link Texture
	this->backGround2nd->sprite->texture = this->sceneManager->resources->texBackGround2nd;
	this->backGround4th->sprite->texture = this->sceneManager->resources->texBackGround4th;

	// Start GameObject && Start Collider (_DEBUG)
	Scene::Start();
}


/*------------------------------------------------------------------------------
< Update >
------------------------------------------------------------------------------*/
void Scene13::Update() {
	// Check Switch Scene
	if (this->sceneManager->player->transform->position.x > this->range[0]->transform->position.x) {
		if (DistancePow(this->sceneManager->player->transform->position,this->range[0]->transform->position) < 1.0f ) {
			this->sceneManager->SetActiveScene(6);
		}
		else {
			this->sceneManager->SetActiveScene(14);
		}
	}

	// Update
	Scene::Update();
}
