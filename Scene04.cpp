
#include "Engine.h"

/*------------------------------------------------------------------------------
< Constructor >
------------------------------------------------------------------------------*/
Scene04::Scene04() {
	// Set Map path
	this->cameraPath = "map/scene_Scene04-Camera.csv";
	this->rangePath = "map/scene_Scene04-Range.csv";
	this->flyerPath = "map/scene_Scene04-Flyer.csv";
	this->orbPath = "map/scene_Scene04-Orb.csv";
	this->blockPath = "map/scene_Scene04-Block.csv";
	this->groundPath = "map/scene_Scene04-Ground.csv";
	this->backGroundPath = "map/scene_Scene04-BackGround.csv";

	// Get GameObject && Get Collider && reset
	Scene::SetScene();
}


/*------------------------------------------------------------------------------
< Destructor >
------------------------------------------------------------------------------*/
Scene04::~Scene04() {

}


/*------------------------------------------------------------------------------
< Start >
------------------------------------------------------------------------------*/
void Scene04::Start() {

	// Start GameObject && Start Collider (_DEBUG)
	Scene::Start();
}


/*------------------------------------------------------------------------------
< Update >
------------------------------------------------------------------------------*/
void Scene04::Update() {
	// Check Switch Scene
	if (this->sceneManager->player->transform->position.x > this->range[0]->transform->position.x) {
		this->sceneManager->SetActiveScene(3);
	}

	// Update
	Scene::Update();
}
