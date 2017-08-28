
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
	this->animShoot = new Animation(3,1,4);
	this->animRun = new Animation(10,1,4);
	this->animJump = new Animation(6,1,4);
	this->animDuck = new Animation(1,1,60);
	this->animDuckFire = new Animation(3,1,4);
	// Collider (this,offsetX,offsetY,sizeX,sizeY) size is in real pixel && Collider is trigger ?
	this->collGroundCheck = new BoxCollider(this,0.0f,0.21f,8.0f,4.0f);
	this->collGroundCheck->trigger = true;
	this->collCeilingCheck = new BoxCollider(this,0.0f,-0.09f,1.0f,5.0f);
	this->collCeilingCheck->trigger = true;
	this->collHorizonCheck = new BoxCollider(this,0.0f,0.06f,24.0f,32.0f);
	this->collHorizonCheck->trigger = true;
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
	// Animation MakeFrame() || Sprite MakeSlice()
	this->animIdle->MakeFrame();
	this->animShoot->MakeFrame();
	this->animRun->MakeFrame();
	this->animJump->MakeFrame();
	this->animDuck->MakeFrame();
	this->animDuckFire->MakeFrame();
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
	if ((float)this->time->currentTime > (float)this->lastFire + 200.0f) {
		this->shoot = false;
	}
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

	/* Fire
	..............................................................................*/
	if (GetKeyboardTrigger(DIK_F)) {
		if ((float)this->time->currentTime > (float)this->lastFire + this->fireColdDown * 1000.0f) {
			this->shoot = true;
			this->audShoot->Play();
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
