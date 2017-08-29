
#ifndef _ENGINE_H_
#define _ENGINE_H_

/*------------------------------------------------------------------------------
< include >
------------------------------------------------------------------------------*/
// Warning
#define _CRT_SECURE_NO_WARNINGS
#define DIRECTINPUT_VERSION 0x0800
// Standard
#include <iostream>
#include <sstream>
#include <vector>
#include <map>
#include <tchar.h>
// Windows & DirectX
#include "windows.h"
#include "dsound.h"
#include "mmsystem.h"
#include "d3dx9.h"
#include "dinput.h"
#if 1
	#pragma comment (lib, "d3d9.lib")
	#pragma comment (lib, "d3dx9.lib")
	#pragma comment (lib, "dinput8.lib")
	#pragma comment (lib, "dxguid.lib")
	#pragma comment ( lib, "dsound.lib" )
	#pragma comment (lib, "winmm.lib")
#endif


/*------------------------------------------------------------------------------
< Macross >
------------------------------------------------------------------------------*/
#define PIXEL_SCALE (2)
#define PIXEL_TO_UNIT (0.01f)
#define UNIT_TO_PIXEL (100)
#define SCREEN_WIDTH (25 * 16 * PIXEL_SCALE)
#define SCREEN_HEIGHT (15 * 16 * PIXEL_SCALE)
#define SCREEN_WIDTH_CENTER (SCREEN_WIDTH / 2)
#define SCREEN_HEIGHT_CENTER (SCREEN_HEIGHT / 2)
#define PI (3.142f)
#define	FVF_VERTEX_2D	(D3DFVF_XYZRHW | D3DFVF_DIFFUSE | D3DFVF_TEX1)


/*------------------------------------------------------------------------------
< Structs >
------------------------------------------------------------------------------*/
struct Vertex2D {
	D3DXVECTOR3 vertex;
	float rhw;
	D3DCOLOR diffuse;
	D3DXVECTOR2 texCoord;
	Vertex2D() {
		this->rhw = 1.0f;
		this->diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
	};
};

struct Int2D {
	int x;
	int y;
	Int2D(){};
	Int2D(int x, int y) {
		this->x = x;
		this->y = y;
	}
};

struct Float2D {
	float x;
	float y;
	Float2D(){};
	Float2D(float x, float y) {
		this->x = x;
		this->y = y;
	}
};

struct Texture {
	LPDIRECT3DTEXTURE9 texture;
	const char* path;
	Int2D size;
	Texture(){};
	Texture(const char* path, int x, int y) {
		this->texture = NULL;
		this->path = path;
		this->size = Int2D(x,y);
	}
};


/*------------------------------------------------------------------------------
< Engine >
------------------------------------------------------------------------------*/
#include "Window.h"
#include "Input.h"
#include "Audio.h"
#include "Time.h"
#include "Transform.h"
#include "Sprite.h"
#include "GameObject.h"
#include "NoneObject.h"
#include "OffsetObject.h"
#include "Camera.h"
#include "BoxCollider.h"
#include "Animation.h"
#include "Particle.h"
#include "ParticleSystem.h"

/*------------------------------------------------------------------------------
< GameObject >
------------------------------------------------------------------------------*/
#include "Bullet.h"
#include "Player.h"
#include "Crab.h"
#include "Ground.h"
#include "BackGround.h"

/*------------------------------------------------------------------------------
< Scene >
------------------------------------------------------------------------------*/
#include "Scene.h"
#include "Scene00.h"
#include "Scene01.h"
#include "Scene02.h"
#include "SceneManager.h"

/*------------------------------------------------------------------------------
< Debug >
------------------------------------------------------------------------------*/
#include "Debug.h"


/*------------------------------------------------------------------------------
< Global Functions >
------------------------------------------------------------------------------*/
// Window.cpp
LPDIRECT3DDEVICE9 GetDevice();
IDirectSound8* GetDirectSound();
// main.cpp
Time* GetTime();
Camera* GetCamera();
std::vector<BoxCollider*>* GetColliders();
std::vector<GameObject*>* GetGameObjects();
std::vector<BoxCollider*> CopyColliders();
std::vector<GameObject*> CopyGameObjects();
unsigned int GetCollidersSize();
unsigned int GetGameObjectsSize();
// Engine.cpp
float RandomRange(float min, float max);
void Destroy(GameObject* gameObject, float time);
float DistancePow(D3DXVECTOR3 a, D3DXVECTOR3 b);


#endif
