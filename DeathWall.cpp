
#include "Engine.h"

/*------------------------------------------------------------------------------
< Constructor >
------------------------------------------------------------------------------*/
DeathWall::DeathWall() {
	// Set GameObject
	this->active = false;
	this->layer = 1;
	this->status->damage = 30.0f;
	// Transform Size in real pixel (Int2D)
	this->transform->scale = Float2D(32.0f,32.0f);
	// Animation (divideX, divideY, sampleTime) || Slice (ID,positionX,positionY,sizeX,sizeY) all in real pixel
	this->sprite->slice = Slice(0,0,0,32,32);
	// Collider (this,offsetX,offsetY,sizeX,sizeY) size is in real pixel && Collider is trigger ?
	this->collider = new BoxCollider(this,0.0f,0.0f,32.0f,32.0f);
	this->collider->tag = "death wall";
}


/*------------------------------------------------------------------------------
< Destructor >
------------------------------------------------------------------------------*/
DeathWall::~DeathWall() {
	// delete objects
	delete this->collider;
}


/*------------------------------------------------------------------------------
< Start >
------------------------------------------------------------------------------*/
void DeathWall::Start() {
	if (!this->right) {
		this->sprite->flipX = true;
	}
	// Resources
	this->sprite->texture = this->resources->texDeathWall;
	// Animation MakeFrame()
}


/*------------------------------------------------------------------------------
< Update >
------------------------------------------------------------------------------*/
void DeathWall::Update() {
	if (this->right) {
		this->transform->position.x += this->speed * this->time->deltaTime;
		if (this->transform->position.x > this->startPosition.x) {
			this->transform->position.x = this->startPosition.x;
			this->active = false;
		}
	}
	else {
		this->transform->position.x -= this->speed * this->time->deltaTime;
		if (this->transform->position.x < this->startPosition.x) {
			this->transform->position.x = this->startPosition.x;
			this->active = false;
		}
	}

	// Animation SetTexture() || Sprite SetTexture()
	this->sprite->SetTexture();
}


/*------------------------------------------------------------------------------
< On Trigger Enter >
------------------------------------------------------------------------------*/
void DeathWall::OnTriggerEnter(BoxCollider* other) {

}


/*------------------------------------------------------------------------------
< Fixed Update >
------------------------------------------------------------------------------*/
void DeathWall::FixedUpdate() {

}


/*------------------------------------------------------------------------------
< Functions >
------------------------------------------------------------------------------*/
void DeathWall::Forward() {
	if (this->right) {
		this->active = true;
		this->transform->position.x -= 3.0f * this->speed * this->time->deltaTime;
		if (this->startPosition.x - this->transform->position.x > this->maxDistance) {
			this->transform->position.x = this->startPosition.x - this->maxDistance;
		}
	}
	else {
		this->active = true;
		this->transform->position.x += 3.0f * this->speed * this->time->deltaTime;
		if (this->transform->position.x - this->startPosition.x > this->maxDistance) {
			this->transform->position.x = this->startPosition.x + this->maxDistance;
		}
	}
}

void DeathWall::DeathArea(bool right) {
	if (right) {
		this->active = true;
		this->transform->position.x -= 3.0f * this->speed * this->time->deltaTime;
		if (this->startPosition.x - this->transform->position.x > this->maxArea) {
			this->transform->position.x = this->startPosition.x - this->maxArea;
		}
	}
	else {
		this->active = true;
		this->transform->position.x += 3.0f * this->speed * this->time->deltaTime;
		if (this->transform->position.x - this->startPosition.x > this->maxArea) {
			this->transform->position.x = this->startPosition.x + this->maxArea;
		}
	}
}
