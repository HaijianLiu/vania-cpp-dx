
#include "Engine.h"

/*------------------------------------------------------------------------------
< Constructor >
------------------------------------------------------------------------------*/
NoneObject::NoneObject(GameObject* parent, float x, float y) {
	// GetGameObjects and push_back
	this->gameObjects = GetGameObjects();
	this->gameObjects->push_back(this);
	// Get GetGameObject pointer
	this->gameObject = this;

	this->parent = parent;
	this->offset.x = x;
	this->offset.y = y;
	this->draw = false;
}


/*------------------------------------------------------------------------------
< Destructor >
------------------------------------------------------------------------------*/
NoneObject::~NoneObject() {

}


/*------------------------------------------------------------------------------
< Start >
------------------------------------------------------------------------------*/
void NoneObject::Start() {
	// Animation MakeFrame()
}


/*------------------------------------------------------------------------------
< Update >
------------------------------------------------------------------------------*/
void NoneObject::Update() {
	// Animation SetTexture() || Sprite SetTexture()
}


/*------------------------------------------------------------------------------
< On Trigger Enter >
------------------------------------------------------------------------------*/
void NoneObject::OnTriggerEnter(BoxCollider* other) {

}


/*------------------------------------------------------------------------------
< Fixed Update >
------------------------------------------------------------------------------*/
void NoneObject::FixedUpdate() {
	this->transform->position.x = this->parent->transform->position.x + this->offset.x;
	this->transform->position.y = this->parent->transform->position.y + this->offset.y;
}
