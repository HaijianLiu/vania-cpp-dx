
#include "Engine.h"

/*------------------------------------------------------------------------------
< Constructor >
------------------------------------------------------------------------------*/
AnimationObject::AnimationObject(int sizeX, int sizeY, int divideX, int divideY, int sampleTime) {
	// Set GameObject
	this->active = false;
	// Transform Size in real pixel (Int2D)
	this->transform->scale = Float2D((float)sizeX, (float)sizeY);
	// Animation (divideX, divideY, sampleTime) || Slice (ID,positionX,positionY,sizeX,sizeY) all in real pixel
	this->animation = new Animation(divideX, divideY, sampleTime);
}


/*------------------------------------------------------------------------------
< Destructor >
------------------------------------------------------------------------------*/
AnimationObject::~AnimationObject() {
	delete this->animation;
}


/*------------------------------------------------------------------------------
< Start >
------------------------------------------------------------------------------*/
void AnimationObject::Start() {
	// Animation MakeFrame()
	this->animation->MakeFrame();
}


/*------------------------------------------------------------------------------
< Update >
------------------------------------------------------------------------------*/
void AnimationObject::Update() {

}


/*------------------------------------------------------------------------------
< On Trigger Enter >
------------------------------------------------------------------------------*/
void AnimationObject::OnTriggerEnter(BoxCollider* other) {

}


/*------------------------------------------------------------------------------
< Fixed Update >
------------------------------------------------------------------------------*/
void AnimationObject::FixedUpdate() {
	if (!this->loop) {
		if (this->animation->currentSprite == this->animation->spriteMax - 1 && this->animation->counter == this->animation->sampleTime - 1) {
			this->active = false;
			AnimationObject::Reset();
		}
		else {
			// Animation SetTexture() || Sprite SetTexture()
			this->animation->SetTexture(this->sprite->vertex);
			this->sprite->texture = this->animation->sprite->texture;
		}
	}
}


/*------------------------------------------------------------------------------
< Reset > for Instantiate()
------------------------------------------------------------------------------*/
void AnimationObject::Reset() {
	this->animation->currentSprite = 0;
	this->animation->counter = 0;
	this->animation->SetTexture(this->sprite->vertex);
	this->sprite->texture = this->animation->sprite->texture;
}
