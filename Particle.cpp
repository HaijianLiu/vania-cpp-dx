
#include "Engine.h"

/*------------------------------------------------------------------------------
< Constructor >
------------------------------------------------------------------------------*/
Particle::Particle() {
	// GetGameObjects and push_back
	this->gameObjects = GetGameObjects();
	this->gameObjects->push_back(this);
	// Get GetGameObject pointer
	this->gameObject = this;

	// Transform Size in real pixel (Int2D)
	this->transform->size = Int2D(4,4);
	// Animation (divideX, divideY, sampleTime) || Slice (ID,positionX,positionY,sizeX,sizeY) all in real pixel
	this->sprite->slice = Slice(0,0,0,32,32);
	// Default GameObject active == true
	this->gameObject->active = false;
}


/*------------------------------------------------------------------------------
< Destructor >
------------------------------------------------------------------------------*/
Particle::~Particle() {

}


/*------------------------------------------------------------------------------
< Start >
------------------------------------------------------------------------------*/
void Particle::Start() {
	// Animation MakeFrame()
}


/*------------------------------------------------------------------------------
< Update >
------------------------------------------------------------------------------*/
void Particle::Update() {
	/* Destroy
	..............................................................................*/
	Destroy(this->gameObject, this->lifeTime);

	/* Transform
	..............................................................................*/
	if (this->gameObject->active) {
		// Animation SetTexture() || Sprite SetTexture()
		this->sprite->SetTexture();
	}
}


/*------------------------------------------------------------------------------
< On Trigger Enter >
------------------------------------------------------------------------------*/
void Particle::OnTriggerEnter(BoxCollider* other) {
	
}


/*------------------------------------------------------------------------------
< Fixed Update >
------------------------------------------------------------------------------*/
void Particle::FixedUpdate() {

}


/*------------------------------------------------------------------------------
< Functions >
------------------------------------------------------------------------------*/
void Particle::Destroy(GameObject* gameObject, float time) {
	if ((float)this->time->currentTime - (float)this->birthTime > time * 1000.0f) {
		this->gameObject->active = false;
	}
}
