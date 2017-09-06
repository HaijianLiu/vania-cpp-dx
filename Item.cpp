
#include "Engine.h"

/*------------------------------------------------------------------------------
< Constructor >
------------------------------------------------------------------------------*/
Item::Item() {
	// Transform Size in real pixel (Int2D)
	this->transform->scale = Float2D(16.0f,16.0f);
	// Animation (divideX, divideY, sampleTime) || Slice (ID,positionX,positionY,sizeX,sizeY) all in real pixel
	this->sprite->slice = Slice(0,0,0,16,16);
	// Collider (this,offsetX,offsetY,sizeX,sizeY) size is in real pixel && Collider is trigger ?
	this->collider = new BoxCollider(this,0.0f,0.0f,16.0f,16.0f);
	this->collider->tag = "item";
}


/*------------------------------------------------------------------------------
< Destructor >
------------------------------------------------------------------------------*/
Item::~Item() {
	delete this->collider;
}


/*------------------------------------------------------------------------------
< Start >
------------------------------------------------------------------------------*/
void Item::Start() {
	// Resources
	this->sprite->texture = this->resources->texOrb;

	// Animation MakeFrame()
}


/*------------------------------------------------------------------------------
< Update >
------------------------------------------------------------------------------*/
void Item::Update() {

	// Animation SetTexture() || Sprite SetTexture()
	this->sprite->SetTexture();
}


/*------------------------------------------------------------------------------
< On Trigger Enter >
------------------------------------------------------------------------------*/
void Item::OnTriggerEnter(BoxCollider* other) {
	if (other->tag == "player") {
		this->active = false;
		this->resources->audOrbGet->Play();
	}
}


/*------------------------------------------------------------------------------
< Fixed Update >
------------------------------------------------------------------------------*/
void Item::FixedUpdate() {

}
