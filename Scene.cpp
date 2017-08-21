
#include "Engine.h"

/*------------------------------------------------------------------------------
< Constructor >
------------------------------------------------------------------------------*/
Scene::Scene() {
	// Camera
	this->camera = GetCamera();

	// GameObject
	this->player = new Player();

	// Load Map Data
	Scene::LoadMapData("assets/10..csv", this->groundData);

	// Layer GameObjects set transform position
	for (unsigned int i = 0; i < this->groundData.size(); i++) {
		if (groundData[i] != 0) {
			this->grounds.push_back(new Ground()); // then set texture  tileID
			this->grounds.back()->transform->position.x = i % mapSize.x * PIXEL_TO_UNIT * tileSize;
			this->grounds.back()->transform->position.y = i / mapSize.x * PIXEL_TO_UNIT * tileSize;
		}
	}
}


/*------------------------------------------------------------------------------
< Destructor >
------------------------------------------------------------------------------*/
Scene::~Scene() {
	// delete GameObject
	delete this->player;

	// delete Layer GameObjects
	for (unsigned int i = 0; i < this->grounds.size(); i++) {
		delete this->grounds[i];
	}

	// delete Texture
	if (this->texTile.texture != NULL) this->texTile.texture->Release();
	if (this->texPlayerIdle.texture != NULL) this->texPlayerIdle.texture->Release();
	if (this->texPlayerRun.texture != NULL) this->texPlayerRun.texture->Release();
	if (this->texPlayerJump.texture != NULL) this->texPlayerJump.texture->Release();

	// Clear Global GameObject and Collider
	// ...

}


/*------------------------------------------------------------------------------
< Start >
------------------------------------------------------------------------------*/
void Scene::Start() {
	// GetDevice
	this->device = GetDevice();
	// Get GameObject && Get Collider
	this->gameObjects = CopyGameObjects();
	this->colliders = CopyColliders();

	// LoadTexture
	LoadTexture(&this->texTile);
	LoadTexture(&this->texPlayerIdle);
	LoadTexture(&this->texPlayerRun);
	LoadTexture(&this->texPlayerJump);

	// Init Layer GameObjects
	this->player->animIdle->sprite->texture = this->texPlayerIdle;
	this->player->animRun->sprite->texture = this->texPlayerRun;
	this->player->animJump->sprite->texture = this->texPlayerJump;
	this->player->sprite->device = this->device;
	this->player->animIdle->sprite->device = this->device;
	this->player->animRun->sprite->device = this->device;
	this->player->animJump->sprite->device = this->device;

	for (unsigned int i = 0; i < this->grounds.size(); i++) {
		this->grounds[i]->sprite->device = this->device;
		this->grounds[i]->sprite->texture = this->texTile;
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
		this->gameObjects[i]->Update();
	}
	CheckCollider();
	for (unsigned int i = 0; i < this->gameObjects.size(); i++) {
		this->gameObjects[i]->UpdateTransform();
	}
	#ifdef _DEBUG
		for (unsigned i = 0; i < this->colliders.size(); i++) {
			this->colliders[i]->Update();
		}
	#endif
}


/*------------------------------------------------------------------------------
< Draw >
------------------------------------------------------------------------------*/
void Scene::Draw() {
	// Draw GameObject && Draw Collider (_DEBUG)
	for (unsigned int i = 0; i < this->gameObjects.size(); i++) {
		this->gameObjects[i]->Draw();
	}
	#ifdef _DEBUG
		for (unsigned i = 0; i < this->colliders.size(); i++) {
			this->colliders[i]->Draw();
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
		if (this->colliders[i]->trigger) {
			for (unsigned int j = 0; j < this->colliders.size(); j++) {
				bool collision = CheckCollision(this->colliders[i],this->colliders[j]);
				if (i != j) {
					if (collision) {
						this->colliders[i]->gameObject->OnTriggerEnter(this->colliders[j]);
					}
				}
			}
		}
	}
}


/*------------------------------------------------------------------------------
< LoadTexture >
------------------------------------------------------------------------------*/
void Scene::LoadTexture(Texture* texture) {
	D3DXCreateTextureFromFileEx(
		this->device, texture->path,
		texture->size.x, texture->size.y,
		1, 0,
		D3DFMT_A8R8G8B8, D3DPOOL_MANAGED, D3DX_FILTER_NONE, D3DX_FILTER_NONE, 0xFF000000, NULL, NULL,
		&texture->texture);
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
