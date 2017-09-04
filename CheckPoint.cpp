
#include "Engine.h"

/*------------------------------------------------------------------------------
< Constructor >
------------------------------------------------------------------------------*/
CheckPoint::CheckPoint() {
	// Set GameObject
	this->active = false;
	// Transform Size in real pixel (Int2D)
	this->transform->scale = Float2D(32.0f,32.0f);
	// Animation (divideX, divideY, sampleTime) || Slice (ID,positionX,positionY,sizeX,sizeY) all in real pixel
	this->sprite->slice = Slice(0,32,0,32,32);
	// Collider (this,offsetX,offsetY,sizeX,sizeY) size is in real pixel && Collider is trigger ?
	this->collider = new BoxCollider(this,0.0f,0.0f,32.0f,32.0f);
	this->collider->tag = "check point";
}


/*------------------------------------------------------------------------------
< Destructor >
------------------------------------------------------------------------------*/
CheckPoint::~CheckPoint() {
	// delete objects
	delete this->collider;
}


/*------------------------------------------------------------------------------
< Start >
------------------------------------------------------------------------------*/
void CheckPoint::Start() {
	// Resources
	this->sprite->texture = this->resources->texCheckPoint;

	// Animation MakeFrame()
}


/*------------------------------------------------------------------------------
< Update >
------------------------------------------------------------------------------*/
void CheckPoint::Update() {

	// Animation SetTexture() || Sprite SetTexture()
	this->sprite->SetTexture();
}


/*------------------------------------------------------------------------------
< On Trigger Enter >
------------------------------------------------------------------------------*/
void CheckPoint::OnTriggerEnter(BoxCollider* other) {
	if (other->tag == "player" && !this->check) {
		for (unsigned int i = 0; i < this->sceneManager->scenes.size(); i++) {
			this->sceneManager->scenes[i]->checkPoint->check = false;
			this->sceneManager->scenes[i]->checkPoint->sprite->slice = Slice(0,32,0,32,32);
		}
		this->check = true;
		this->sceneManager->checkPoint = this->sceneManager->activeScene;
		this->sprite->slice = Slice(0,0,0,32,32);
		this->resources->audCheckPoint->Play();
	}
}


/*------------------------------------------------------------------------------
< Fixed Update >
------------------------------------------------------------------------------*/
void CheckPoint::FixedUpdate() {

}
