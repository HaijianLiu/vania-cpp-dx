
#include "Engine.h"

/*------------------------------------------------------------------------------
< Constructor >
------------------------------------------------------------------------------*/
DeathBite::DeathBite() {
	// Set GameObject
	this->active = false;
	this->status->damage = 30.0f;
	// Transform Size in real pixel (Int2D)
	this->transform->scale = Float2D(64.0f,64.0f);
	// Animation (divideX, divideY, sampleTime) || Slice (ID,positionX,positionY,sizeX,sizeY) all in real pixel
	this->animBite = new Animation(4,1,15);
	this->animAppear = new Animation(4,1,15);
	this->animDisappear = new Animation(4,1,15);
	// Collider (this,offsetX,offsetY,sizeX,sizeY) size is in real pixel && Collider is trigger ?
	this->collider = new BoxCollider(this,0.0f,0.0f,32.0f,32.0f);
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

	// Animation SetTexture() || Sprite SetTexture()
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
