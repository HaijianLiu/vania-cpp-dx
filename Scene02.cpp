
#include "Engine.h"

/*------------------------------------------------------------------------------
< Constructor >
------------------------------------------------------------------------------*/
Scene02::Scene02() {
	// Set Map path
	this->cameraPath = "map/scene_Scene02-Camera.csv";
	this->rangePath = "map/scene_Scene02-Range.csv";
	this->flyerPath = "map/scene_Scene02-Flyer.csv";
	this->groundPath = "map/scene_Scene02-Ground.csv";
	this->backGroundPath = "map/scene_Scene02-BackGround.csv";

	// Get GameObject && Get Collider && reset
	Scene::SetScene();
}


/*------------------------------------------------------------------------------
< Destructor >
------------------------------------------------------------------------------*/
Scene02::~Scene02() {

}


/*------------------------------------------------------------------------------
< Start >
------------------------------------------------------------------------------*/
void Scene02::Start() {

	// Start GameObject && Start Collider (_DEBUG)
	Scene::Start();
}


/*------------------------------------------------------------------------------
< Update >
------------------------------------------------------------------------------*/
void Scene02::Update() {
	// Update
	Scene::Update();

	// Check Switch Scene
	if (this->sceneManager->player->transform->position.x < this->range[0]->transform->position.x) {
		if (DistancePow(this->sceneManager->player->transform->position,this->range[0]->transform->position) < 1.0f ) {
			this->sceneManager->SetActiveScene(1);
		}
		else {
			this->sceneManager->SetActiveScene(3);
		}
	}
}
