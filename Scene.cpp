
#include "Engine.h"

/*------------------------------------------------------------------------------
< Constructor >
------------------------------------------------------------------------------*/
Scene::Scene() {
	// Camera
	this->camera = GetCamera();

	// Load Map Data
	Scene::LoadMapData("map/scene_Ground.csv", this->groundData);

	// GameObject Order in Layers
	for (unsigned int i = 0; i < this->groundData.size(); i++) {
		if (groundData[i] != -1) {
			this->grounds.push_back(new Ground());
			Scene::SetTile(this->grounds.back(), i, groundData[i]);
		}
	}
	this->player = new Player();
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
	if (this->texDefault.texture != NULL) this->texDefault.texture->Release();
	if (this->texTile.texture != NULL) this->texTile.texture->Release();
	if (this->texPlayerIdle.texture != NULL) this->texPlayerIdle.texture->Release();
	if (this->texPlayerRun.texture != NULL) this->texPlayerRun.texture->Release();
	if (this->texPlayerJump.texture != NULL) this->texPlayerJump.texture->Release();
	if (this->texBullet.texture != NULL) this->texBullet.texture->Release();

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
	LoadTexture(&this->texDefault);
	LoadTexture(&this->texTile);
	LoadTexture(&this->texPlayerIdle);
	LoadTexture(&this->texPlayerRun);
	LoadTexture(&this->texPlayerJump);
	LoadTexture(&this->texBullet);

	// Link GameObjects device && texture
	this->player->animIdle->sprite->device = this->device;
	this->player->animIdle->sprite->texture = this->texPlayerIdle;
	this->player->animRun->sprite->device = this->device;
	this->player->animRun->sprite->texture = this->texPlayerRun;
	this->player->animJump->sprite->device = this->device;
	this->player->animJump->sprite->texture = this->texPlayerJump;
	for (unsigned int i = 0; i < this->player->bullets.size(); i++) {
		this->player->bullets[i]->sprite->texture = this->texBullet;
		this->player->bullets[i]->fxDestroy->LinkTexture(this->texDefault);
	}

	for (unsigned int i = 0; i < this->grounds.size(); i++) {
		this->grounds[i]->sprite->texture = this->texTile;
	}



	/*------------------------------------------------------------------------------
	< ............................................................................ >
	------------------------------------------------------------------------------*/
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
		if (this->gameObjects[i]->active) {
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

void Scene::SetTile(GameObject* gameObject, int mapID, int tileID) {
	gameObject->transform->position.x = mapID % this->mapSize.x * PIXEL_TO_UNIT * this->tilePixel;
	gameObject->transform->position.y = mapID / this->mapSize.x * PIXEL_TO_UNIT * this->tilePixel;
	gameObject->transform->scale = Float2D((float)this->tilePixel, (float)this->tilePixel);
	gameObject->sprite->slice = Slice(tileID, tileID % this->tileSize.x * this->tilePixel , tileID / this->tileSize.x * this->tilePixel, this->tilePixel, this->tilePixel);
}
