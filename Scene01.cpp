
#include "Engine.h"

/*------------------------------------------------------------------------------
< Constructor >
------------------------------------------------------------------------------*/
Scene01::Scene01() {
	// Set Map path
	this->cameraPath = "map/scene_Scene01-Camera.csv";
	this->groundPath = "map/scene_Scene01-Ground.csv";
	this->backGroundPath = "map/scene_Scene01-BackGround.csv";
	this->rangePath = "map/scene_Scene01-Range.csv";

	// Get GameObject && Get Collider && reset
	Scene::SetScene();
}


/*------------------------------------------------------------------------------
< Destructor >
------------------------------------------------------------------------------*/
Scene01::~Scene01() {

}


/*------------------------------------------------------------------------------
< Start >
------------------------------------------------------------------------------*/
void Scene01::Start() {

	// Start GameObject && Start Collider (_DEBUG)
	Scene::Start();
}


/*------------------------------------------------------------------------------
< Update >
------------------------------------------------------------------------------*/
void Scene01::Update() {
	// Update
	Scene::Update();

	// Check Switch Scene
	if (this->sceneManager->player->transform->position.x < this->range[0]->transform->position.x) {
		this->sceneManager->SetActiveScene(0);
	}
}
