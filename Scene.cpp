﻿
#include "Engine.h"

/*------------------------------------------------------------------------------
< Constructor >
------------------------------------------------------------------------------*/
Scene::Scene() {
	// Camera
	this->camera = GetCamera();

	// get start size
	this->gpGameObjects = GetGameObjects();
	this->gpColliders = GetColliders();
	this->startGameObjectsSize = GetGameObjectsSize();
	this->startCollidersSize = GetCollidersSize();
}

void Scene::SetScene() {
	// Load Map Data

	// push_back to scene map Objects (Order in Layer Order)
	// range
	std::vector<Int2D> cameraData;
	Scene::LoadMapData(this->cameraPath, cameraData);
	for (unsigned int i = 0; i < cameraData.size(); i++) {
		this->camera->range.push_back(new NoneObject());
		Scene::SetPosition(this->camera->range.back(), cameraData[i].x);
	}
	std::vector<Int2D> rangeData;
	Scene::LoadMapData(this->rangePath, rangeData);
	for (unsigned int i = 0; i < rangeData.size(); i++) {
		this->range.push_back(new NoneObject());
		Scene::SetPosition(this->range.back(), rangeData[i].x);
	}
	// Enemy
	std::vector<Int2D> crabData;
	Scene::LoadMapData(this->crabPath, crabData);
	for (unsigned int i = 0; i < crabData.size(); i++) {
		this->crabs.push_back(new Crab());
		Scene::SetPosition(this->crabs.back(), crabData[i].x);
	}
	std::vector<Int2D> aiData;
	Scene::LoadMapData(this->aiPath, aiData);
	for (unsigned int i = 0; i < aiData.size(); i++) {
		this->ai.push_back(new Ground());
		Scene::SetTile(this->ai.back(), aiData[i].x, aiData[i].y);
		this->ai.back()->collider->tag = "ai";
	}
	// Block
	std::vector<Int2D> blockData;
	Scene::LoadMapData(this->blockPath, blockData);
	for (unsigned int i = 0; i < blockData.size(); i++) {
		this->blocks.push_back(new Block());
		Scene::SetPosition(this->blocks.back(), blockData[i].x);
	}
	// Map
	std::vector<Int2D> backGroundData;
	Scene::LoadMapData(this->backGroundPath, backGroundData);
	for (unsigned int i = 0; i < backGroundData.size(); i++) {
		this->backGrounds.push_back(new BackGround());
		Scene::SetTile(this->backGrounds.back(), backGroundData[i].x, backGroundData[i].y);
	}
	std::vector<Int2D> groundData;
	Scene::LoadMapData(this->groundPath, groundData);
	for (unsigned int i = 0; i < groundData.size(); i++) {
		this->grounds.push_back(new Ground());
		Scene::SetTile(this->grounds.back(), groundData[i].x, groundData[i].y);
	}

	// Get GameObject && Get Collider
	this->gameObjects = CopyGameObjects();
	this->colliders = CopyColliders();
	// reset global gameObjects
	int size;
	size = this->gpGameObjects->size() - this->startGameObjectsSize;
	for (int i = 0; i < size; i++) {
		this->gpGameObjects->pop_back();
	}
	size = this->gpColliders->size() - this->startCollidersSize;
	for (int i = 0; i < size; i++) {
		this->gpColliders->pop_back();
	}
}


/*------------------------------------------------------------------------------
< Destructor >
------------------------------------------------------------------------------*/
Scene::~Scene() {
	// delete Map GameObjects
	for (unsigned int i = 0; i < this->range.size(); i++) delete this->range[i];
	for (unsigned int i = 0; i < this->ai.size(); i++) delete this->ai[i];
	for (unsigned int i = 0; i < this->crabs.size(); i++) delete this->crabs[i];
	for (unsigned int i = 0; i < this->blocks.size(); i++) delete this->blocks[i];
	for (unsigned int i = 0; i < this->grounds.size(); i++) delete this->grounds[i];
	for (unsigned int i = 0; i < this->backGrounds.size(); i++) delete this->backGrounds[i];
}


/*------------------------------------------------------------------------------
< Start >
------------------------------------------------------------------------------*/
void Scene::Start() {
	// Link Texture
	for (unsigned int i = 0; i < this->backGrounds.size(); i++) {
		this->backGrounds[i]->sprite->texture = this->sceneManager->resources->texTile;
	}

	// Start GameObject && Start Collider (_DEBUG)
	for (unsigned int i = 0; i < this->gameObjects.size(); i++) {
		this->gameObjects[i]->PreStart();
		this->gameObjects[i]->Start();
	}
	#ifdef _DEBUG
		for (unsigned i = 0; i < this->colliders.size(); i++) {
			this->colliders[i]->Start();
		}
	#endif
}


