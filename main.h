
#ifndef _MAIN_H_
#define _MAIN_H_

/*------------------------------------------------------------------------------
< include >
------------------------------------------------------------------------------*/
#define _CRT_SECURE_NO_WARNINGS // scanf のwarning防止
#include "windows.h"
#include "d3dx9.h"
#include <tchar.h>

#define DIRECTINPUT_VERSION 0x0800 // 警告対処
#include "dinput.h"
#include "mmsystem.h"

#if 1	// [ここを"0"にした場合、"構成プロパティ" -> "リンカ" -> "入力" -> "追加の依存ファイル"に対象ライブラリを設定する]
	#pragma comment (lib, "d3d9.lib")
	#pragma comment (lib, "d3dx9.lib")
	#pragma comment (lib, "dinput8.lib")
	#pragma comment (lib, "dxguid.lib")
	#pragma comment (lib, "winmm.lib")
#endif


/*------------------------------------------------------------------------------
< Macross >
------------------------------------------------------------------------------*/

#define PIXEL_SCALE (4)


// 頂点フォーマット( 頂点座標[2D] / 反射光 / テクスチャ座標 )
#define	FVF_VERTEX_2D	(D3DFVF_XYZRHW | D3DFVF_DIFFUSE | D3DFVF_TEX1)


/*------------------------------------------------------------------------------
< Struct >
------------------------------------------------------------------------------*/
// 上記頂点フォーマットに合わせた構造体を定義
typedef struct {
	D3DXVECTOR3 vertex;  // 頂点座標
	float       rhw;     // テクスチャのパースペクティブコレクト用
	D3DCOLOR    diffuse; // 反射光
	D3DXVECTOR2 texture; // テクスチャ座標(*33)
} Vertex2D;


typedef struct {
	LPDIRECT3DTEXTURE9 texture;
	int divideX, divideY;
	int patterSizeX, patterSizeY;
	int currentPattern;
	int patternMax;
	int sampleTime;
	int counter;
} Animation;


/*------------------------------------------------------------------------------
< Functions >
------------------------------------------------------------------------------*/
LPDIRECT3DDEVICE9 GetDevice(void);		// デバイス取得関数

#endif
