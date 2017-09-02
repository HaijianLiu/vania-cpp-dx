
#include "Engine.h"

/*------------------------------------------------------------------------------
< Constructor >
------------------------------------------------------------------------------*/
Jumper::Jumper() {
	// Status
	this->status->hp = 100;
	this->status->damage = 30;
	// Transform Size in real pixel (Int2D)
	this->transform->scale = Float2D(47.0f,32.0f);
	// Animation (divideX, divideY, sampleTime) || Slice (ID,positionX,positionY,sizeX,sizeY) all in real pixel
	this->animIdle = new Animation(4,1,15);
	this->animJump = new Animation(1,1,60);
	// Collider (this,offsetX,offsetY,sizeX,sizeY) size is in real pixel && Collider is trigger ?
	this->collGroundCheck = new BoxCollider(this,0.0f,0.14f,4.0f,4.0f);
	this->collGroundCheck->trigger = true;
	this->collGroundCheck->tag = "ground check";
	this->collCeilingCheck = new BoxCollider(this,0.0f,-0.05f,4.0f,4.0f);
	this->collCeilingCheck->trigger = true;
	this->collCeilingCheck->tag = "ceiling check";
	this->collHorizonCheck = new BoxCollider(this,0.0f,0.05f,28.0f,20.0f);
	this->collHorizonCheck->trigger = true;
	this->collHorizonCheck->tag = "enemy";

	// GameObject
	this->orb = new Orb();
}


/*------------------------------------------------------------------------------
< Destructor >
------------------------------------------------------------------------------*/
Jumper::~Jumper() {
	// Animation
	delete this->animIdle;
	delete this->animJump;
	// Collider
	delete this->collGroundCheck;
	delete this->collCeilingCheck;
	delete this->collHorizonCheck;
	// GameObject
	delete this->orb;
}


/*------------------------------------------------------------------------------
< Start >
------------------------------------------------------------------------------*/
void Jumper::Start() {
	// Resources
	this->animIdle->sprite->device = this->resources->device;
	this->animIdle->sprite->texture = this->resources->texJumperIdle;
	this->animJump->sprite->device = this->resources->device;
	this->animJump->sprite->texture = this->resources->texJumperJump;

	// Animation MakeFrame() || Sprite MakeSlice()
	this->animIdle->MakeFrame();
	this->animJump->MakeFrame();
}


/*------------------------------------------------------------------------------
< Update >
------------------------------------------------------------------------------*/
void Jumper::Update() {
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
	if (!this->air) {
		if (this->time->currentTime > this->lastJump + this->jumpColdDown * 1000.0f) {
			if (this->target->transform->position.x > this->transform->position.x) {
				this->right = true;
			}
			else {
				this->right = false;
			}
			this->verticalSpeed = this->jumpPower;
			this->air = true;
			this->lastJump = this->time->currentTime;
		}
	}
	else {
		if (!this->right) {
			this->transform->position.x -= this->speed * this->time->deltaTime;
		}
		else {
			this->transform->position.x += this->speed * this->time->deltaTime;
		}
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
	if (this->air) {
		this->animJump->sprite->flipX = this->right;
		this->animJump->SetTexture(this->sprite->vertex);
		this->sprite->texture = this->animJump->sprite->texture;
	}
	else {
		this->animIdle->sprite->flipX = this->right;
		this->animIdle->SetTexture(this->sprite->vertex);
		this->sprite->texture = this->animIdle->sprite->texture;
	}
}


/*------------------------------------------------------------------------------
< On Trigger Enter >
------------------------------------------------------------------------------*/
void Jumper::OnTriggerEnter(BoxCollider* other) {
	/* Transform if tag = "ground"
	..............................................................................*/
	if (other->tag == "ground") {
		if (this->collGroundCheck->enter == true) {
			this->transform->position.y = other->gameObject->transform->position.y + other->offset.y - other->halfSize.y * PIXEL_TO_UNIT - this->collGroundCheck->offset.y - this->collGroundCheck->halfSize.y * PIXEL_TO_UNIT;
			this->air = false;
			this->verticalSpeed = 0.0f;
		}
		if (this->collHorizonCheck->enter == true) {
			if (this->transform->position.x > other->gameObject->transform->position.x) {
				this->transform->position.x = other->gameObject->transform->position.x + other->offset.x + other->halfSize.x * PIXEL_TO_UNIT - this->collHorizonCheck->offset.x + this->collHorizonCheck->halfSize.x * PIXEL_TO_UNIT;
			}
			if (this->transform->position.x < other->gameObject->transform->position.x) {
				this->transform->position.x = other->gameObject->transform->position.x + other->offset.x - other->halfSize.x * PIXEL_TO_UNIT - this->collHorizonCheck->offset.x - this->collHorizonCheck->halfSize.x * PIXEL_TO_UNIT;
			}
		}
		if (this->collCeilingCheck->enter == true) {
			this->transform->position.y = other->gameObject->transform->position.y + other->offset.y + other->halfSize.y * PIXEL_TO_UNIT - this->collCeilingCheck->offset.y + this->collCeilingCheck->halfSize.y * PIXEL_TO_UNIT;
			this->verticalSpeed = 0.0f;
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
void Jumper::FixedUpdate() {

}
