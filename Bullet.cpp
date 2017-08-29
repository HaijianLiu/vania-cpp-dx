
#include "Engine.h"

/*------------------------------------------------------------------------------
< Constructor >
------------------------------------------------------------------------------*/
Bullet::Bullet() {
	// GetGameObjects and push_back
	this->gameObjects = GetGameObjects();
	this->gameObjects->push_back(this);
	// Get GetGameObject pointer
	this->gameObject = this;

	// Transform Size in real pixel (Int2D)
	this->transform->scale = Float2D(4.0f,4.0f);
	// Animation (divideX, divideY, sampleTime) || Slice (ID,positionX,positionY,sizeX,sizeY) all in real pixel
	this->sprite->slice = Slice(0,0,0,4,4);
	// Collider (this,offsetX,offsetY,sizeX,sizeY) size is in real pixel && Collider is trigger ?
	this->collider = new BoxCollider(this,0.0f,0.0f,8.0f,8.0f);
	this->collider->trigger = true;
	this->collider->tag = "player";
	// Default GameObject active == true
	this->gameObject->active = false;
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
	// Particle System Parameters
	this->fxTail->rateOverTime = false;
	this->fxTail->SetStartLifeTimeRange(1.0f,2.0f);
	this->fxTail->SetStartSpeedRange(0.02f,0.2f);
	this->fxTail->SetStartSizeRange(0.01f,0.02f);
	this->fxTail->SetStartAngleRange(0.0f,2.0f*PI);
	this->fxTail->SetGravity(0.0f);
	this->fxTail->SetColor(63,140,242,255);
	this->fxDestroy->SetStartLifeTimeRange(0.1f,0.4f);
	this->fxDestroy->SetStartSpeedRange(0.2f,1.0f);
	this->fxDestroy->SetStartSizeRange(0.05f,0.1f);
	this->fxDestroy->SetGravity(0.0f);
	// this->fxDestroy->SetColor(113,214,247,10);
	// Animation MakeFrame()
}


/*------------------------------------------------------------------------------
< Update >
------------------------------------------------------------------------------*/
void Bullet::Update() {
	/* Destroy
	..............................................................................*/
	Destroy(this->gameObject, this->lifeTime);

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
	if (DistancePow(this->lastPosition, this->transform->position) >= pow(1.0f / (float)this->fxTail->rate, 2.0f)) {
		this->fxTail->Instantiate(this->transform);
		this->lastPosition = this->transform->position;
	}

	// Animation SetTexture() || Sprite SetTexture()
	this->sprite->SetTexture();
}


/*------------------------------------------------------------------------------
< On Trigger Enter >
------------------------------------------------------------------------------*/
void Bullet::OnTriggerEnter(BoxCollider* other) {
	if (other->tag != "player") {
		this->gameObject->active = false;
		this->fxDestroy->Instantiate(this->transform);
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
