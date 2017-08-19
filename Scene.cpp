
#include "Engine.h"

Scene::Scene() {
	// Camera
	this->camera = GetCamera();

	// GameObject
	this->player = new Player();
	this->ground1 = new Ground();
	this->ground2 = new Ground();
	this->ground3 = new Ground();
	this->ground4 = new Ground();
	this->ground5 = new Ground();
}
Scene::~Scene() {
	// delete GameObject
	delete this->player;
	delete this->ground1;
	delete this->ground2;
	delete this->ground3;
	delete this->ground4;
	delete this->ground5;

	// delete Texture
	if (this->texTile.texture != NULL) this->texTile.texture->Release();
	if (this->texPlayerIdle.texture != NULL) this->texPlayerIdle.texture->Release();
	if (this->texPlayerRun.texture != NULL) this->texPlayerRun.texture->Release();
	if (this->texPlayerJump.texture != NULL) this->texPlayerJump.texture->Release();

	// Clear Global GameObject and Collider
	// ...

}

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

	// Init GameObject
	this->player->animIdle->sprite->texture = this->texPlayerIdle;
	this->player->animRun->sprite->texture = this->texPlayerRun;
	this->player->animJump->sprite->texture = this->texPlayerJump;
	this->ground1->sprite->texture = this->texTile;
	this->ground1->transform->position.y = 0.96f;
	this->ground1->transform->position.x = 0.0f;
	this->ground2->sprite->texture = this->texTile;
	this->ground2->transform->position.y = 0.96f;
	this->ground2->transform->position.x = 0.32f;
	this->ground3->sprite->texture = this->texTile;
	this->ground3->transform->position.y = 0.96f;
	this->ground3->transform->position.x = 0.64f;
	this->ground4->sprite->texture = this->texTile;
	this->ground4->transform->position.y = 0.96f;
	this->ground4->transform->position.x = 0.96f;
	this->ground5->sprite->texture = this->texTile;
	this->ground5->transform->position.y = 0.96f;
	this->ground5->transform->position.x = 1.28f;

	this->player->sprite->device = this->device;
	this->player->animIdle->sprite->device = this->device;
	this->player->animRun->sprite->device = this->device;
	this->player->animJump->sprite->device = this->device;
	this->ground1->sprite->device = this->device;
	this->ground2->sprite->device = this->device;
	this->ground3->sprite->device = this->device;
	this->ground4->sprite->device = this->device;
	this->ground5->sprite->device = this->device;

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

void Scene::LoadTexture(Texture* texture) {
	D3DXCreateTextureFromFileEx(
		this->device, texture->path,
		texture->size.x, texture->size.y,
		1, 0,
		D3DFMT_A8R8G8B8, D3DPOOL_MANAGED, D3DX_FILTER_NONE, D3DX_FILTER_NONE, 0xFF000000, NULL, NULL,
		&texture->texture);
}

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
