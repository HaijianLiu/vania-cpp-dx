﻿
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
	this->gameObjects = GetGameObjects();
	this->gameObjects->push_back(this);

	// pixel size
	this->transform->size = Int2D(80,80);
	// Animation
	this->animIdle = new Animation(240,80,3,1,15);
	this->animRun = new Animation(800,80,10,1,4);
	this->animJump = new Animation(480,80,6,1,4);
	// Collider
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
	this->animIdle->sprite->CreatTexture(TEXTURE_PLAYER_IDLE);
	this->animRun->sprite->CreatTexture(TEXTURE_PLAYER_RUN_SHOOT);
	this->animJump->sprite->CreatTexture(TEXTURE_PLAYER_JUMP);
}


/*------------------------------------------------------------------------------
< Update >
------------------------------------------------------------------------------*/
void Player::Update() {

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
}


/*------------------------------------------------------------------------------
< On Trigger Enter >
------------------------------------------------------------------------------*/
void Player::OnTriggerEnter(BoxCollider* other) {
	// this->groundCounter++;
	this->transform->position.y = other->gameObject->transform->position.y + other->offset.y - other->size.y / UNIT_TO_PIXEL - this->collGroundCheck->offset.y - this->collGroundCheck->size.y / UNIT_TO_PIXEL;
	this->air = false;
	this->verticalSpeed = 0.0f;
}



/*------------------------------------------------------------------------------
< Draw >
------------------------------------------------------------------------------*/
void Player::Draw() {
	if (this->air) {
		this->animJump->sprite->flipX = !this->right;
		this->animJump->Update(this->vertex);
		this->animJump->sprite->Draw(this->vertex);
	}
	else {
		if (this->move) {
			this->animRun->sprite->flipX = !this->right;
			this->animRun->Update(this->vertex);
			this->animRun->sprite->Draw(this->vertex);
		}
		if (!this->move) {
			this->animIdle->sprite->flipX = !this->right;
			this->animIdle->Update(this->vertex);
			this->animIdle->sprite->Draw(this->vertex);
		}
	}
}
