
#include "Engine.h"

/*------------------------------------------------------------------------------
< Constructor >
------------------------------------------------------------------------------*/
Flyer::Flyer() {
	// Status
	this->status->hp = 100;
	this->status->damage = 30;
	// Transform Size in real pixel (Int2D)
	this->transform->scale = Float2D(32.0f,32.0f);
	// Animation (divideX, divideY, sampleTime) || Slice (ID,positionX,positionY,sizeX,sizeY) all in real pixel
	this->animFlyer = new Animation(2,1,15);
	// Collider (this,offsetX,offsetY,sizeX,sizeY) size is in real pixel && Collider is trigger ?
	this->collHorizonCheck = new BoxCollider(this,0.0f,0.0f,16.0f,16.0f);
	this->collHorizonCheck->trigger = true;
	this->collHorizonCheck->tag = "enemy";

	// GameObject
	this->orb = new Orb();
}


/*------------------------------------------------------------------------------
< Destructor >
------------------------------------------------------------------------------*/
Flyer::~Flyer() {
	// Animation
	delete this->animFlyer;
	// Collider
	delete this->collHorizonCheck;
	// GameObject
	delete this->orb;
}


/*------------------------------------------------------------------------------
< Start >
------------------------------------------------------------------------------*/
void Flyer::Start() {
	// Resources
	this->animFlyer->sprite->device = this->resources->device;
	this->animFlyer->sprite->texture = this->resources->texFlyer;

	// Animation MakeFrame() || Sprite MakeSlice()
	this->animFlyer->MakeFrame();
}


/*------------------------------------------------------------------------------
< Update >
------------------------------------------------------------------------------*/
void Flyer::Update() {
	/* Death
	..............................................................................*/
	if (this->status->hp <= 0) {
		this->active = false;
		this->resources->audEnemyDestroy->Play();
		Instantiate(this->resources->enemyDestroy, this->transform);
		Instantiate(this->orb, this->transform);
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

	/* Animation
	..............................................................................*/
	// Animation SetTexture() || Sprite SetTexture()
	this->animFlyer->sprite->flipX = this->right;
	this->animFlyer->SetTexture(this->sprite->vertex);
	this->sprite->texture = this->animFlyer->sprite->texture;
}


/*------------------------------------------------------------------------------
< On Trigger Enter >
------------------------------------------------------------------------------*/
void Flyer::OnTriggerEnter(BoxCollider* other) {
	/* Transform if tag = "ground"
	..............................................................................*/
	if (other->tag == "ground" || other->tag == "ai") {
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
void Flyer::FixedUpdate() {

}
