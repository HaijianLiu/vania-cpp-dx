
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
	this->sprRun = new Sprite(800,80,10,1);
	this->animRun = new Animation(800,80,10,1,4);
	this->sprIdle = new Sprite(240,80,3,1);
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
	// delete textures
	if (this->texAnimRun != NULL) {
		this->texAnimRun->Release();
	}
	if (this->texAnimIdle != NULL) {
		this->texAnimIdle->Release();
	}
	// delete objects
	delete this->transform;
	delete this->sprRun;
	delete this->animRun;
	delete this->sprIdle;
	delete this->animIdle;
}


/*------------------------------------------------------------------------------
< Start >
------------------------------------------------------------------------------*/
void Player::Start() {
	this->device = GetDevice();
	this->time = GetTime();
	this->sprIdle->CreatTexture(TEXTURE_PLAYER_IDLE);
	this->sprRun->CreatTexture(TEXTURE_PLAYER_RUN_SHOOT);

	D3DXCreateTextureFromFileEx(
		this->device, TEXTURE_PLAYER_RUN_SHOOT,
		800, 80,
		1, 0,
		D3DFMT_A8R8G8B8, D3DPOOL_MANAGED, D3DX_FILTER_NONE, D3DX_FILTER_NONE, 0xFF000000, NULL, NULL,
		&this->texAnimRun);

	D3DXCreateTextureFromFileEx(
		this->device, TEXTURE_PLAYER_IDLE,
		240, 80,
		1, 0,
		D3DFMT_A8R8G8B8, D3DPOOL_MANAGED, D3DX_FILTER_NONE, D3DX_FILTER_NONE, 0xFF000000, NULL, NULL,
		&this->texAnimIdle);

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
		this->transform->position.y -= 0.5f * this->verticalSpeed  * this->time->deltaTime * UNIT_TO_PIXEL;
		this->verticalSpeed -= this->gravity * this->time->deltaTime;
	}

	// Update Transform
	this->transform->Update(this->vertex, this->animRun->patterSizeX, this->animRun->patterSizeY);


	// Update Animation
	if (this->move) {
		this->animRun->flipX = !this->right;
		this->animRun->Update(this->vertex);
	}
	if (!this->move) {
		this->animIdle->flipX = !this->right;
		this->animIdle->Update(this->vertex);
	}

}


/*------------------------------------------------------------------------------
< Draw >
------------------------------------------------------------------------------*/
void Player::Draw() {
	this->device->SetFVF(FVF_VERTEX_2D);
	if (this->move) {
		this->device->SetTexture(0,this->texAnimRun);
	}
	if (!this->move) {
		this->device->SetTexture(0,this->texAnimIdle);
	}
	this->device->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, 2, this->vertex, sizeof(Vertex2D));
}
