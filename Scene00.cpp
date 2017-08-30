
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
	for (unsigned int i = 0; i < playerPositionData.size(); i++) {
		if (playerPositionData[i] != -1) {
			this->playerPosition.push_back(new NoneObject());
			Scene::SetPosition(this->playerPosition.back(), i);
		}
	}

	// Enemy
	std::vector<int> crabData;
	Scene::LoadMapData("map/scene_Scene00-Crab.csv", crabData);
	for (unsigned int i = 0; i < crabData.size(); i++) {
		if (crabData[i] != -1) {
			this->crabs.push_back(new Crab());
			Scene::SetPosition(this->crabs.back(), i);
		}
	}
	std::vector<int> aiData;
	Scene::LoadMapData("map/scene_Scene00-AI.csv", aiData);
	for (unsigned int i = 0; i < aiData.size(); i++) {
		if (aiData[i] != -1) {
			this->ai.push_back(new Ground());
			Scene::SetTile(this->ai.back(), i, aiData[i]);
			this->ai.back()->collider->tag = "ai";
		}
	}

	// Get GameObject && Get Collider && reset
	Scene::SetScene();
}


/*------------------------------------------------------------------------------
< Destructor >
------------------------------------------------------------------------------*/
Scene00::~Scene00() {
	for (unsigned int i = 0; i < this->playerPosition.size(); i++) delete this->playerPosition[i];
	for (unsigned int i = 0; i < this->crabs.size(); i++) delete this->crabs[i];
	for (unsigned int i = 0; i < this->ai.size(); i++) delete this->ai[i];
}


/*------------------------------------------------------------------------------
< Start >
------------------------------------------------------------------------------*/
void Scene00::Start() {
	// Link Resourse
	for (unsigned int i = 0; i < this->crabs.size(); i++) {
		this->crabs[i]->animWalk->sprite->device = this->sceneManager->device;
		this->crabs[i]->animWalk->sprite->texture = this->sceneManager->texCrabWalk;
		this->crabs[i]->enemyDestroy = this->sceneManager->enemyDestroy;
		this->crabs[i]->audEnemyDamage = this->sceneManager->audEnemyDamage;
	}

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
