﻿
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
#define PIXEL_SCALE (2.5f)
#define PIXEL_TO_UNIT (0.01f)
#define UNIT_TO_PIXEL (100)
#define SCREEN_WIDTH (25 * 16 * PIXEL_SCALE)
#define SCREEN_HEIGHT (15 * 16 * PIXEL_SCALE)
#define SCREEN_WIDTH_CENTER (SCREEN_WIDTH / 2)
#define SCREEN_HEIGHT_CENTER (SCREEN_HEIGHT / 2)
#define PI (3.142f)
#define	FVF_VERTEX_2D	(D3DFVF_XYZRHW | D3DFVF_DIFFUSE | D3DFVF_TEX1)


/*------------------------------------------------------------------------------
< Engine >
------------------------------------------------------------------------------*/
#include "Core.h"
#include "Window.h"
#include "Input.h"
#include "Audio.h"
#include "Time.h"
#include "Transform.h"
#include "Sprite.h"
#include "Status.h"
#include "GameObject.h"
#include "NoneObject.h"
#include "OffsetObject.h"
#include "Camera.h"
#include "UIObject.h"
#include "BoxCollider.h"
#include "Animation.h"
#include "AnimationObject.h"
#include "Particle.h"
#include "ParticleSystem.h"
#include "Resources.h"

/*------------------------------------------------------------------------------
< GameObject >
------------------------------------------------------------------------------*/
#include "Orb.h"
#include "Bullet.h"
#include "CheckPoint.h"
#include "Score.h"
#include "Player.h"
#include "Crab.h"
#include "Flyer.h"
#include "Jumper.h"
#include "Ghost.h"
#include "Ball.h"
#include "DeathBite.h"
#include "DeathWall.h"
#include "BossBullet.h"
#include "BossCore.h"
#include "Boss.h"
#include "Ground.h"
#include "DamageZone.h"
#include "BackGround.h"
#include "Item.h"
#include "Block.h"

/*------------------------------------------------------------------------------
< Scene >
------------------------------------------------------------------------------*/
#include "Scene.h"
#include "Scene00.h"
#include "Scene01.h"
#include "Scene02.h"
#include "Scene03.h"
#include "Scene04.h"
#include "Scene05.h"
#include "Scene06.h"
#include "Scene07.h"
#include "Scene08.h"
#include "Scene09.h"
#include "Scene10.h"
#include "Scene11.h"
#include "Scene12.h"
#include "Scene13.h"
#include "Scene14.h"
#include "Scene15.h"
#include "Scene16.h"
#include "Scene17.h"
#include "Scene18.h"
#include "Scene19.h"
#include "Scene20.h"
#include "Scene21.h"
#include "Scene22.h"
#include "Scene23.h"
#include "SceneGameOver.h"
#include "SceneTitle.h"
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
Resources* GetResources();
std::vector<BoxCollider*>* GetColliders();
std::vector<GameObject*>* GetGameObjects();
std::vector<BoxCollider*> CopyColliders();
std::vector<GameObject*> CopyGameObjects();
unsigned int GetCollidersSize();
unsigned int GetGameObjectsSize();
// Engine.cpp
void Instantiate(GameObject* gameObject, Transform* transform);
float RandomRange(float min, float max);
void Destroy(GameObject* gameObject, float time);
float DistancePow(D3DXVECTOR3 a, D3DXVECTOR3 b);


#endif
