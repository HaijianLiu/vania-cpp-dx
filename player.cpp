

#include "main.h"
#include "player.h"

/*------------------------------------------------------------------------------
< Macross >
------------------------------------------------------------------------------*/
#define	NUM_VERTEX      (4) // 頂点数
#define	NUM_PLAYER      (2) // ポリゴン数
#define TEXTURE_GAME_PLAYER00 _T("assets/player/player-run.png")	// サンプル用画像 (*33)
#define TEXTURE_PLAYER00_SIZE_X (800/10*4) // テクスチャサイズ (*33)
#define TEXTURE_PLAYER00_SIZE_Y (80/1*4) // 同上 (*33)
#define TEXTURE_PATTERN_DIVIDE_X (10) // アニメパターンのテクスチャ内分割数（X) (*34)
#define TEXTURE_PATTERN_DIVIDE_Y (1) // アニメパターンのテクスチャ内分割数（Y) (*34)
#define ANIM_PATTERN_NUM         (TEXTURE_PATTERN_DIVIDE_X*TEXTURE_PATTERN_DIVIDE_Y)	// アニメーションパターン数 (*34)
#define TIME_ANIMATION           (40) // アニメーションの切り替わるカウント (*34)


Player::Player() {

	this->position = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	this->rotation = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	// テクスチャの読み込み
	this->animationCount = 0;
	this->animationPattern = 0;

	Player::SetVertex();

	this->vertex[0].rhw =
	this->vertex[1].rhw =
	this->vertex[2].rhw =
	this->vertex[3].rhw = 1.0f;

	// 反射光の設定
	this->vertex[0].diffuse = D3DCOLOR_RGBA(255, 255, 255, 0);
	this->vertex[1].diffuse = D3DCOLOR_RGBA(255, 255, 255, 0);
	this->vertex[2].diffuse = D3DCOLOR_RGBA(255, 255, 255, 0);
	this->vertex[3].diffuse = D3DCOLOR_RGBA(255, 255, 255, 0);

	// テクスチャ座標の設定
	this->vertex[0].texture = D3DXVECTOR2(0.0f, 0.0f);
	this->vertex[1].texture = D3DXVECTOR2(1.0f/TEXTURE_PATTERN_DIVIDE_X, 0.0f);
	this->vertex[2].texture = D3DXVECTOR2(0.0f, 1.0f/TEXTURE_PATTERN_DIVIDE_Y);
	this->vertex[3].texture = D3DXVECTOR2(1.0f/TEXTURE_PATTERN_DIVIDE_X, 1.0f/TEXTURE_PATTERN_DIVIDE_Y);

}

Player::~Player(void)
{
	if(this->texture != NULL ) { // テクスチャの開放
		this->texture->Release();
		this->texture = NULL;
	}
}

void Player::Start() {
	this->device = GetDevice();
	// D3DXCreateTextureFromFile(this->device, TEXTURE_GAME_PLAYER00, &texture);
	D3DXCreateTextureFromFileEx(
        this->device,
        TEXTURE_GAME_PLAYER00,
        800, 80, //★取得した画像ファイルのサイズを指定する
        1, 0,
        D3DFMT_A8R8G8B8,
        D3DPOOL_MANAGED,
        D3DX_FILTER_NONE,
        D3DX_FILTER_NONE,
        0xFF000000,
        NULL, NULL,
        &texture);
}

void Player::Update() {

	Player::SetVertex();

	this->animationCount++;
	// リセットカウンター
	if (this->animationCount > TIME_ANIMATION-1) {
		this->animationCount = 0; // 先頭に戻す
	}
	if(this->animationCount % TIME_ANIMATION == 0) {
		// パターンの切り替え
		this->animationPattern = (this->animationPattern + 1) % ANIM_PATTERN_NUM;
		// テクスチャ座標を設定
		Player::SetTexture(this->animationPattern);
	}


}

void Player::Draw() {

	this->device->SetFVF(FVF_VERTEX_2D);

	// テクスチャの設定 (*33)
	this->device->SetTexture(0,texture);

	// ポリゴンの描画
	this->device->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, 2, vertex, sizeof(Vertex2D));
}

//=============================================================================
// テクスチャ座標の設定 (*34)
//=============================================================================
void Player::SetTexture(int animationPattern)
{
	// テクスチャ座標の設定
	int x             = animationPattern % TEXTURE_PATTERN_DIVIDE_X;
	int y             = animationPattern / TEXTURE_PATTERN_DIVIDE_X;
	float sizeX       = 1.0f / TEXTURE_PATTERN_DIVIDE_X;
	float sizeY       = 1.0f / TEXTURE_PATTERN_DIVIDE_Y;

	this->vertex[0].texture = D3DXVECTOR2( (float)( x ) * sizeX, (float)( y ) * sizeY );
	this->vertex[1].texture = D3DXVECTOR2( (float)( x ) * sizeX + sizeX, (float)( y ) * sizeY );
	this->vertex[2].texture = D3DXVECTOR2( (float)( x ) * sizeX, (float)( y ) * sizeY + sizeY );
	this->vertex[3].texture = D3DXVECTOR2( (float)( x ) * sizeX + sizeX, (float)( y ) * sizeY + sizeY );
}

// 頂点座標の設定
void Player::SetVertex() {
	this->vertex[0].vertex = D3DXVECTOR3(this->position.x, this->position.y, 0.0f);
	this->vertex[1].vertex = D3DXVECTOR3(this->position.x + TEXTURE_PLAYER00_SIZE_X, this->position.y, 0.0f);
	this->vertex[2].vertex = D3DXVECTOR3(this->position.x, this->position.y + TEXTURE_PLAYER00_SIZE_Y, 0.0f);
	this->vertex[3].vertex = D3DXVECTOR3(this->position.x + TEXTURE_PLAYER00_SIZE_X, this->position.y + TEXTURE_PLAYER00_SIZE_Y, 0.0f);
}
