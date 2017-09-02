
#include "Engine.h"

/*------------------------------------------------------------------------------
< Constructor >
------------------------------------------------------------------------------*/
Boss::Boss() {
	// Status
	this->status->hp = 1000;
	this->status->damage = 30;
	// Transform Size in real pixel (Int2D)
	this->transform->scale = Float2D(128.0f,128.0f);
	// Animation (divideX, divideY, sampleTime) || Slice (ID,positionX,positionY,sizeX,sizeY) all in real pixel
	this->sprite->slice = Slice(0,0,0,128,128);
	// Collider (this,offsetX,offsetY,sizeX,sizeY) size is in real pixel && Collider is trigger ?
	this->collider = new BoxCollider(this,0.0f,0.0f,64.0f,64.0f);
	this->collider->trigger = true;
	this->collider->tag = "boss";
	// GameObject
	this->core = new BossCore();
}


/*------------------------------------------------------------------------------
< Destructor >
------------------------------------------------------------------------------*/
Boss::~Boss() {
	// Collider
	delete this->collider;
	// GameObject
	delete this->core;
}


/*------------------------------------------------------------------------------
< Start >
------------------------------------------------------------------------------*/
void Boss::Start() {
	// Resources
	this->sprite->texture = this->resources->texBossEyeBall;

	// Animation MakeFrame() || Sprite MakeSlice()
	this->sprite->SetTexture();
}


/*------------------------------------------------------------------------------
< Update >
------------------------------------------------------------------------------*/
void Boss::Update() {
	/* Core Transform
	..............................................................................*/
	float angle = atan((this->target->transform->position.y - this->transform->position.y) / (this->target->transform->position.x - this->transform->position.x));

	if (this->target->transform->position.x < this->transform->position.x) {
		this->core->transform->position.x = this->transform->position.x + cos(angle) * this->core->radius;
		this->core->transform->position.y = this->transform->position.y + sin(angle) * this->core->radius;
	}
	else {
		this->core->transform->position.x = this->transform->position.x - cos(angle) * this->core->radius;
		this->core->transform->position.y = this->transform->position.y - sin(angle) * this->core->radius;
	}


	/* Death
	..............................................................................*/
	if (this->status->hp <= 0) {
		this->active = false;
		this->resources->audEnemyDestroy->Play();
		Instantiate(this->resources->enemyDestroy, this->transform);
	}
}


/*------------------------------------------------------------------------------
< On Trigger Enter >
------------------------------------------------------------------------------*/
void Boss::OnTriggerEnter(BoxCollider* other) {
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
void Boss::FixedUpdate() {

}
