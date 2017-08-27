
#include "Engine.h"

/*------------------------------------------------------------------------------
< Constructor >
------------------------------------------------------------------------------*/
Scene02::Scene02() {
	// Load Map Data
	Scene::LoadMapData("map/scene_Scene02-Camera.csv", this->cameraData);
	Scene::LoadMapData("map/scene_Scene02-Ground.csv", this->groundData);
	Scene::LoadMapData("map/scene_Scene02-BackGround.csv", this->backGroundData);
	// Map Data
	this->mapSize = Int2D(100,11);
	this->tilePixel = 16;
	this->tileSize = Int2D(384/16,192/16);

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

	// Get GameObject && Get Collider && reset
	Scene::ResetGameObjectsAndColliders();
}


/*------------------------------------------------------------------------------
< Destructor >
------------------------------------------------------------------------------*/
Scene02::~Scene02() {
	// delete Layer GameObjects
	for (unsigned int i = 0; i < this->grounds.size(); i++) {
		delete this->grounds[i];
	}
	for (unsigned int i = 0; i < this->backGrounds.size(); i++) {
		delete this->backGrounds[i];
	}
}


/*------------------------------------------------------------------------------
< Start >
------------------------------------------------------------------------------*/
void Scene02::Start() {

	for (unsigned int i = 0; i < this->backGrounds.size(); i++) {
		this->backGrounds[i]->sprite->texture = this->sceneManager->texTile;
	}

	// Start GameObject && Start Collider (_DEBUG)
	Scene::Start();
}
