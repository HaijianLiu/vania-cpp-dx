﻿
#include "Engine.h"

/*------------------------------------------------------------------------------
< Constructor >
------------------------------------------------------------------------------*/
Scene08::Scene08() {
	// Set Map path
	this->cameraPath = "map/scene_Scene08-Camera.csv";
	this->rangePath = "map/scene_Scene08-Range.csv";
	this->flyerPath = "map/scene_Scene08-Flyer.csv";
	this->jumperPath = "map/scene_Scene08-Jumper.csv";
	this->blockPath = "map/scene_Scene08-Block.csv";
	this->damageZonePath = "map/scene_Scene08-DamageZone.csv";
	this->groundPath = "map/scene_Scene08-Ground.csv";
	this->backGroundPath = "map/scene_Scene08-BackGround.csv";
	this->backGround2Path = "map/scene_Scene08-BackGround2.csv";

	// Get GameObject && Get Collider && reset
	Scene::SetScene();
}


/*------------------------------------------------------------------------------
< Destructor >
------------------------------------------------------------------------------*/
Scene08::~Scene08() {

}


/*------------------------------------------------------------------------------
< Start >
------------------------------------------------------------------------------*/
void Scene08::Start() {
	// Link Texture
	this->backGround2nd->sprite->texture = this->sceneManager->resources->texBackGround2ndTissue;
	this->backGround4th->active = false;
	this->bgm = this->sceneManager->resources->audSceneBGMMap;

	// Start GameObject && Start Collider (_DEBUG)
	Scene::Start();
}


/*------------------------------------------------------------------------------
< Update >
------------------------------------------------------------------------------*/
void Scene08::Update() {
	// Check Switch Scene
	if (this->sceneManager->player->transform->position.x < this->range[0]->transform->position.x) {
		this->sceneManager->SetActiveScene(7);
	}
	if (this->sceneManager->player->transform->position.x > this->range[1]->transform->position.x) {
		this->sceneManager->SetActiveScene(9);
	}

	// Update
	Scene::Update();
}
