
#include "Engine.h"

/*------------------------------------------------------------------------------
< Texture Pathes >
------------------------------------------------------------------------------*/
#define TEXTURE_TILE_SETS _T("assets/tilesets.png")


/*------------------------------------------------------------------------------
< Constructor >
------------------------------------------------------------------------------*/
Ground::Ground(Sprite* sprite) {
	this->sprite = sprite;
	this->transform = new Transform();
	this->collider = new BoxCollider(this->transform, 0.0f,0.0f,32.0f,32.0f);
}


/*------------------------------------------------------------------------------
< Destructor >
------------------------------------------------------------------------------*/
Ground::~Ground() {
	delete this->transform;
	delete this->collider;
}


/*------------------------------------------------------------------------------
< Start >
------------------------------------------------------------------------------*/
void Ground::Start() {
	this->sprite->MakeSlice("Floor",160,64,32,32);
	this->sprite->SetTexture(this->vertex, "Floor");

	#ifdef _DEBUG
		this->collider->Start();
	#endif
}


/*------------------------------------------------------------------------------
< Update >
------------------------------------------------------------------------------*/
void Ground::Update() {
	this->transform->Update(this->vertex, this->sprite->slices.at("Floor").size);

	#ifdef _DEBUG
		this->collider->Update();
	#endif
}


/*------------------------------------------------------------------------------
< Draw >
------------------------------------------------------------------------------*/
void Ground::Draw() {
	this->sprite->Draw(this->vertex);

	#ifdef _DEBUG
		this->collider->Draw();
	#endif
}
