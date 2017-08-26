
#include "Engine.h"

/*------------------------------------------------------------------------------
< Constructor >
------------------------------------------------------------------------------*/
OffsetObject::OffsetObject(GameObject* parent, float x, float y) {
	// GetGameObjects and push_back
	this->gameObjects = GetGameObjects();
	this->gameObjects->push_back(this);
	// Get GetGameObject pointer
	this->gameObject = this;
	// Set GameObject
	this->draw = false;

	this->parent = parent;
	this->offset.x = x;
	this->offset.y = y;
}


/*------------------------------------------------------------------------------
< Destructor >
------------------------------------------------------------------------------*/
OffsetObject::~OffsetObject() {

}


/*------------------------------------------------------------------------------
< Start >
------------------------------------------------------------------------------*/
void OffsetObject::Start() {
	// Animation MakeFrame()
}


/*------------------------------------------------------------------------------
< Update >
------------------------------------------------------------------------------*/
void OffsetObject::Update() {
	// Animation SetTexture() || Sprite SetTexture()
}


/*------------------------------------------------------------------------------
< On Trigger Enter >
------------------------------------------------------------------------------*/
void OffsetObject::OnTriggerEnter(BoxCollider* other) {

}


/*------------------------------------------------------------------------------
< Fixed Update >
------------------------------------------------------------------------------*/
void OffsetObject::FixedUpdate() {
	this->transform->position.x = this->parent->transform->position.x + this->offset.x;
	this->transform->position.y = this->parent->transform->position.y + this->offset.y;
}
