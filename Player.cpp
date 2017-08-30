﻿
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
	this->sprite->flashTime = this->hurtColdDown;
	// Animation (divideX, divideY, sampleTime) || Slice (ID,positionX,positionY,sizeX,sizeY) all in real pixel
	this->animIdle = new Animation(3,1,15);
	this->animShoot = new Animation(3,1,4);
	this->animRun = new Animation(10,1,4);
	this->animJump = new Animation(6,1,4);
	this->animDuck = new Animation(1,1,60);
	this->animDuckFire = new Animation(3,1,4);
	this->animHurt = new Animation(1,1,60);
	// Collider (this,offsetX,offsetY,sizeX,sizeY) size is in real pixel && Collider is trigger ?
	this->collGroundCheck = new BoxCollider(this,0.0f,0.21f,8.0f,4.0f);
	this->collGroundCheck->trigger = true;
	this->collGroundCheck->tag = "player";
	this->collCeilingCheck = new BoxCollider(this,0.0f,-0.09f,1.0f,5.0f);
	this->collCeilingCheck->trigger = true;
	this->collCeilingCheck->tag = "player";
	this->collHorizonCheck = new BoxCollider(this,0.0f,0.06f,24.0f,32.0f);
	this->collHorizonCheck->trigger = true;
	this->collHorizonCheck->tag = "player";
	// None Object
	this->leftFire = new OffsetObject(this,-0.2f,-0.015f);
	this->rightFire = new OffsetObject(this,0.2f,-0.015f);
	this->leftDuckFire = new OffsetObject(this,-0.2f,0.1f);
	this->rightDuckFire = new OffsetObject(this,0.2f,0.1f);
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
	delete this->animShoot;
	delete this->animRun;
	delete this->animJump;
	delete this->animDuck;
	delete this->animDuckFire;
	delete this->animHurt;
	delete this->collGroundCheck;
	delete this->collCeilingCheck;
	delete this->collHorizonCheck;
	delete this->leftFire;
	delete this->rightFire;
	delete this->leftDuckFire;
	delete this->rightDuckFire;
	for (unsigned int i = 0; i < this->bullets.size(); i++) {
		delete this->bullets[i];
	}
}


/*------------------------------------------------------------------------------
< Start >
------------------------------------------------------------------------------*/
void Player::Start() {
	/* Resources
	..............................................................................*/
	// Animation
	this->animIdle->sprite->device = this->resources->device;
	this->animIdle->sprite->texture = this->resources->texPlayerIdle;
	this->animShoot->sprite->device = this->resources->device;
	this->animShoot->sprite->texture = this->resources->texPlayerShoot;
	this->animRun->sprite->device = this->resources->device;
	this->animRun->sprite->texture = this->resources->texPlayerRun;
	this->animJump->sprite->device = this->resources->device;
	this->animJump->sprite->texture = this->resources->texPlayerJump;
	this->animDuck->sprite->device = this->resources->device;
	this->animDuck->sprite->texture = this->resources->texPlayerDuck;
	this->animDuckFire->sprite->device = this->resources->device;
	this->animDuckFire->sprite->texture = this->resources->texPlayerDuckFire;
	this->animHurt->sprite->device = this->resources->device;
	this->animHurt->sprite->texture = this->resources->texPlayerHurt;
	// Bullet
	for (unsigned int i = 0; i < this->bullets.size(); i++) {
		this->bullets[i]->sprite->texture = this->resources->texBullet;
		this->bullets[i]->fxDestroy = this->resources->fxDestroy;
		this->bullets[i]->fxTail = this->resources->fxTail;
	}
	// Audio
	this->audShoot = this->resources->audShoot;
	this->audLanding = this->resources->audLanding;


	// Animation MakeFrame() || Sprite MakeSlice()
	this->animIdle->MakeFrame();
	this->animShoot->MakeFrame();
	this->animRun->MakeFrame();
	this->animJump->MakeFrame();
	this->animDuck->MakeFrame();
	this->animDuckFire->MakeFrame();
	this->animHurt->MakeFrame();
}


