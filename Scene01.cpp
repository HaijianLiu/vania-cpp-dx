﻿
#include "Engine.h"

/*------------------------------------------------------------------------------
< Constructor >
------------------------------------------------------------------------------*/
Scene01::Scene01() {
	// Set Map path
	this->cameraPath = "map/scene_Scene01-Camera.csv";
	this->rangePath = "map/scene_Scene01-Range.csv";
	this->crabPath = "map/scene_Scene01-Crab.csv";
	this->aiPath = "map/scene_Scene01-AI.csv";
	this->orbPath = "map/scene_Scene01-Orb.csv";
	this->blockPath = "map/scene_Scene01-Block.csv";
	this->groundPath = "map/scene_Scene01-Ground.csv";
	this->backGroundPath = "map/scene_Scene01-BackGround.csv";
	this->backGround2Path = "map/scene_Scene01-BackGround2.csv";

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
	this->backGround2nd->sprite->texture = this->sceneManager->resources->texBackGround2nd;
	this->backGround4th->sprite->texture = this->sceneManager->resources->texBackGround4th;
	this->bgm = this->sceneManager->resources->audSceneBGMBasic;

	// Start GameObject && Start Collider (_DEBUG)
	Scene::Start();
}


/*------------------------------------------------------------------------------
< Update >
------------------------------------------------------------------------------*/
void Scene01::Update() {
	// Check Switch Scene
	if (this->sceneManager->player->transform->position.x < this->range[0]->transform->position.x) {
		this->sceneManager->SetActiveScene(0);
	}
	if (this->sceneManager->player->transform->position.x > this->range[1]->transform->position.x) {
		this->sceneManager->SetActiveScene(2);
	}

	// Update
	Scene::Update();
}
