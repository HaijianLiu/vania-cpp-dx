
#include "Engine.h"

/*------------------------------------------------------------------------------
< Constructor >
------------------------------------------------------------------------------*/
Block::Block() {
	// Status
	this->status->hp = 100;
	// Transform Size in real pixel (Int2D)
	this->transform->scale = Float2D(16.0f,16.0f);
	// Animation (divideX, divideY, sampleTime) || Slice (ID,positionX,positionY,sizeX,sizeY) all in real pixel
	this->sprite->slice = Slice(0,0,0,16,16);
	// Collider (this,offsetX,offsetY,sizeX,sizeY) size is in real pixel && Collider is trigger ?
	this->collider = new BoxCollider(this,0.0f,0.0f,16.0f,16.0f);
	this->collider->tag = "ground";
}


/*------------------------------------------------------------------------------
< Destructor >
------------------------------------------------------------------------------*/
Block::~Block() {

}


/*------------------------------------------------------------------------------
< Start >
------------------------------------------------------------------------------*/
void Block::Start() {
	// Resources
	this->sprite->texture = this->resources->texBlock;
	// Animation MakeFrame()
}


/*------------------------------------------------------------------------------
< Update >
------------------------------------------------------------------------------*/
void Block::Update() {
	if (this->status->hp < 70 && this->status->hp >= 40) {
		this->sprite->slice = Slice(0,16,0,16,16);
	}
	else if (this->status->hp < 40 && this->status->hp > 0) {
		this->sprite->slice = Slice(0,32,0,16,16);
	}
	else if (this->status->hp <= 0) {
		this->active = false;
	}

	// Animation SetTexture() || Sprite SetTexture()
	this->sprite->SetTexture();
}


/*------------------------------------------------------------------------------
< On Trigger Enter >
------------------------------------------------------------------------------*/
void Block::OnTriggerEnter(BoxCollider* other) {
	if (other->tag == "bullet") {
		this->status->hp -= other->gameObject->status->damage;
	}
	if (other->tag == "ground check") {
		this->status->hp -= (int)(this->destroySpeed * this->time->deltaTime);
	}
}


/*------------------------------------------------------------------------------
< Fixed Update >
------------------------------------------------------------------------------*/
void Block::FixedUpdate() {

}