/*------------------------------------------------------------------------------
< Update >
------------------------------------------------------------------------------*/
void Player::Update() {

	/* Transform
	..............................................................................*/
	if (!this->hurt) {
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
		if (GetKeyboardTrigger(DIK_SPACE)) {
			if (!this->air) {
				this->verticalSpeed = this->jumpPower;
				this->air = true;
			}
		}
		// duck
		if (GetKeyboardPress(DIK_DOWN)) {
			if (!this->air) {
				this->duck = true;
			}
		}
		else {
			this->duck = false;
		}
	}
	else {
		if (this->right) {
			this->transform->position.x -= this->backSpeed * this->time->deltaTime;
		}
		else {
			this->transform->position.x += this->backSpeed * this->time->deltaTime;
		}
	}

	/* Gravity
	..............................................................................*/
	this->verticalSpeed -= this->gravity * this->time->deltaTime;
	if (this->verticalSpeed <= - 0.8f * this->jumpPower) {
		this->verticalSpeed = - 0.8f * this->jumpPower;
	}
	this->transform->position.y -= this->verticalSpeed * this->time->deltaTime;
	if (this->verticalSpeed < -1.0f) {
		this->air = true;
	}

	/* Animation
	..............................................................................*/
	// Animation SetTexture() || Sprite SetTexture()
	if ((float)this->time->currentTime > (float)this->lastFire + 200.0f) {
		this->shoot = false;
	}
	if ((float)this->time->currentTime > (float)this->lastHurt + 0.3f * this->hurtColdDown * 1000.0f) {
		this->hurt = false;
	}

	if (!this->hurt) {
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
				if (this->duck) {
					if (this->shoot) {
						this->animDuckFire->sprite->flipX = !this->right;
						this->animDuckFire->SetTexture(this->sprite->vertex);
						this->sprite->texture = this->animDuckFire->sprite->texture;
					}
					else {
						this->animDuck->sprite->flipX = !this->right;
						this->animDuck->SetTexture(this->sprite->vertex);
						this->sprite->texture = this->animDuck->sprite->texture;
					}
				}
				else {
					if (this->shoot) {
						this->animShoot->sprite->flipX = !this->right;
						this->animShoot->SetTexture(this->sprite->vertex);
						this->sprite->texture = this->animShoot->sprite->texture;
					}
					else{
						this->animIdle->sprite->flipX = !this->right;
						this->animIdle->SetTexture(this->sprite->vertex);
						this->sprite->texture = this->animIdle->sprite->texture;
					}
				}
			}
		}
	}
	else {
		this->animHurt->sprite->flipX = !this->right;
		this->animHurt->SetTexture(this->sprite->vertex);
		this->sprite->texture = this->animHurt->sprite->texture;
	}
}


/*------------------------------------------------------------------------------
< On Trigger Enter >
------------------------------------------------------------------------------*/
void Player::OnTriggerEnter(BoxCollider* other) {
	/* Transform if tag = "ground"
	..............................................................................*/
	if (other->tag == "ground") {
		if (this->collGroundCheck->enter == true) {
			this->transform->position.y = other->gameObject->transform->position.y + other->offset.y - other->halfSize.y * PIXEL_TO_UNIT - this->collGroundCheck->offset.y - this->collGroundCheck->halfSize.y * PIXEL_TO_UNIT;
			this->air = false;
			if (this->verticalSpeed <= -0.2f * this->jumpPower) {
				this->audLanding->Play();
			}
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
	/* Shield if tag = "enemy"
	..............................................................................*/
	if (other->tag == "enemy") {
		if ((float)this->time->currentTime > (float)this->lastHurt + this->hurtColdDown * 1000.0f) {
			this->hurt = true;
			if (other->gameObject->transform->position.x > this->transform->position.x) {
				this->right = true;
			}
			else {
				this->right = false;
			}
			this->lastHurt = this->time->currentTime;
			this->verticalSpeed = 0.5f * this->jumpPower;
			this->sprite->Flash();
		}
	}
}


/*------------------------------------------------------------------------------
< Fixed Update >
------------------------------------------------------------------------------*/
void Player::FixedUpdate() {
	/* Fire
	..............................................................................*/
	if (!this->hurt) {
		if (GetKeyboardTrigger(DIK_F)) {
			if ((float)this->time->currentTime > (float)this->lastFire + this->fireColdDown * 1000.0f) {
				this->shoot = true;
				for (unsigned int i = 0; i < this->audShoot.size(); i++) {
					if (!this->audShoot[i]->Playing()) {
						this->audShoot[i]->Play();
						break;
					}
				}
				for (unsigned int i = 0; i < this->bullets.size(); i++) {
					if (!this->bullets[i]->gameObject->active) {
						this->lastFire = this->time->currentTime;
						this->bullets[i]->birthTime = this->time->currentTime;
						this->bullets[i]->right = this->right;
						this->bullets[i]->gameObject->active = true;
						if (this->right) {
							if (this->duck && !this->move && !this->air) {
								this->bullets[i]->transform->position = this->rightDuckFire->transform->position;
							}
							else {
								this->bullets[i]->transform->position = this->rightFire->transform->position;
							}
						}
						else {
							if (this->duck && !this->move && !this->air) {
								this->bullets[i]->transform->position = this->leftDuckFire->transform->position;
							}
							else {
								this->bullets[i]->transform->position = this->leftFire->transform->position;
							}
						}
						break;
					}
				}
			}
		}
	}
}
