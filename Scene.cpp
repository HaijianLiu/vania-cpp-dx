
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
	std::vector<int> cameraData;
	std::vector<int> groundData;
	std::vector<int> backGroundData;
	std::vector<int> rangeData;
	Scene::LoadMapData(this->cameraPath, cameraData);
	Scene::LoadMapData(this->groundPath, groundData);
	Scene::LoadMapData(this->backGroundPath, backGroundData);
	Scene::LoadMapData(this->rangePath, rangeData);

	// push_back to scene map Objects (Order in Layer Order)
	for (unsigned int i = 0; i < cameraData.size(); i++) {
		if (cameraData[i] != -1) {
			this->camera->range.push_back(new NoneObject());
			Scene::SetPosition(this->camera->range.back(), i);
		}
	}
	for (unsigned int i = 0; i < backGroundData.size(); i++) {
		if (backGroundData[i] != -1) {
			this->backGrounds.push_back(new BackGround());
			Scene::SetTile(this->backGrounds.back(), i, backGroundData[i]);
		}
	}
	for (unsigned int i = 0; i < groundData.size(); i++) {
		if (groundData[i] != -1) {
			this->grounds.push_back(new Ground());
			Scene::SetTile(this->grounds.back(), i, groundData[i]);
		}
	}
	for (unsigned int i = 0; i < rangeData.size(); i++) {
		if (rangeData[i] != -1) {
			this->range.push_back(new NoneObject());
			Scene::SetPosition(this->range.back(), i);
		}
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
void Scene::Start() {
	// Link Texture
	for (unsigned int i = 0; i < this->backGrounds.size(); i++) {
		this->backGrounds[i]->sprite->texture = this->sceneManager->texTile;
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
bool Scene::LoadMapData(const char* path, std::vector<int>& data) {
	FILE* file = fopen(path,"rb");
	if (file == NULL) return false;
	int num;

	while (!feof(file)) {
		if(fscanf(file, "%d,", &num) == 1){
			data.push_back(num);
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
