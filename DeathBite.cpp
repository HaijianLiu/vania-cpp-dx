
#include "Engine.h"

/*------------------------------------------------------------------------------
< Constructor >
------------------------------------------------------------------------------*/
DeathBite::DeathBite() {
	// Set GameObject
	this->active = false;
	this->layer = 1;
	this->status->damage = 30.0f;
	// Transform Size in real pixel (Int2D)
	this->transform->scale = Float2D(64.0f,64.0f);
	// Animation (divideX, divideY, sampleTime) || Slice (ID,positionX,positionY,sizeX,sizeY) all in real pixel
	this->animBite = new Animation(6,1,10);
	this->animAppear = new Animation(4,1,20);
	this->animDisappear = new Animation(4,1,20);
	// Collider (this,offsetX,offsetY,sizeX,sizeY) size is in real pixel && Collider is trigger ?
	this->collider = new BoxCollider(this,0.0f,0.0f,32.0f,32.0f);
	this->collider->active = false;
	this->collider->tag = "enemy";
}


/*------------------------------------------------------------------------------
< Destructor >
------------------------------------------------------------------------------*/
DeathBite::~DeathBite() {
	// delete objects
	delete this->animBite;
	delete this->animAppear;
	delete this->animDisappear;
	delete this->collider;
}


/*------------------------------------------------------------------------------
< Start >
------------------------------------------------------------------------------*/
void DeathBite::Start() {
	// Resources
	this->animBite->sprite->device = this->resources->device;
	this->animBite->sprite->texture = this->resources->texBossBiteBite;
	this->animAppear->sprite->device = this->resources->device;
	this->animAppear->sprite->texture = this->resources->texBossBiteAppear;
	this->animDisappear->sprite->device = this->resources->device;
	this->animDisappear->sprite->texture = this->resources->texBossBiteDisappear;

	// Animation MakeFrame()
	this->animBite->MakeFrame();
	this->animAppear->MakeFrame();
	this->animDisappear->MakeFrame();
}


/*------------------------------------------------------------------------------
< Update >
------------------------------------------------------------------------------*/
void DeathBite::Update() {
	if (this->time->currentTime > this->lastAppear + this->lastTime * 1000.0f) {
		this->active = false;
	}

	// Animation SetTexture() || Sprite SetTexture()
	if (this->time->currentTime < this->lastAppear + this->appearTime * 1000.0f) {
		this->animAppear->SetTexture(this->sprite->vertex);
		this->collider->active = false;
		this->sprite->texture = this->animAppear->sprite->texture;
	}
	if (this->time->currentTime >= this->lastAppear + this->appearTime * 1000.0f && this->time->currentTime <= this->lastAppear + (this->lastTime - this->appearTime) * 1000.0f) {
		this->collider->active = true;
		this->animBite->SetTexture(this->sprite->vertex);
		this->sprite->texture = this->animBite->sprite->texture;
	}
	if (this->time->currentTime > this->lastAppear + (this->lastTime - this->appearTime) * 1000.0f) {
		this->collider->active = false;
		this->animDisappear->SetTexture(this->sprite->vertex);
		this->sprite->texture = this->animDisappear->sprite->texture;
	}
}


/*------------------------------------------------------------------------------
< On Trigger Enter >
------------------------------------------------------------------------------*/
void DeathBite::OnTriggerEnter(BoxCollider* other) {

}


/*------------------------------------------------------------------------------
< Fixed Update >
------------------------------------------------------------------------------*/
void DeathBite::FixedUpdate() {

}


/*------------------------------------------------------------------------------
< Functions >
------------------------------------------------------------------------------*/
void DeathBite::Appear() {
	if (!this->active) {
		this->transform->position.x = this->target->transform->position.x;
		this->transform->position.y = this->target->transform->position.y;
		this->active = true;
		this->animAppear->counter = 0;
		this->animAppear->currentSprite = 0;
		this->animDisappear->counter = 0;
		this->animDisappear->currentSprite = 0;
		this->lastAppear = this->time->currentTime;
	}
}
