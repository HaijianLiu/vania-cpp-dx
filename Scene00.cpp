
#include "Engine.h"

/*------------------------------------------------------------------------------
< Constructor >
------------------------------------------------------------------------------*/
Scene00::Scene00() {
	// Set Map path
	this->cameraPath = "map/scene_Scene00-Camera.csv";
	this->groundPath = "map/scene_Scene00-Ground.csv";
	this->backGroundPath = "map/scene_Scene00-BackGround.csv";
	this->rangePath = "map/scene_Scene00-Range.csv";

	// Load Map Data
	std::vector<int> playerPositionData;
	Scene::LoadMapData("map/scene_Scene00-Player.csv", playerPositionData);
	// push_back to scene map Objects (Order in Layer Order)
	for (unsigned int i = 0; i < playerPositionData.size(); i++) {
		if (playerPositionData[i] != -1) {
			this->playerPosition.push_back(new NoneObject());
			Scene::SetTile(this->playerPosition.back(), i, playerPositionData[i]);
		}
	}

	// Enemy
	this->crab = new Crab();

	// Get GameObject && Get Collider && reset
	Scene::SetScene();
}


/*------------------------------------------------------------------------------
< Destructor >
------------------------------------------------------------------------------*/
Scene00::~Scene00() {
	for (unsigned int i = 0; i < this->playerPosition.size(); i++) {
		delete this->playerPosition[i];
	}
	delete this->crab;
}


/*------------------------------------------------------------------------------
< Start >
------------------------------------------------------------------------------*/
void Scene00::Start() {
	// Link Texture
	for (unsigned int i = 0; i < this->backGrounds.size(); i++) {
		this->backGrounds[i]->sprite->texture = this->sceneManager->texTile;
	}
	this->crab->animWalk->sprite->device = this->sceneManager->device;
	this->crab->animWalk->sprite->texture = this->sceneManager->texCrabWalk;

	// Set Player position
	this->sceneManager->player->transform->position.x = this->playerPosition[0]->transform->position.x;
	this->sceneManager->player->transform->position.y = this->playerPosition[0]->transform->position.y;

	// Start
	Scene::Start();
}


/*------------------------------------------------------------------------------
< Update >
------------------------------------------------------------------------------*/
void Scene00::Update() {
	// Update
	Scene::Update();

	// Check Switch Scene
	if (this->sceneManager->player->transform->position.x > this->range[1]->transform->position.x) {
		this->sceneManager->SetActiveScene(1);
	}
}
