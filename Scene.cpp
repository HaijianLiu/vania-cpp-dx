
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

void Scene::ResetGameObjectsAndColliders() {
	// Get GameObject && Get Collider && reset
	this->gameObjects = CopyGameObjects();
	this->colliders = CopyColliders();

	int size = this->gpGameObjects->size() - this->startGameObjectsSize;
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

}


/*------------------------------------------------------------------------------
< Start >
------------------------------------------------------------------------------*/
void Scene::Start() {
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
	for (unsigned int i = 0; i < this->gameObjects.size(); i++) {
		if (this->gameObjects[i]->active && this->gameObjects[i]->draw) {
			this->gameObjects[i]->Draw();
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
		if (this->colliders[i]->trigger && this->colliders[i]->gameObject->active) {
			for (unsigned int j = 0; j < this->colliders.size(); j++) {
				bool collision = CheckCollision(this->colliders[i],this->colliders[j]);
				if (i != j && collision && this->colliders[j]->trigger == false && this->colliders[j]->gameObject->active) {
					this->colliders[i]->enter = true;
					this->colliders[i]->gameObject->OnTriggerEnter(this->colliders[j]);
					this->colliders[i]->enter = false;
					break;
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
