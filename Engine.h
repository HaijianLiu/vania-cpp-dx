
#ifndef _ENGINE_H_
#define _ENGINE_H_

/*------------------------------------------------------------------------------
< include >
------------------------------------------------------------------------------*/
// Warning
#define _CRT_SECURE_NO_WARNINGS
#define DIRECTINPUT_VERSION 0x0800
// Standard
#include "stdio.h"
#include <tchar.h>
// Windows & DirectX
#include "windows.h"
#include "mmsystem.h"
#include "d3dx9.h"
#include "dinput.h"
#if 1
	#pragma comment (lib, "d3d9.lib")
	#pragma comment (lib, "d3dx9.lib")
	#pragma comment (lib, "dinput8.lib")
	#pragma comment (lib, "dxguid.lib")
	#pragma comment (lib, "winmm.lib")
#endif


/*------------------------------------------------------------------------------
< Macross >
------------------------------------------------------------------------------*/
#define SCREEN_WIDTH (800)
#define SCREEN_HEIGHT (600)
#define SCREEN_WIDTH_CENTER (SCREEN_WIDTH / 2)
#define SCREEN_HEIGHT_CENTER (SCREEN_HEIGHT / 2)
#define PIXEL_SCALE (3)
#define UNIT_TO_PIXEL (PIXEL_SCALE * 100)
#define	FVF_VERTEX_2D	(D3DFVF_XYZRHW | D3DFVF_DIFFUSE | D3DFVF_TEX1)


/*------------------------------------------------------------------------------
< Structs >
------------------------------------------------------------------------------*/
typedef struct {
	D3DXVECTOR3 vertex;
	float rhw;
	D3DCOLOR diffuse;
	D3DXVECTOR2 texture;
} Vertex2D;


/*------------------------------------------------------------------------------
< Engine classes >
------------------------------------------------------------------------------*/
#include "Input.h"
#include "Time.h"
#include "Animation.h"


/*------------------------------------------------------------------------------
< Game Object classes >
------------------------------------------------------------------------------*/
#include "Player.h"


/*------------------------------------------------------------------------------
< Global Functions >
------------------------------------------------------------------------------*/
LPDIRECT3DDEVICE9 GetDevice();
Time* GetTime();


#endif
