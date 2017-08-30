
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
	std::vector<Int2D> playerPositionData;
	Scene::LoadMapData("map/scene_Scene00-Player.csv", playerPositionData);
	for (unsigned int i = 0; i < playerPositionData.size(); i++) {
		this->playerPosition.push_back(new NoneObject());
		Scene::SetPosition(this->playerPosition.back(), playerPositionData[i].x);
	}

	// Enemy
	std::vector<Int2D> crabData;
	Scene::LoadMapData("map/scene_Scene00-Crab.csv", crabData);
	for (unsigned int i = 0; i < crabData.size(); i++) {
		this->crabs.push_back(new Crab());
		Scene::SetPosition(this->crabs.back(), crabData[i].x);
	}
	std::vector<Int2D> aiData;
	Scene::LoadMapData("map/scene_Scene00-AI.csv", aiData);
	for (unsigned int i = 0; i < aiData.size(); i++) {
		this->ai.push_back(new Ground());
		Scene::SetTile(this->ai.back(), aiData[i].x, aiData[i].y);
		this->ai.back()->collider->tag = "ai";
	}
	std::vector<Int2D> blockData;
	Scene::LoadMapData("map/scene_Scene00-Block.csv", blockData);
	for (unsigned int i = 0; i < blockData.size(); i++) {
		this->blocks.push_back(new Block());
		Scene::SetPosition(this->blocks.back(), blockData[i].x);
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
	for (unsigned int i = 0; i < this->blocks.size(); i++) delete this->blocks[i];
}


/*------------------------------------------------------------------------------
< Start >
------------------------------------------------------------------------------*/
void Scene00::Start() {
	// Set Player position
	this->sceneManager->player->transform->position.x = this->playerPosition[0]->transform->position.x;
	this->sceneManager->player->transform->position.y = this->playerPosition[0]->transform->position.y;

	// Start GameObject && Start Collider (_DEBUG)
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
