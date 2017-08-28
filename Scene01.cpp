
#include "Engine.h"

/*------------------------------------------------------------------------------
< Constructor >
------------------------------------------------------------------------------*/
Scene01::Scene01() {
	// Set Map Data Info
	this->mapSize = Int2D(100,11);
	this->tilePixel = 16;
	this->tileSize = Int2D(384/16,192/16);

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
	// Link Texture
	for (unsigned int i = 0; i < this->backGrounds.size(); i++) {
		this->backGrounds[i]->sprite->texture = this->sceneManager->texTile;
	}

	// Start
	Scene::Start();
}


/*------------------------------------------------------------------------------
< Update >
------------------------------------------------------------------------------*/
void Scene01::Update() {
	// Update
	Scene::Update();

	// Check Switch Scene
	if (this->sceneManager->player->transform->position.x > this->range[1]->transform->position.x) {
		this->sceneManager->SetActiveScene(1);
	}
}
