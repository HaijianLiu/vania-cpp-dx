
#include "Engine.h"

/*------------------------------------------------------------------------------
< Constructor >
------------------------------------------------------------------------------*/
Scene07::Scene07() {
	// Set Map path
	this->cameraPath = "map/scene_Scene07-Camera.csv";
	this->rangePath = "map/scene_Scene07-Range.csv";
	this->jumperPath = "map/scene_Scene07-Jumper.csv";
	this->flyerPath = "map/scene_Scene07-Flyer.csv";
	this->blockPath = "map/scene_Scene07-Block.csv";
	this->groundPath = "map/scene_Scene07-Ground.csv";
	this->backGroundPath = "map/scene_Scene07-BackGround.csv";

	// Get GameObject && Get Collider && reset
	Scene::SetScene();
}


/*------------------------------------------------------------------------------
< Destructor >
------------------------------------------------------------------------------*/
Scene07::~Scene07() {

}


/*------------------------------------------------------------------------------
< Start >
------------------------------------------------------------------------------*/
void Scene07::Start() {

	// Start GameObject && Start Collider (_DEBUG)
	Scene::Start();
}


/*------------------------------------------------------------------------------
< Update >
------------------------------------------------------------------------------*/
void Scene07::Update() {
	// Check Switch Scene
	if (this->sceneManager->player->transform->position.y > this->range[0]->transform->position.y) {
		this->sceneManager->SetActiveScene(6);
	}

	// Update
	Scene::Update();
}
