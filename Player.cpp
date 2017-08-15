
#include "Engine.h"

/*------------------------------------------------------------------------------
< Texture Pathes >
------------------------------------------------------------------------------*/
#define TEXTURE_PLAYER_RUN_SHOOT _T("assets/player-run-shoot.png")
#define TEXTURE_PLAYER_IDLE _T("assets/player-idle.png")


/*------------------------------------------------------------------------------
< Constructor >
------------------------------------------------------------------------------*/
Player::Player() {

	this->transform = new Transform();
	this->animRun = new Animation(800,80,10,1,4);
	this->animIdle = new Animation(240,80,3,1,15);

	this->vertex[0].rhw = 1.0f;
	this->vertex[1].rhw = 1.0f;
	this->vertex[2].rhw = 1.0f;
	this->vertex[3].rhw = 1.0f;

	this->vertex[0].diffuse = D3DCOLOR_RGBA(255, 255, 255, 0);
	this->vertex[1].diffuse = D3DCOLOR_RGBA(255, 255, 255, 0);
	this->vertex[2].diffuse = D3DCOLOR_RGBA(255, 255, 255, 0);
	this->vertex[3].diffuse = D3DCOLOR_RGBA(255, 255, 255, 0);
}


/*------------------------------------------------------------------------------
< Destructor >
------------------------------------------------------------------------------*/
Player::~Player() {
	// delete objects
	delete this->transform;
	delete this->animRun;
	delete this->animIdle;
}


/*------------------------------------------------------------------------------
< Start >
------------------------------------------------------------------------------*/
void Player::Start() {
	this->device = GetDevice();
	this->time = GetTime();
	this->animIdle->sprite->CreatTexture(TEXTURE_PLAYER_IDLE);
	this->animRun->sprite->CreatTexture(TEXTURE_PLAYER_RUN_SHOOT);
}


/*------------------------------------------------------------------------------
< Update >
------------------------------------------------------------------------------*/
void Player::Update() {

	// move
	if (GetKeyboardPress(DIK_LEFT)) {
		this->move = true;
		this->right = false;
		this->transform->position.x -= this->speed * this->time->deltaTime * UNIT_TO_PIXEL;
	}
	else if (GetKeyboardPress(DIK_RIGHT)) {
		this->move = true;
		this->right = true;
		this->transform->position.x += this->speed * this->time->deltaTime * UNIT_TO_PIXEL;
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
	if (this->air) {
		this->transform->position.y -= this->verticalSpeed  * this->time->deltaTime * UNIT_TO_PIXEL;
		this->verticalSpeed -= this->gravity * this->time->deltaTime;
	}

	// Update Transform
	this->transform->Update(this->vertex, (int)this->animRun->sprite->spriteSize.x, (int)this->animRun->sprite->spriteSize.y);
}


/*------------------------------------------------------------------------------
< Draw >
------------------------------------------------------------------------------*/
void Player::Draw() {
	if (this->move) {
		this->animRun->sprite->flipX = !this->right;
		this->animRun->Update(this->vertex);
		this->animRun->sprite->Draw(vertex);
	}
	if (!this->move) {
		this->animIdle->sprite->flipX = !this->right;
		this->animIdle->Update(this->vertex);
		this->animIdle->sprite->Draw(vertex);
	}
}
