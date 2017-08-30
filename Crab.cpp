
#include "Engine.h"

/*------------------------------------------------------------------------------
< Constructor >
------------------------------------------------------------------------------*/
Crab::Crab() {
	// Status
	this->status->hp = 100;
	// Transform Size in real pixel (Int2D)
	this->transform->scale = Float2D(48.0f,32.0f);
	// Animation (divideX, divideY, sampleTime) || Slice (ID,positionX,positionY,sizeX,sizeY) all in real pixel
	this->animWalk = new Animation(4,1,15);
	// Collider (this,offsetX,offsetY,sizeX,sizeY) size is in real pixel && Collider is trigger ?
	this->collGroundCheck = new BoxCollider(this,0.0f,0.14f,1.0f,4.0f);
	this->collGroundCheck->trigger = true;
	this->collGroundCheck->tag = "enemy";
	this->collHorizonCheck = new BoxCollider(this,0.0f,0.0f,28.0f,28.0f);
	this->collHorizonCheck->trigger = true;
	this->collHorizonCheck->tag = "enemy";
}


/*------------------------------------------------------------------------------
< Destructor >
------------------------------------------------------------------------------*/
Crab::~Crab() {
	// Animation
	delete this->animWalk;
	// Collider
	delete this->collGroundCheck;
	delete this->collHorizonCheck;
}


/*------------------------------------------------------------------------------
< Start >
------------------------------------------------------------------------------*/
void Crab::Start() {
	// Resources
	this->animWalk->sprite->device = this->resources->device;
	this->animWalk->sprite->texture = this->resources->texCrabWalk;

	// Animation MakeFrame() || Sprite MakeSlice()
	this->animWalk->MakeFrame();
}


/*------------------------------------------------------------------------------
< Update >
------------------------------------------------------------------------------*/
void Crab::Update() {
	/* Death
	..............................................................................*/
	if (this->status->hp <= 0) {
		this->active = false;
		this->resources->audEnemyDestroy->Play();
		Instantiate(this->resources->enemyDestroy, this->transform);
	}

	/* Transform
	..............................................................................*/
	// move
	if (!this->right) {
		this->transform->position.x -= this->speed * this->time->deltaTime;
	}
	else {
		this->transform->position.x += this->speed * this->time->deltaTime;
	}

	/* Gravity
	..............................................................................*/
	this->verticalSpeed -= this->gravity * this->time->deltaTime;
	if (this->verticalSpeed <= - 0.9f * this->jumpPower) {
		this->verticalSpeed = - 0.9f * this->jumpPower;
	}
	this->transform->position.y -= this->verticalSpeed * this->time->deltaTime;
	if (this->verticalSpeed < -1.0f) {
		this->air = true;
	}

	/* Animation
	..............................................................................*/
	// Animation SetTexture() || Sprite SetTexture()
	this->animWalk->sprite->flipX = this->right;
	this->animWalk->SetTexture(this->sprite->vertex);
	this->sprite->texture = this->animWalk->sprite->texture;
}


/*------------------------------------------------------------------------------
< On Trigger Enter >
------------------------------------------------------------------------------*/
void Crab::OnTriggerEnter(BoxCollider* other) {
	/* Transform if tag = "ground"
	..............................................................................*/
	if (other->tag == "ground" || other->tag == "ai") {
		if (this->collGroundCheck->enter == true) {
			this->transform->position.y = other->gameObject->transform->position.y + other->offset.y - other->halfSize.y * PIXEL_TO_UNIT - this->collGroundCheck->offset.y - this->collGroundCheck->halfSize.y * PIXEL_TO_UNIT;
			this->air = false;
			this->verticalSpeed = 0.0f;
		}
		if (this->collHorizonCheck->enter == true) {
			if (this->transform->position.x > other->gameObject->transform->position.x) {
				this->transform->position.x = other->gameObject->transform->position.x + other->offset.x + other->halfSize.x * PIXEL_TO_UNIT - this->collHorizonCheck->offset.x + this->collHorizonCheck->halfSize.x * PIXEL_TO_UNIT;
				this->right = true;
			}
			if (this->transform->position.x < other->gameObject->transform->position.x) {
				this->transform->position.x = other->gameObject->transform->position.x + other->offset.x - other->halfSize.x * PIXEL_TO_UNIT - this->collHorizonCheck->offset.x - this->collHorizonCheck->halfSize.x * PIXEL_TO_UNIT;
				this->right = false;
			}
		}
	}
	/* Damage if tag = "bullet"
	..............................................................................*/
	if (other->tag == "bullet") {
		this->sprite->Flash();
		this->status->hp -= other->gameObject->status->damage;
	}
}


/*------------------------------------------------------------------------------
< Fixed Update >
------------------------------------------------------------------------------*/
void Crab::FixedUpdate() {

}
