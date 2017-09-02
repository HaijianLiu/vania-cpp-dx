
#include "Engine.h"

/*------------------------------------------------------------------------------
< Constructor >
------------------------------------------------------------------------------*/
Ball::Ball() {
	// Status
	this->status->hp = 100;
	this->status->damage = 30;
	// Transform Size in real pixel (Int2D)
	this->transform->scale = Float2D(16.0f,16.0f);
	// Animation (divideX, divideY, sampleTime) || Slice (ID,positionX,positionY,sizeX,sizeY) all in real pixel
	this->sprite->slice = Slice(0,0,0,16,16);
	// Collider (this,offsetX,offsetY,sizeX,sizeY) size is in real pixel && Collider is trigger ?
	this->collGroundCheck = new BoxCollider(this,0.0f,0.07f,4.0f,4.0f);
	this->collGroundCheck->trigger = true;
	this->collGroundCheck->tag = "ground check";
	this->collCeilingCheck = new BoxCollider(this,0.0f,-0.07f,4.0f,4.0f);
	this->collCeilingCheck->trigger = true;
	this->collCeilingCheck->tag = "ceiling check";
	this->collHorizonCheck = new BoxCollider(this,0.0f,0.0f,16.0f,16.0f);
	this->collHorizonCheck->trigger = true;
	this->collHorizonCheck->tag = "enemy";

	// GameObject
	this->orb = new Orb();
}


/*------------------------------------------------------------------------------
< Destructor >
------------------------------------------------------------------------------*/
Ball::~Ball() {
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
void Ball::Start() {
	// Resources
	this->sprite->texture = this->resources->texBall;

	// Animation MakeFrame()
}


/*------------------------------------------------------------------------------
< Update >
------------------------------------------------------------------------------*/
void Ball::Update() {
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
	if (this->right) {
		this->transform->position.x += this->horizonSpeed * this->time->deltaTime;
	}
	else {
		this->transform->position.x -= this->horizonSpeed * this->time->deltaTime;
	}

	if (this->up) {
		this->transform->position.y -= this->verticalSpeed * this->time->deltaTime;
	}
	else {
		this->transform->position.y += this->verticalSpeed * this->time->deltaTime;
	}
	/* Animation
	..............................................................................*/
	// Animation SetTexture() || Sprite SetTexture()
	this->sprite->SetTexture();
}


/*------------------------------------------------------------------------------
< On Trigger Enter >
------------------------------------------------------------------------------*/
void Ball::OnTriggerEnter(BoxCollider* other) {
	/* Transform if tag = "ground"
	..............................................................................*/
	if (other->tag == "ground" || other->tag == "ai") {
		this->resources->audBallBounce->Play();
		if (this->collGroundCheck->enter == true) {
			this->transform->position.y = other->gameObject->transform->position.y + other->offset.y - other->halfSize.y * PIXEL_TO_UNIT - this->collGroundCheck->offset.y - this->collGroundCheck->halfSize.y * PIXEL_TO_UNIT;
			this->up = true;
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
		if (this->collCeilingCheck->enter == true) {
			this->transform->position.y = other->gameObject->transform->position.y + other->offset.y + other->halfSize.y * PIXEL_TO_UNIT - this->collCeilingCheck->offset.y + this->collCeilingCheck->halfSize.y * PIXEL_TO_UNIT;
			this->up = false;
		}
	}

	/* Damage if tag = "bullet"
	..............................................................................*/
	if (other->tag == "bullet") {
		this->right = !this->right;
		this->up = !this->up;
		this->sprite->Flash();
		this->status->hp -= other->gameObject->status->damage;
	}
}


/*------------------------------------------------------------------------------
< Fixed Update >
------------------------------------------------------------------------------*/
void Ball::FixedUpdate() {

}
