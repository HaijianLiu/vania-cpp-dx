
#include "Engine.h"

/*------------------------------------------------------------------------------
< Constructor >
------------------------------------------------------------------------------*/
Scene01::Scene01() {
	// Set Map Data Info
	this->mapSize = Int2D(100,11);
	this->tilePixel = 16;
	this->tileSize = Int2D(384/16,192/16);

	// Load Map Data
	Scene::LoadMapData("map/scene_Scene01-Camera.csv", this->cameraData);
	Scene::LoadMapData("map/scene_Scene01-Ground.csv", this->groundData);
	Scene::LoadMapData("map/scene_Scene01-BackGround.csv", this->backGroundData);
	Scene::LoadMapData("map/scene_Scene01-Range.csv", this->rangeData);

	// push_back to scene map Objects (Order in Layer Order)
	for (unsigned int i = 0; i < this->cameraData.size(); i++) {
		if (this->cameraData[i] != -1) {
			this->camera->range.push_back(new NoneObject());
			Scene::SetTile(this->camera->range.back(), i, this->cameraData[i]);
		}
	}
	for (unsigned int i = 0; i < this->backGroundData.size(); i++) {
		if (this->backGroundData[i] != -1) {
			this->backGrounds.push_back(new BackGround());
			Scene::SetTile(this->backGrounds.back(), i, this->backGroundData[i]);
		}
	}
	for (unsigned int i = 0; i < this->groundData.size(); i++) {
		if (this->groundData[i] != -1) {
			this->grounds.push_back(new Ground());
			Scene::SetTile(this->grounds.back(), i, this->groundData[i]);
		}
	}
	for (unsigned int i = 0; i < this->rangeData.size(); i++) {
		if (this->rangeData[i] != -1) {
			this->range.push_back(new NoneObject());
			Scene::SetTile(this->range.back(), i, this->rangeData[i]);
		}
	}

	// Get GameObject && Get Collider && reset
	Scene::ResetGameObjectsAndColliders();
}


/*------------------------------------------------------------------------------
< Destructor >
------------------------------------------------------------------------------*/
Scene01::~Scene01() {
	// delete Layer GameObjects
	for (unsigned int i = 0; i < this->grounds.size(); i++) {
		delete this->grounds[i];
	}
	for (unsigned int i = 0; i < this->backGrounds.size(); i++) {
		delete this->backGrounds[i];
	}
	for (unsigned int i = 0; i < this->range.size(); i++) {
		delete this->range[i];
	}
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
