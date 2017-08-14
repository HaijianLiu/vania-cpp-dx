

#include "main.h"
#include "Animation.h"
#include "Player.h"

/*------------------------------------------------------------------------------
< Texture Pathes >
------------------------------------------------------------------------------*/
#define TEXTURE_PLAYER_RUN_SHOOT _T("assets/player-run-shoot.png")


/*------------------------------------------------------------------------------
< Constructor >
------------------------------------------------------------------------------*/
Player::Player() {

	this->position = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	this->rotation = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	this->animRun = new Animation(800,80,10,1,4);

	Player::SetVertex();

	this->vertex[0].rhw = 1.0f;
	this->vertex[1].rhw = 1.0f;
	this->vertex[2].rhw = 1.0f;
	this->vertex[3].rhw = 1.0f;
	
	this->vertex[0].diffuse = D3DCOLOR_RGBA(255, 255, 255, 0);
	this->vertex[1].diffuse = D3DCOLOR_RGBA(255, 255, 255, 0);
	this->vertex[2].diffuse = D3DCOLOR_RGBA(255, 255, 255, 0);
	this->vertex[3].diffuse = D3DCOLOR_RGBA(255, 255, 255, 0);

	this->vertex[0].texture = D3DXVECTOR2(0.0f, 0.0f);
	this->vertex[1].texture = D3DXVECTOR2(1.0f/this->animRun->divideX, 0.0f);
	this->vertex[2].texture = D3DXVECTOR2(0.0f, 1.0f/this->animRun->divideY);
	this->vertex[3].texture = D3DXVECTOR2(1.0f/this->animRun->divideX, 1.0f/this->animRun->divideY);
}


/*------------------------------------------------------------------------------
< Destructor >
------------------------------------------------------------------------------*/
Player::~Player() {
	if (this->texture != NULL) {
		this->texture->Release();
	}
	delete animRun;
}


/*------------------------------------------------------------------------------
< Start >
------------------------------------------------------------------------------*/
void Player::Start() {
	this->device = GetDevice();

	D3DXCreateTextureFromFileEx(
		this->device, TEXTURE_PLAYER_RUN_SHOOT,
		800, 80,
		1, 0,
		D3DFMT_A8R8G8B8, D3DPOOL_MANAGED, D3DX_FILTER_NONE, D3DX_FILTER_NONE, 0xFF000000, NULL, NULL,
		&this->texture);
}


/*------------------------------------------------------------------------------
< Update >
------------------------------------------------------------------------------*/
void Player::Update() {

	Player::SetVertex();
	this->animRun->Update(this->vertex);

}


/*------------------------------------------------------------------------------
< Draw >
------------------------------------------------------------------------------*/
void Player::Draw() {
	this->device->SetFVF(FVF_VERTEX_2D);
	this->device->SetTexture(0,this->texture);
	this->device->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, 2, vertex, sizeof(Vertex2D));
}





void Player::SetVertex() {
	this->vertex[0].vertex = D3DXVECTOR3(this->position.x, this->position.y, 0.0f);
	this->vertex[1].vertex = D3DXVECTOR3(this->position.x + this->animRun->patterSizeX, this->position.y, 0.0f);
	this->vertex[2].vertex = D3DXVECTOR3(this->position.x, this->position.y + this->animRun->patterSizeY, 0.0f);
	this->vertex[3].vertex = D3DXVECTOR3(this->position.x + this->animRun->patterSizeX, this->position.y + this->animRun->patterSizeY, 0.0f);
}
