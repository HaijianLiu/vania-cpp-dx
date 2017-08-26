
#include "Engine.h"

/*------------------------------------------------------------------------------
< Constructor >
------------------------------------------------------------------------------*/
SceneManager::SceneManager() {
	// Camera
	this->camera = GetCamera();

	// Player
	this->player = new Player();
	// Particle
	this->fxDestroy = new ParticleSystem(40);
	this->fxTail = new ParticleSystem(100);
	// Enemy
	this->crab = new Crab();
	// Scene
	this->scene = new Scene();
}


/*------------------------------------------------------------------------------
< Destructor >
------------------------------------------------------------------------------*/
SceneManager::~SceneManager() {
	delete this->player;
	delete this->fxDestroy;
	delete this->fxTail;
	delete this->crab;
	delete this->scene;
	// delete Texture
	if (this->texDefault.texture != NULL) this->texDefault.texture->Release();
	if (this->texTile.texture != NULL) this->texTile.texture->Release();
	if (this->texPlayerIdle.texture != NULL) this->texPlayerIdle.texture->Release();
	if (this->texPlayerShoot.texture != NULL) this->texPlayerShoot.texture->Release();
	if (this->texPlayerRun.texture != NULL) this->texPlayerRun.texture->Release();
	if (this->texPlayerJump.texture != NULL) this->texPlayerJump.texture->Release();
	if (this->texPlayerDuck.texture != NULL) this->texPlayerDuck.texture->Release();
	if (this->texPlayerDuckFire.texture != NULL) this->texPlayerDuckFire.texture->Release();
	if (this->texBullet.texture != NULL) this->texBullet.texture->Release();
	if (this->texFxDestroy.texture != NULL) this->texFxDestroy.texture->Release();
	if (this->texCrabWalk.texture != NULL) this->texCrabWalk.texture->Release();
}


/*------------------------------------------------------------------------------
< Start >
------------------------------------------------------------------------------*/
void SceneManager::Start() {
	// GetDevice
	this->device = GetDevice();
	// set SceneManager in scene
	this->scene->sceneManager = this;
	// LoadTexture
	LoadTexture(&this->texDefault);
	LoadTexture(&this->texTile);
	LoadTexture(&this->texPlayerIdle);
	LoadTexture(&this->texPlayerShoot);
	LoadTexture(&this->texPlayerRun);
	LoadTexture(&this->texPlayerJump);
	LoadTexture(&this->texPlayerDuck);
	LoadTexture(&this->texPlayerDuckFire);
	LoadTexture(&this->texBullet);
	LoadTexture(&this->texFxDestroy);
	LoadTexture(&this->texCrabWalk);
	// Link GameObjects device && texture
	this->player->animIdle->sprite->device = this->device;
	this->player->animIdle->sprite->texture = this->texPlayerIdle;
	this->player->animShoot->sprite->device = this->device;
	this->player->animShoot->sprite->texture = this->texPlayerShoot;
	this->player->animRun->sprite->device = this->device;
	this->player->animRun->sprite->texture = this->texPlayerRun;
	this->player->animJump->sprite->device = this->device;
	this->player->animJump->sprite->texture = this->texPlayerJump;
	this->player->animDuck->sprite->device = this->device;
	this->player->animDuck->sprite->texture = this->texPlayerDuck;
	this->player->animDuckFire->sprite->device = this->device;
	this->player->animDuckFire->sprite->texture = this->texPlayerDuckFire;
	this->fxDestroy->LinkTexture(this->texFxDestroy);
	this->fxTail->LinkTexture(this->texDefault);
	for (unsigned int i = 0; i < this->player->bullets.size(); i++) {
		this->player->bullets[i]->sprite->texture = this->texBullet;
		this->player->bullets[i]->fxDestroy = this->fxDestroy;
		this->player->bullets[i]->fxTail = this->fxTail;
	}
	this->crab->animWalk->sprite->device = this->device;
	this->crab->animWalk->sprite->texture = this->texCrabWalk;

	this->scene->Start();
}


/*------------------------------------------------------------------------------
< Update >
------------------------------------------------------------------------------*/
void SceneManager::Update() {
	this->scene->Update();
}


/*------------------------------------------------------------------------------
< Draw >
------------------------------------------------------------------------------*/
void SceneManager::Draw() {
	this->scene->Draw();
}


/*------------------------------------------------------------------------------
< LoadTexture >
------------------------------------------------------------------------------*/
void SceneManager::LoadTexture(Texture* texture) {
	D3DXCreateTextureFromFileEx(
		this->device, texture->path,
		texture->size.x, texture->size.y,
		1, 0,
		D3DFMT_A8R8G8B8, D3DPOOL_MANAGED, D3DX_FILTER_NONE, D3DX_FILTER_NONE, 0xFF000000, NULL, NULL,
		&texture->texture);
}
