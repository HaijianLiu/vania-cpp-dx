
#include "Engine.h"

/*------------------------------------------------------------------------------
< Constructor >
------------------------------------------------------------------------------*/
Bullet::Bullet() {
	// Transform Size in real pixel (Int2D)
	this->transform->scale = Float2D(4.0f,4.0f);
	// Animation (divideX, divideY, sampleTime) || Slice (ID,positionX,positionY,sizeX,sizeY) all in real pixel
	this->sprite->slice = Slice(0,0,0,4,4);
	// Collider (this,offsetX,offsetY,sizeX,sizeY) size is in real pixel && Collider is trigger ?
	this->collider = new BoxCollider(this,0.0f,0.0f,8.0f,8.0f);
	this->collider->trigger = true;
	this->collider->tag = "bullet";
	// Default GameObject active == true
	this->active = false;
}


/*------------------------------------------------------------------------------
< Destructor >
------------------------------------------------------------------------------*/
Bullet::~Bullet() {
	// delete objects
	delete this->collider;
}


/*------------------------------------------------------------------------------
< Start >
------------------------------------------------------------------------------*/
void Bullet::Start() {
	// Resources
	this->sprite->texture = this->resources->texBullet;
	// Animation MakeFrame()
}


/*------------------------------------------------------------------------------
< Update >
------------------------------------------------------------------------------*/
void Bullet::Update() {
	/* Destroy
	..............................................................................*/
	Destroy(this, this->lifeTime);

	/* Transform
	..............................................................................*/
	if (this->right) {
		this->transform->position.x += this->speed * this->time->deltaTime;
	}
	else {
		this->transform->position.x -= this->speed * this->time->deltaTime;
	}

	/* Particle System
	..............................................................................*/
	if (DistancePow(this->lastPosition, this->transform->position) >= pow(1.0f / (float)this->resources->fxTail->rate, 2.0f)) {
		this->resources->fxTail->Instantiate(this->transform);
		this->lastPosition = this->transform->position;
	}

	// Animation SetTexture() || Sprite SetTexture()
	this->sprite->SetTexture();
}


/*------------------------------------------------------------------------------
< On Trigger Enter >
------------------------------------------------------------------------------*/
void Bullet::OnTriggerEnter(BoxCollider* other) {
	if (other->tag != "player" && other->tag != "ai" && other->tag != "orb" && other->tag != "check point") {
		this->active = false;
		this->resources->fxDestroy->Instantiate(this->transform);
	}
}


/*------------------------------------------------------------------------------
< Fixed Update >
------------------------------------------------------------------------------*/
void Bullet::FixedUpdate() {

}


/*------------------------------------------------------------------------------
< Functions >
------------------------------------------------------------------------------*/
