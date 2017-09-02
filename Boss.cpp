
#include "Engine.h"

/*------------------------------------------------------------------------------
< Constructor >
------------------------------------------------------------------------------*/
Boss::Boss() {
	// Status
	this->status->hp = 100;
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
	// UIObject
	this->uiLife = new UIObject(0.0f, 0.0f, 100.0f, 2.0f);
	this->uiBossBG = new UIObject(200.0f - 56.0f, -120.0f + 16.0f, 112.0f, 32.0f);
}


/*------------------------------------------------------------------------------
< Destructor >
------------------------------------------------------------------------------*/
Boss::~Boss() {
	// Collider
	delete this->collider;
	// GameObject
	delete this->core;
	// UIObject
	delete this->uiLife;
	delete this->uiBossBG;
}


/*------------------------------------------------------------------------------
< Start >
------------------------------------------------------------------------------*/
void Boss::Start() {
	// Resources
	this->sprite->texture = this->resources->texBossEyeBall;
	this->uiLife->sprite->texture = this->resources->texDefault;
	this->uiBossBG->sprite->texture = this->resources->texUIBossBG;

	// Animation MakeFrame() || Sprite MakeSlice()
	this->sprite->SetTexture();
}


/*------------------------------------------------------------------------------
< Update >
------------------------------------------------------------------------------*/
void Boss::Update() {
	/* UIObject
	..............................................................................*/
	this->uiLife->offset = Float2D(200.0f - 6.0f - 0.05f * this->status->hp,  -120.0f + 20.0f);
	this->uiLife->transform->scale = Float2D(this->status->hp * 0.1f, 2.0f);
	if (!this->freeze) {
		if (this->status->hp > 600) {
			this->uiLife->sprite->SetColor(0,255,255,255);
		}
		else if (this->status->hp > 200) {
			this->uiLife->sprite->SetColor(255,192,0,255);
		}
		else {
			this->uiLife->sprite->SetColor(255,79,108,255);
		}
	}
	else {
		this->uiLife->sprite->SetColor(100,100,100,255);
	}

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
		if (!this->awake) {
			this->awake = true;
			this->status->hp = this->hp;
		}
		else {
			this->active = false;
			this->resources->audEnemyDestroy->Play();
			Instantiate(this->resources->enemyDestroy, this->transform);
		}
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
