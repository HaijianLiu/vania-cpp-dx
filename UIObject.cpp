
#include "Engine.h"

/*------------------------------------------------------------------------------
< Constructor >
------------------------------------------------------------------------------*/
UIObject::UIObject(float offsetX, float offsetY, float sizeX, float sizeY) {
	// Set GameObject
	this->layer = 1;
	// Camera
	this->camera = GetCamera();
	// offset in real pixel
	this->offset = Float2D(offsetX,offsetY);
	// Transform Size in real pixel (Int2D)
	this->transform->scale = Float2D(sizeX,sizeY);
	// Animation (divideX, divideY, sampleTime) || Slice (ID,positionX,positionY,sizeX,sizeY) all in real pixel
	this->sprite->slice = Slice(0,0,0,(int)sizeX,(int)sizeY);
}


/*------------------------------------------------------------------------------
< Destructor >
------------------------------------------------------------------------------*/
UIObject::~UIObject() {

}


/*------------------------------------------------------------------------------
< Start >
------------------------------------------------------------------------------*/
void UIObject::Start() {
	// Animation MakeFrame()
}


/*------------------------------------------------------------------------------
< Update >
------------------------------------------------------------------------------*/
void UIObject::Update() {

	// Animation SetTexture() || Sprite SetTexture()
	this->sprite->SetTexture();
}


/*------------------------------------------------------------------------------
< On Trigger Enter >
------------------------------------------------------------------------------*/
void UIObject::OnTriggerEnter(BoxCollider* other) {

}


/*------------------------------------------------------------------------------
< Fixed Update >
------------------------------------------------------------------------------*/
void UIObject::FixedUpdate() {
	this->transform->position.x = this->camera->position.x + this->offset.x * PIXEL_TO_UNIT;
	this->transform->position.y = this->camera->position.y + this->offset.y * PIXEL_TO_UNIT;
}
