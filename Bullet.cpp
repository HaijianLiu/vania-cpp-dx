
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
	this->collider = new BoxCollider(this,0.0f,0.0f,4.0f,4.0f);
	this->collider->trigger = true;
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

	// Animation SetTexture() || Sprite SetTexture()
	this->sprite->SetTexture();
}


/*------------------------------------------------------------------------------
< On Trigger Enter >
------------------------------------------------------------------------------*/
void Bullet::OnTriggerEnter(BoxCollider* other) {
	this->gameObject->active = false;
	this->fxDestroy->Instantiate(this->transform);
}


/*------------------------------------------------------------------------------
< Fixed Update >
------------------------------------------------------------------------------*/
void Bullet::FixedUpdate() {

}


/*------------------------------------------------------------------------------
< Functions >
------------------------------------------------------------------------------*/
