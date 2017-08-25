
#include "Engine.h"

/*------------------------------------------------------------------------------
< Constructor >
------------------------------------------------------------------------------*/
Ground::Ground() {
	// GetGameObjects and push_back
	this->gameObjects = GetGameObjects();
	this->gameObjects->push_back(this);
	// Get GetGameObject pointer
	this->gameObject = this;
	// Draw
	this->draw = false;

	// Transform Size in real pixel (Int2D)
				// get from scene mapData
	// Animation (divideX, divideY, sampleTime) || Slice (ID,positionX,positionY,sizeX,sizeY) all in real pixel
				// get from scene mapData
	// Collider (this,offsetX,offsetY,sizeX,sizeY) size is in real pixel && Collider is trigger ?
	this->collider = new BoxCollider(this,0.0f,0.0f,16.0f,16.0f);
}


/*------------------------------------------------------------------------------
< Destructor >
------------------------------------------------------------------------------*/
Ground::~Ground() {
	// delete objects
	delete this->collider;
}


/*------------------------------------------------------------------------------
< Start >
------------------------------------------------------------------------------*/
void Ground::Start() {
	// Animation MakeFrame()
}


/*------------------------------------------------------------------------------
< Update >
------------------------------------------------------------------------------*/
void Ground::Update() {

	// Animation SetTexture() || Sprite SetTexture()
	// this->sprite->SetTexture();
}


/*------------------------------------------------------------------------------
< On Trigger Enter >
------------------------------------------------------------------------------*/
void Ground::OnTriggerEnter(BoxCollider* other) {

}


/*------------------------------------------------------------------------------
< Fixed Update >
------------------------------------------------------------------------------*/
void Ground::FixedUpdate() {

}
