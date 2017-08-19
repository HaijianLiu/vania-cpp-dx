
#include "Engine.h"

/*------------------------------------------------------------------------------
< Constructor >
------------------------------------------------------------------------------*/
Ground::Ground() {
	// GetGameObjects and push_back
	this->gameObjects = GetGameObjects();
	this->gameObjects->push_back(this);
	// Transform Size in real pixel (Int2D)
	this->transform->size = Int2D(32, 32);
	// Animation (divideX, divideY, sampleTime) || Slice (name,positionX,positionY,sizeX,sizeY) all in real pixel
	this->slice = Slice("Floor", 160, 192 - 64 - 32, 32, 32);
	// Collider (this,offsetX,offsetY,sizeX,sizeY) size is in real pixel && Collider is trigger ?
	this->collider = new BoxCollider(this,0.0f,0.0f,32.0f,32.0f);
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
	// set Animation || set Slice
	this->sprite->MakeSlice(this->slice);
	this->sprite->SetTexture(this->sprite->vertex, "Floor");
}


/*------------------------------------------------------------------------------
< Update >
------------------------------------------------------------------------------*/
void Ground::Update() {

}


/*------------------------------------------------------------------------------
< Draw >
------------------------------------------------------------------------------*/
void Ground::Draw() {
	this->sprite->Draw(this->sprite->vertex);
}


/*------------------------------------------------------------------------------
< On Trigger Enter >
------------------------------------------------------------------------------*/
void Ground::OnTriggerEnter(BoxCollider* other) {

}
