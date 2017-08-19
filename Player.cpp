
#include "Engine.h"

/*------------------------------------------------------------------------------
< Texture Pathes >
------------------------------------------------------------------------------*/
#define TEXTURE_PLAYER_IDLE _T("assets/player-idle.png")
#define TEXTURE_PLAYER_RUN_SHOOT _T("assets/player-run-shoot.png")
#define TEXTURE_PLAYER_JUMP _T("assets/player-jump.png")


/*------------------------------------------------------------------------------
< Constructor >
------------------------------------------------------------------------------*/
Player::Player() {
	// GetGameObjects and push_back
	this->gameObjects = GetGameObjects();
	this->gameObjects->push_back(this);
	// Transform Size in real pixel (Int2D)
	this->transform->size = Int2D(80,80);
	// Animation (divideX, divideY, sampleTime) || Slice (name,positionX,positionY,sizeX,sizeY) all in real pixel
	this->animIdle = new Animation(3,1,15);
	this->animRun = new Animation(10,1,4);
	this->animJump = new Animation(6,1,4);
	// Collider (this,offsetX,offsetY,sizeX,sizeY) size is in real pixel && Collider is trigger ?
	this->collGroundCheck = new BoxCollider(this,0.0f,0.21f,1.0f,5.0f);
	this->collGroundCheck->trigger = true;
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
}


/*------------------------------------------------------------------------------
< Start >
------------------------------------------------------------------------------*/
void Player::Start() {
	// set Animation || set Slice
	this->animIdle->Start();
	this->animRun->Start();
	this->animJump->Start();
}


/*------------------------------------------------------------------------------
< Update >
------------------------------------------------------------------------------*/
void Player::Update() {

	// move
	if (GetKeyboardPress(DIK_LEFT)) {
		this->move = true;
		this->sprite->flipX = true;
		this->transform->position.x -= this->speed * this->time->deltaTime;
	}
	else if (GetKeyboardPress(DIK_RIGHT)) {
		this->move = true;
		this->sprite->flipX = false;
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
}


/*------------------------------------------------------------------------------
< On Trigger Enter >
------------------------------------------------------------------------------*/
void Player::OnTriggerEnter(BoxCollider* other) {
	// this->groundCounter++;
	this->transform->position.y = other->gameObject->transform->position.y + other->offset.y - other->halfSize.y * PIXEL_TO_UNIT - this->collGroundCheck->offset.y - this->collGroundCheck->halfSize.y * PIXEL_TO_UNIT;
	this->air = false;
	this->verticalSpeed = 0.0f;
}



/*------------------------------------------------------------------------------
< Draw >
------------------------------------------------------------------------------*/
void Player::Draw() {
	if (this->air) {
		this->animJump->Update(this->sprite->vertex);
		this->animJump->sprite->Draw(this->sprite->vertex);
	}
	else {
		if (this->move) {
			this->animRun->Update(this->sprite->vertex);
			this->animRun->sprite->Draw(this->sprite->vertex);
		}
		if (!this->move) {
			this->animIdle->Update(this->sprite->vertex);
			this->animIdle->sprite->Draw(this->sprite->vertex);
		}
	}
}
