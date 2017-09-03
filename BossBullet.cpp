
#include "Engine.h"

/*------------------------------------------------------------------------------
< Constructor >
------------------------------------------------------------------------------*/
BossBullet::BossBullet() {
	// Set GameObject
	this->active = false;
	this->layer = 1;
	this->status->hp = this->hp;
	this->status->damage = 30.0f;
	// Transform Size in real pixel (Int2D)
	this->transform->scale = Float2D(21.0f,21.0f);
	// Animation (divideX, divideY, sampleTime) || Slice (ID,positionX,positionY,sizeX,sizeY) all in real pixel
	this->animation = new Animation(7,1,15);
	// Collider (this,offsetX,offsetY,sizeX,sizeY) size is in real pixel && Collider is trigger ?
	this->collider = new BoxCollider(this,0.0f,0.0f,16.0f,16.0f);
	this->collider->tag = "enemy";
}


/*------------------------------------------------------------------------------
< Destructor >
------------------------------------------------------------------------------*/
BossBullet::~BossBullet() {
	// delete objects
	delete this->collider;
	delete this->animation;
}


/*------------------------------------------------------------------------------
< Start >
------------------------------------------------------------------------------*/
void BossBullet::Start() {
	// Resources
	this->animation->sprite->device = this->resources->device;
	this->animation->sprite->texture = this->resources->texBossBullet;

	// Animation MakeFrame() || Sprite MakeSlice()
	this->animation->MakeFrame();
}


/*------------------------------------------------------------------------------
< Update >
------------------------------------------------------------------------------*/
void BossBullet::Update() {

	// Animation SetTexture() || Sprite SetTexture()
	this->animation->SetTexture(this->sprite->vertex);
	this->sprite->texture = this->animation->sprite->texture;
}


/*------------------------------------------------------------------------------
< On Trigger Enter >
------------------------------------------------------------------------------*/
void BossBullet::OnTriggerEnter(BoxCollider* other) {

}


/*------------------------------------------------------------------------------
< Fixed Update >
------------------------------------------------------------------------------*/
void BossBullet::FixedUpdate() {

}
