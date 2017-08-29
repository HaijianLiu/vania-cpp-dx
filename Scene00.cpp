
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
	std::vector<int> playerData;
	Scene::LoadMapData("map/scene_Scene00-Player.csv", playerData);
	// push_back to scene map Objects (Order in Layer Order)
	for (unsigned int i = 0; i < playerData.size(); i++) {
		if (playerData[i] != -1) {
			this->player.push_back(new NoneObject());
			Scene::SetTile(this->player.back(), i, playerData[i]);
		}
	}

	// Get GameObject && Get Collider && reset
	Scene::SetScene();
}


/*------------------------------------------------------------------------------
< Destructor >
------------------------------------------------------------------------------*/
Scene00::~Scene00() {
	delete this->player[0];
}


/*------------------------------------------------------------------------------
< Start >
------------------------------------------------------------------------------*/
void Scene00::Start() {
	// Link Texture
	for (unsigned int i = 0; i < this->backGrounds.size(); i++) {
		this->backGrounds[i]->sprite->texture = this->sceneManager->texTile;
	}

	// Set Player position
	this->sceneManager->player->transform->position.x = this->player[0]->transform->position.x;
	this->sceneManager->player->transform->position.y = this->player[0]->transform->position.y;

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
