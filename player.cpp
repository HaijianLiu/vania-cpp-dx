

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

//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
HRESULT MakeVertexPlayer(void);
void SetTexturePlayer( int cntPattern );	// (*34)
void SetVertexPlayer(void);

//*****************************************************************************
// グローバル変数
//*****************************************************************************
LPDIRECT3DTEXTURE9 g_pD3DTexturePlayer = NULL; // テクスチャへのポリゴン (*33)

Vertex2D          g_vertexWkPlayer[NUM_VERTEX];      // 頂点情報格納ワーク

D3DXVECTOR3        g_posPlayer;                // ポリゴンの移動量
D3DXVECTOR3        g_rotPlayer;                // ポリゴンの回転量
int                g_nCountAnimPlayer;                // アニメーションカウント (*34)
int                g_nPatternAnimPlayer;              // アニメーションパターンナンバー (*34)
int                g_dirPlayer = 0;

//=============================================================================
// 初期化処理
//=============================================================================
HRESULT InitPlayer(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	g_posPlayer = D3DXVECTOR3(0.5f, 0.5f, 0.5f);
	g_rotPlayer = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	g_nCountAnimPlayer = 0;
	g_nPatternAnimPlayer = 0;

	// 頂点情報の作成
	MakeVertexPlayer();

	// テクスチャの読み込み (*33)
	D3DXCreateTextureFromFile( pDevice, // デバイスのポインタ
		TEXTURE_GAME_PLAYER00,            // ファイルの名前
		&g_pD3DTexturePlayer );          // 読み込むメモリのポインタ
		
	return S_OK;
}

//=============================================================================
// 終了処理
//=============================================================================
void UninitPlayer(void)
{
	if( g_pD3DTexturePlayer != NULL ) // (*31)
	{ // テクスチャの開放
		g_pD3DTexturePlayer->Release();
		g_pD3DTexturePlayer = NULL;
	}
}

//=============================================================================
// 更新処理
//=============================================================================
void UpdatePlayer(void)
{

	SetVertexPlayer();

	g_nCountAnimPlayer++;
	// リセットカウンター
	if (g_nCountAnimPlayer > TIME_ANIMATION-1)
	{
		g_nCountAnimPlayer = 0; // 先頭に戻す
	}
	// アニメーション (*34)
	if( ( g_nCountAnimPlayer % TIME_ANIMATION ) == 0 )
	{
		// パターンの切り替え
		g_nPatternAnimPlayer = ( g_nPatternAnimPlayer + 1 ) % ANIM_PATTERN_NUM;
		// テクスチャ座標を設定
		SetTexturePlayer( g_nPatternAnimPlayer );
	}


}

//=============================================================================
// 描画処理
//=============================================================================
void DrawPlayer(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	// 頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_2D);

	// テクスチャの設定 (*33)
	pDevice->SetTexture( 0, g_pD3DTexturePlayer );

	// ポリゴンの描画
	pDevice->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, NUM_PLAYER, g_vertexWkPlayer, sizeof(Vertex2D));
}

//=============================================================================
// 頂点の作成
//=============================================================================
HRESULT MakeVertexPlayer(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	// 頂点座標の設定
	SetVertexPlayer();

	// rhwの設定
	g_vertexWkPlayer[0].rhw =
	g_vertexWkPlayer[1].rhw =
	g_vertexWkPlayer[2].rhw =
	g_vertexWkPlayer[3].rhw = 1.0f;

	// 反射光の設定 (*33)
	g_vertexWkPlayer[0].diffuse = D3DCOLOR_RGBA(255, 255, 255, 0);
	g_vertexWkPlayer[1].diffuse = D3DCOLOR_RGBA(255, 255, 255, 0);
	g_vertexWkPlayer[2].diffuse = D3DCOLOR_RGBA(255, 255, 255, 0);
	g_vertexWkPlayer[3].diffuse = D3DCOLOR_RGBA(255, 255, 255, 0);

	// テクスチャ座標の設定 (*33)
	g_vertexWkPlayer[0].texture = D3DXVECTOR2( 0.0f, 0.0f );
	g_vertexWkPlayer[1].texture = D3DXVECTOR2( 1.0f/TEXTURE_PATTERN_DIVIDE_X, 0.0f );
	g_vertexWkPlayer[2].texture = D3DXVECTOR2( 0.0f, 1.0f/TEXTURE_PATTERN_DIVIDE_Y );
	g_vertexWkPlayer[3].texture = D3DXVECTOR2( 1.0f/TEXTURE_PATTERN_DIVIDE_X, 1.0f/TEXTURE_PATTERN_DIVIDE_Y );


	return S_OK;
}

//=============================================================================
// テクスチャ座標の設定 (*34)
//=============================================================================
void SetTexturePlayer( int cntPattern )
{
	// テクスチャ座標の設定
	int x             = cntPattern % TEXTURE_PATTERN_DIVIDE_X;
	int y             = cntPattern / TEXTURE_PATTERN_DIVIDE_X;
	float sizeX       = 1.0f / TEXTURE_PATTERN_DIVIDE_X;
	float sizeY       = 1.0f / TEXTURE_PATTERN_DIVIDE_Y;

		g_vertexWkPlayer[0].texture = D3DXVECTOR2( (float)( x ) * sizeX, (float)( y ) * sizeY );
		g_vertexWkPlayer[1].texture = D3DXVECTOR2( (float)( x ) * sizeX + sizeX, (float)( y ) * sizeY );
		g_vertexWkPlayer[2].texture = D3DXVECTOR2( (float)( x ) * sizeX, (float)( y ) * sizeY + sizeY );
		g_vertexWkPlayer[3].texture = D3DXVECTOR2( (float)( x ) * sizeX + sizeX, (float)( y ) * sizeY + sizeY );
}

// 頂点座標の設定
void SetVertexPlayer(void) {
	g_vertexWkPlayer[0].vertex = D3DXVECTOR3(g_posPlayer.x, g_posPlayer.y, 0.0f);
	g_vertexWkPlayer[1].vertex = D3DXVECTOR3(g_posPlayer.x + TEXTURE_PLAYER00_SIZE_X, g_posPlayer.y, 0.0f);
	g_vertexWkPlayer[2].vertex = D3DXVECTOR3(g_posPlayer.x, g_posPlayer.y + TEXTURE_PLAYER00_SIZE_Y, 0.0f);
	g_vertexWkPlayer[3].vertex = D3DXVECTOR3(g_posPlayer.x + TEXTURE_PLAYER00_SIZE_X, g_posPlayer.y + TEXTURE_PLAYER00_SIZE_Y, 0.0f);
}
