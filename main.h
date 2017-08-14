
#ifndef _MAIN_H_
#define _MAIN_H_

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

#define PIXEL_SCALE (3)

#define	FVF_VERTEX_2D	(D3DFVF_XYZRHW | D3DFVF_DIFFUSE | D3DFVF_TEX1)


/*------------------------------------------------------------------------------
< Struct >
------------------------------------------------------------------------------*/
typedef struct {
	D3DXVECTOR3 vertex;
	float rhw;
	D3DCOLOR diffuse;
	D3DXVECTOR2 texture;
} Vertex2D;


/*------------------------------------------------------------------------------
< class Prototype >
------------------------------------------------------------------------------*/
#include "Input.h"
#include "Time.h"
#include "Player.h"


/*------------------------------------------------------------------------------
< Functions >
------------------------------------------------------------------------------*/
LPDIRECT3DDEVICE9 GetDevice(void);

#endif
