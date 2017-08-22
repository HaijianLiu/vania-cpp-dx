
#include "Engine.h"

/*------------------------------------------------------------------------------
< Constructor >
------------------------------------------------------------------------------*/
Player::Player() {
	// GetGameObjects and push_back
	this->gameObjects = GetGameObjects();
	this->gameObjects->push_back(this);
	// Get GetGameObject pointer
	this->gameObject = this;

	// Transform Size in real pixel (Int2D)
	this->transform->scale = Float2D(80.0f,80.0f);
	// Animation (divideX, divideY, sampleTime) || Slice (ID,positionX,positionY,sizeX,sizeY) all in real pixel
	this->animIdle = new Animation(3,1,15);
	this->animRun = new Animation(10,1,4);
	this->animJump = new Animation(6,1,4);
	// Collider (this,offsetX,offsetY,sizeX,sizeY) size is in real pixel && Collider is trigger ?
	this->collGroundCheck = new BoxCollider(this,0.0f,0.21f,1.0f,5.0f);
	this->collGroundCheck->trigger = true;
	this->collCeilingCheck = new BoxCollider(this,0.0f,-0.09f,1.0f,5.0f);
	this->collCeilingCheck->trigger = true;
	this->collHorizonCheck = new BoxCollider(this,0.0f,0.06f,18.0f,32.0f);
	this->collHorizonCheck->trigger = true;
	// Camera
	this->camera = GetCamera();
	// Bullet
	for (int i = 0; i < 16; i++) {
		this->bullets.push_back(new Bullet());
	}
}


/*------------------------------------------------------------------------------
< Destructor >
------------------------------------------------------------------------------*/
Player::~Player() {
	// delete objects
	delete this->animIdle;
	delete this->animRun;
	delete this->animJump;
	delete this->collGroundCheck;
	delete this->collCeilingCheck;
	delete this->collHorizonCheck;
	for (unsigned int i = 0; i < this->bullets.size(); i++) {
		delete this->bullets[i];
	}
}


/*------------------------------------------------------------------------------
< Start >
------------------------------------------------------------------------------*/
void Player::Start() {
	// Animation MakeFrame() || Sprite MakeSlice()
	this->animIdle->MakeFrame();
	this->animRun->MakeFrame();
	this->animJump->MakeFrame();
}


/*------------------------------------------------------------------------------
< Update >
------------------------------------------------------------------------------*/
void Player::Update() {

	/* Transform
	..............................................................................*/
	// move
	if (GetKeyboardPress(DIK_LEFT)) {
		this->move = true;
		this->right = false;
		this->transform->position.x -= this->speed * this->time->deltaTime;
	}
	else if (GetKeyboardPress(DIK_RIGHT)) {
		this->move = true;
		this->right = true;
		this->transform->position.x += this->speed * this->time->deltaTime;
	}
	else {
		this->move = false;
	}
	// jump
	if (GetKeyboardPress(DIK_SPACE)) {
		if (!this->air) {
			this->verticalSpeed = this->jumpPower;
			this->air = true;
		}
	}
	// gravity
	this->verticalSpeed -= this->gravity * this->time->deltaTime;
	this->transform->position.y -= this->verticalSpeed * this->time->deltaTime;
	if (this->verticalSpeed < -1.0f) {
		this->air = true;
	}

	/* Animation
	..............................................................................*/
	// Animation SetTexture() || Sprite SetTexture()
	if (this->air) {
		this->animJump->sprite->flipX = !this->right;
		this->animJump->SetTexture(this->sprite->vertex);
		this->sprite->texture = this->animJump->sprite->texture;
	}
	else {
		if (this->move) {
			this->animRun->sprite->flipX = !this->right;
			this->animRun->SetTexture(this->sprite->vertex);
			this->sprite->texture = this->animRun->sprite->texture;
		}
		if (!this->move) {
			this->animIdle->sprite->flipX = !this->right;
			this->animIdle->SetTexture(this->sprite->vertex);
			this->sprite->texture = this->animIdle->sprite->texture;
		}
	}
}


/*------------------------------------------------------------------------------
< On Trigger Enter >
------------------------------------------------------------------------------*/
void Player::OnTriggerEnter(BoxCollider* other) {
	/* Transform
	..............................................................................*/
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


/*------------------------------------------------------------------------------
< Fixed Update >
------------------------------------------------------------------------------*/
void Player::FixedUpdate() {
	/* Camera
	..............................................................................*/
	this->camera->position.x = this->transform->position.x;
	this->camera->position.y = this->transform->position.y;

	/* Fire
	..............................................................................*/
	if (GetKeyboardPress(DIK_F)) {
		if ((float)this->time->currentTime > (float)this->lastFire + this->fireColdDown * 1000.0f) {
			for (unsigned int i = 0; i < this->bullets.size(); i++) {
				if (!this->bullets[i]->gameObject->active) {
					this->lastFire = this->time->currentTime;
					this->bullets[i]->birthTime = this->time->currentTime;
					this->bullets[i]->right = this->right;
					this->bullets[i]->gameObject->active = true;
					if (this->right) {
						this->bullets[i]->transform->position.x = this->transform->position.x + 0.2f;
					}
					else {
						this->bullets[i]->transform->position.x = this->transform->position.x - 0.2f;
					}
					this->bullets[i]->transform->position.y = this->transform->position.y - 0.015f;
					break;
				}
			}
		}
	}
}
