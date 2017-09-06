
#include "Engine.h"

/*------------------------------------------------------------------------------
< Constructor >
------------------------------------------------------------------------------*/
Orb::Orb() {
	// Set GameObject
	this->active = false;
	this->status->hp = 300;
	// Transform Size in real pixel (Int2D)
	this->transform->scale = Float2D(16.0f,16.0f);
	// Animation (divideX, divideY, sampleTime) || Slice (ID,positionX,positionY,sizeX,sizeY) all in real pixel
	this->sprite->slice = Slice(0,16,0,16,16);
	// Collider (this,offsetX,offsetY,sizeX,sizeY) size is in real pixel && Collider is trigger ?
	this->collider = new BoxCollider(this,0.0f,0.0f,16.0f,16.0f);
	this->collider->tag = "orb";
}


/*------------------------------------------------------------------------------
< Destructor >
------------------------------------------------------------------------------*/
Orb::~Orb() {
	delete this->collider;
}


/*------------------------------------------------------------------------------
< Start >
------------------------------------------------------------------------------*/
void Orb::Start() {
	// Resources
	this->sprite->texture = this->resources->texOrb;
	this->fxOrb = this->resources->fxOrb;

	// Animation MakeFrame()
}


/*------------------------------------------------------------------------------
< Update >
------------------------------------------------------------------------------*/
void Orb::Update() {
	this->transform->position.y += 0.002f * sin(this->time->currentTime/300.0f);
	this->fxOrb->Instantiate(this->transform);

	// Animation SetTexture() || Sprite SetTexture()
	this->sprite->SetTexture();
	// this->animation->SetTexture(this->sprite->vertex);
	// this->sprite->texture = this->animation->sprite->texture;
}


/*------------------------------------------------------------------------------
< On Trigger Enter >
------------------------------------------------------------------------------*/
void Orb::OnTriggerEnter(BoxCollider* other) {
	if (other->tag == "player") {
		this->active = false;
		this->resources->audOrbGet->Play();
	}
}


/*------------------------------------------------------------------------------
< Fixed Update >
------------------------------------------------------------------------------*/
void Orb::FixedUpdate() {

}
