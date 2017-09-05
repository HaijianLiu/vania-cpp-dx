
#include "Engine.h"

/*------------------------------------------------------------------------------
< Constructor >
------------------------------------------------------------------------------*/
Ghost::Ghost() {
	// Set GameObject
	this->active = false;
	this->layer = 1;
	this->status->hp = this->hp;
	this->status->damage = 30.0f;
	// Transform Size in real pixel (Int2D)
	this->transform->scale = Float2D(28.0f,37.0f);
	// Animation (divideX, divideY, sampleTime) || Slice (ID,positionX,positionY,sizeX,sizeY) all in real pixel
	this->animation = new Animation(4,1,15);
	// Collider (this,offsetX,offsetY,sizeX,sizeY) size is in real pixel && Collider is trigger ?
	this->collider = new BoxCollider(this,0.0f,0.0f,24.0f,24.0f);
	this->collider->tag = "enemy";
}


/*------------------------------------------------------------------------------
< Destructor >
------------------------------------------------------------------------------*/
Ghost::~Ghost() {
	// delete objects
	delete this->collider;
	delete this->animation;
}


/*------------------------------------------------------------------------------
< Start >
------------------------------------------------------------------------------*/
void Ghost::Start() {
	// Resources
	this->animation->sprite->device = this->resources->device;
	this->animation->sprite->texture = this->resources->texGhost;

	// Animation MakeFrame() || Sprite MakeSlice()
	this->animation->MakeFrame();
}


/*------------------------------------------------------------------------------
< Update >
------------------------------------------------------------------------------*/
void Ghost::Update() {
	/* Death
	..............................................................................*/
	if (this->status->hp <= 0) {
		this->active = false;
		this->resources->audEnemyDestroy->Play();
		Instantiate(this->resources->enemyDestroy, this->transform);
	}

	/* Transform
	..............................................................................*/
	float angle = atan((this->target->transform->position.y - this->transform->position.y) / (this->target->transform->position.x - this->transform->position.x));

	if (this->target->transform->position.x < this->transform->position.x) {
		this->transform->position.x -= cos(angle) * this->speed * this->time->deltaTime;
		this->transform->position.y -= sin(angle) * this->speed * this->time->deltaTime;
	}
	else {
		this->transform->position.x += cos(angle) * this->speed * this->time->deltaTime;
		this->transform->position.y += sin(angle) * this->speed * this->time->deltaTime;
	}


	// Animation SetTexture() || Sprite SetTexture()
	this->animation->SetTexture(this->sprite->vertex);
	this->sprite->texture = this->animation->sprite->texture;
}


/*------------------------------------------------------------------------------
< On Trigger Enter >
------------------------------------------------------------------------------*/
void Ghost::OnTriggerEnter(BoxCollider* other) {
	/* Damage if tag = "bullet"
	..............................................................................*/
	if (other->tag == "bullet") {
		this->sprite->Flash();
		this->status->hp -= other->gameObject->status->damage;
	}
	/* dead if tag = "player"
	..............................................................................*/
	if (other->tag == "player") {
		this->active = false;
		this->resources->audEnemyDestroy->Play();
		Instantiate(this->resources->enemyDestroy, this->transform);
	}
}


/*------------------------------------------------------------------------------
< Fixed Update >
------------------------------------------------------------------------------*/
void Ghost::FixedUpdate() {

}
