
#include "Engine.h"

/*------------------------------------------------------------------------------
< Constructor >
------------------------------------------------------------------------------*/
Scene02::Scene02() {
	// Set Map Data Info
	this->mapSize = Int2D(100,11);
	this->tilePixel = 16;
	this->tileSize = Int2D(384/16,192/16);

	// Set Map path
	this->cameraPath = "map/scene_Scene02-Camera.csv";
	this->groundPath = "map/scene_Scene02-Ground.csv";
	this->backGroundPath = "map/scene_Scene02-BackGround.csv";
	this->rangePath = "map/scene_Scene02-Range.csv";

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
	// Link Texture
	for (unsigned int i = 0; i < this->backGrounds.size(); i++) {
		this->backGrounds[i]->sprite->texture = this->sceneManager->texTile;
	}

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
		this->sceneManager->SetActiveScene(0);
	}
}
