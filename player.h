
#ifndef _PLAYER_H_
#define _PLAYER_H_


// マクロ定義
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
HRESULT InitPlayer(void);
void UninitPlayer(void);
void UpdatePlayer(void);
void DrawPlayer(void);


#endif
