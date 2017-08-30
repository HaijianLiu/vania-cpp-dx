
#include "Engine.h"

/*------------------------------------------------------------------------------
< Constructor >
------------------------------------------------------------------------------*/
Block::Block() {
	// GetGameObjects and push_back
	this->gameObjects = GetGameObjects();
	this->gameObjects->push_back(this);
	// Get GetGameObject pointer
	this->gameObject = this;

	// Transform Size in real pixel (Int2D)
	this->transform->scale = Float2D(16.0f,16.0f);
	// Animation (divideX, divideY, sampleTime) || Slice (ID,positionX,positionY,sizeX,sizeY) all in real pixel
	this->sprite->slice = Slice(0,0,0,16,16);
	// Collider (this,offsetX,offsetY,sizeX,sizeY) size is in real pixel && Collider is trigger ?
	this->collider = new BoxCollider(this,0.0f,0.0f,16.0f,16.0f);
	this->collider->tag = "ground";
}


/*------------------------------------------------------------------------------
< Destructor >
------------------------------------------------------------------------------*/
Block::~Block() {

}


/*------------------------------------------------------------------------------
< Start >
------------------------------------------------------------------------------*/
void Block::Start() {
	// Resources
	this->sprite->texture = this->resources->texBlock;
	// Animation MakeFrame()
}


/*------------------------------------------------------------------------------
< Update >
------------------------------------------------------------------------------*/
void Block::Update() {
	if (this->hp < 70 && this->hp >= 40) {
		this->sprite->slice = Slice(0,16,0,16,16);
	}
	else if (this->hp < 40 && this->hp > 0) {
		this->sprite->slice = Slice(0,32,0,16,16);
	}
	else if (this->hp <= 0) {
		this->active = false;
		this->resources->audEnemyDestroy->Play();
		Instantiate(this->resources->enemyDestroy, this->transform);
	}

	// Animation SetTexture() || Sprite SetTexture()
	this->sprite->SetTexture();
}


/*------------------------------------------------------------------------------
< On Trigger Enter >
------------------------------------------------------------------------------*/
void Block::OnTriggerEnter(BoxCollider* other) {
	if (other->tag == "bullet") {
		this->hp -= 40;
	}
	if (other->tag == "ground check") {
		this->hp -= 100 * this->time->deltaTime;
	}
}


/*------------------------------------------------------------------------------
< Fixed Update >
------------------------------------------------------------------------------*/
void Block::FixedUpdate() {

}