/*------------------------------------------------------------------------------
< Update >
------------------------------------------------------------------------------*/
void Scene::Update() {
	// Update GameObject && CheckCollider && Update Collider (_DEBUG)
	for (unsigned int i = 0; i < this->gameObjects.size(); i++) {
		if (this->gameObjects[i]->active) {
			this->gameObjects[i]->Update();
		}
	}
	CheckCollider();
	this->camera->Update();
	for (unsigned int i = 0; i < this->gameObjects.size(); i++) {
		if (this->gameObjects[i]->active) {
			this->gameObjects[i]->FixedUpdate();
			this->gameObjects[i]->UpdateTransform();
		}
	}
	#ifdef _DEBUG
		for (unsigned i = 0; i < this->colliders.size(); i++) {
			if (this->colliders[i]->gameObject->active) {
				this->colliders[i]->Update();
			}
		}
	#endif
}


/*------------------------------------------------------------------------------
< Draw >
------------------------------------------------------------------------------*/
void Scene::Draw() {
	// Draw GameObject && Draw Collider (_DEBUG)
	for (unsigned int i = this->gameObjects.size(); i > 0; i--) {
		if (this->gameObjects[i-1]->active && this->gameObjects[i-1]->draw) {
			this->gameObjects[i-1]->Draw();
		}
	}
	#ifdef _DEBUG
		for (unsigned i = 0; i < this->colliders.size(); i++) {
			if (this->colliders[i]->gameObject->active) {
				this->colliders[i]->Draw();
			}
		}
	#endif
}


/*------------------------------------------------------------------------------
< CheckCollision >
------------------------------------------------------------------------------*/
bool Scene::CheckCollision(BoxCollider* a, BoxCollider* b) {
	// Collision x-axis?
	bool collisionX =
		a->gameObject->transform->position.x + a->offset.x + a->halfSize.x * PIXEL_TO_UNIT >
		b->gameObject->transform->position.x + b->offset.x - b->halfSize.x * PIXEL_TO_UNIT
		&&
		a->gameObject->transform->position.x + a->offset.x - a->halfSize.x * PIXEL_TO_UNIT <
		b->gameObject->transform->position.x + b->offset.x + b->halfSize.x * PIXEL_TO_UNIT;
	// Collision y-axis?
	bool collisionY =
		a->gameObject->transform->position.y + a->offset.y + a->halfSize.y * PIXEL_TO_UNIT >
		b->gameObject->transform->position.y + b->offset.y - b->halfSize.y * PIXEL_TO_UNIT
		&&
		a->gameObject->transform->position.y + a->offset.y - a->halfSize.y * PIXEL_TO_UNIT <
		b->gameObject->transform->position.y + b->offset.y + b->halfSize.y * PIXEL_TO_UNIT;
	// Collision only if on both axes
	return collisionX && collisionY;
}
void Scene::CheckCollider() {
	for (unsigned int i = 0; i < this->colliders.size(); i++) {
		if (this->colliders[i]->trigger && this->colliders[i]->gameObject->active && this->colliders[i]->active) {
			for (unsigned int j = 0; j < this->colliders.size(); j++) {
				bool collision = CheckCollision(this->colliders[i],this->colliders[j]);
				if (i != j && collision && this->colliders[j]->gameObject->active && this->colliders[j]->active) {
					this->colliders[i]->enter = true;
					this->colliders[i]->gameObject->OnTriggerEnter(this->colliders[j]);
					this->colliders[i]->enter = false;
					this->colliders[j]->enter = true;
					this->colliders[j]->gameObject->OnTriggerEnter(this->colliders[i]);
					this->colliders[j]->enter = false;
				}
			}
		}
	}
}


/*------------------------------------------------------------------------------
< LoadMapData >
------------------------------------------------------------------------------*/
bool Scene::LoadMapData(const char* path, std::vector<Int2D>& data) {
	FILE* file = fopen(path,"rb");
	if (file == NULL) return false;
	unsigned int counter = 0;
	int num;

	while (!feof(file)) {
		if(fscanf(file, "%d,", &num) == 1){
			if (num != -1) {
				data.push_back(Int2D(counter,num));
			}
			counter++;
		}
	}

	fclose(file);
	return true;
}

void Scene::SetTile(GameObject* gameObject, int mapID, int tileID) {
	gameObject->transform->position.x = mapID % this->mapSize.x * PIXEL_TO_UNIT * this->tilePixel;
	gameObject->transform->position.y = mapID / this->mapSize.x * PIXEL_TO_UNIT * this->tilePixel;
	gameObject->transform->scale = Float2D((float)this->tilePixel, (float)this->tilePixel);
	gameObject->sprite->slice = Slice(tileID, tileID % this->tileSize.x * this->tilePixel , tileID / this->tileSize.x * this->tilePixel, this->tilePixel, this->tilePixel);
}

void Scene::SetPosition(GameObject* gameObject, int mapID) {
	gameObject->transform->position.x = mapID % this->mapSize.x * PIXEL_TO_UNIT * this->tilePixel;
	gameObject->transform->position.y = mapID / this->mapSize.x * PIXEL_TO_UNIT * this->tilePixel;
}
