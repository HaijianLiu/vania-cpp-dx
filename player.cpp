

#include "main.h"
#include "player.h"

/*------------------------------------------------------------------------------
< Macross >
------------------------------------------------------------------------------*/
#define	NUM_VERTEX      (4) // 頂点数
#define	NUM_PLAYER      (2) // ポリゴン数
#define TEXTURE_GAME_PLAYER00 _T("assets/player/player-run.png")	// サンプル用画像 (*33)


Player::Player() {

	this->position = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	this->rotation = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	Player::SetVertex();

	this->vertex[0].rhw = 1.0f;
	this->vertex[1].rhw = 1.0f;
	this->vertex[2].rhw = 1.0f;
	this->vertex[3].rhw = 1.0f;

	// 反射光の設定
	this->vertex[0].diffuse = D3DCOLOR_RGBA(255, 255, 255, 0);
	this->vertex[1].diffuse = D3DCOLOR_RGBA(255, 255, 255, 0);
	this->vertex[2].diffuse = D3DCOLOR_RGBA(255, 255, 255, 0);
	this->vertex[3].diffuse = D3DCOLOR_RGBA(255, 255, 255, 0);

	// テクスチャ座標の設定
	this->vertex[0].texture = D3DXVECTOR2(0.0f, 0.0f);
	this->vertex[1].texture = D3DXVECTOR2(1.0f/this->animRun.divideX, 0.0f);
	this->vertex[2].texture = D3DXVECTOR2(0.0f, 1.0f/this->animRun.divideY);
	this->vertex[3].texture = D3DXVECTOR2(1.0f/this->animRun.divideX, 1.0f/this->animRun.divideY);

}

Player::~Player(void)
{
	if(this->animRun.texture != NULL ) { // テクスチャの開放
		this->animRun.texture->Release();
		this->animRun.texture = NULL;
	}
}

void Player::Start() {
	this->device = GetDevice();
	// D3DXCreateTextureFromFile(this->device, TEXTURE_GAME_PLAYER00, &texture);
	D3DXCreateTextureFromFileEx(
		this->device, TEXTURE_GAME_PLAYER00,
		800, 80, //取得した画像ファイルのサイズを指定する
		1, 0,
		D3DFMT_A8R8G8B8, D3DPOOL_MANAGED, D3DX_FILTER_NONE, D3DX_FILTER_NONE, 0xFF000000, NULL, NULL,
		&this->animRun.texture);
	this->animRun.counter = 0;
	this->animRun.pattern = 0;

	this->animRun.sampleTime = 4;
	this->animRun.divideX = 10;
	this->animRun.divideY = 1;
	this->animRun.patterSizeX = 800 / this->animRun.divideX * PIXEL_SCALE;
	this->animRun.patterSizeY = 80 / this->animRun.divideY * PIXEL_SCALE;
	this->animRun.patternMax = this->animRun.divideX * this->animRun.divideY;

}

void Player::Update() {

	Player::SetVertex();

	this->animRun.counter++;
	// リセットカウンター
	if (this->animRun.counter > this->animRun.sampleTime-1) {
		this->animRun.counter = 0; // 先頭に戻す
	}
	if(this->animRun.counter % this->animRun.sampleTime == 0) {
		// パターンの切り替え
		this->animRun.pattern = (this->animRun.pattern + 1) % this->animRun.patternMax;
		// テクスチャ座標を設定
		Player::SetTexture(this->animRun.pattern);
	}
}

void Player::Draw() {

	this->device->SetFVF(FVF_VERTEX_2D);

	// テクスチャの設定 (*33)
	this->device->SetTexture(0,this->animRun.texture);

	// ポリゴンの描画
	this->device->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, 2, vertex, sizeof(Vertex2D));
}

//=============================================================================
// テクスチャ座標の設定 (*34)
//=============================================================================
void Player::SetTexture(int animationPattern)
{
	// テクスチャ座標の設定
	int x             = animationPattern % this->animRun.divideX;
	int y             = animationPattern / this->animRun.divideY;
	float sizeX       = 1.0f / this->animRun.divideX;
	float sizeY       = 1.0f / this->animRun.divideY;

	this->vertex[0].texture = D3DXVECTOR2( (float)( x ) * sizeX, (float)( y ) * sizeY );
	this->vertex[1].texture = D3DXVECTOR2( (float)( x ) * sizeX + sizeX, (float)( y ) * sizeY );
	this->vertex[2].texture = D3DXVECTOR2( (float)( x ) * sizeX, (float)( y ) * sizeY + sizeY );
	this->vertex[3].texture = D3DXVECTOR2( (float)( x ) * sizeX + sizeX, (float)( y ) * sizeY + sizeY );
}

// 頂点座標の設定
void Player::SetVertex() {
	this->vertex[0].vertex = D3DXVECTOR3(this->position.x, this->position.y, 0.0f);
	this->vertex[1].vertex = D3DXVECTOR3(this->position.x + this->animRun.patterSizeX, this->position.y, 0.0f);
	this->vertex[2].vertex = D3DXVECTOR3(this->position.x, this->position.y + this->animRun.patterSizeY, 0.0f);
	this->vertex[3].vertex = D3DXVECTOR3(this->position.x + this->animRun.patterSizeX, this->position.y + this->animRun.patterSizeY, 0.0f);
}
