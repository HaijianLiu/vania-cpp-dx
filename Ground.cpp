
#include "Engine.h"

/*------------------------------------------------------------------------------
< Texture Pathes >
------------------------------------------------------------------------------*/
#define TEXTURE_TILE_SETS _T("assets/tilesets.png")


/*------------------------------------------------------------------------------
< Constructor >
------------------------------------------------------------------------------*/
Ground::Ground(Sprite* sprite) {
	this->gameObjects = GetGameObjects();
	this->gameObjects->push_back(this);

	this->sprite = sprite;
	this->collider = new BoxCollider(this,0.0f,0.0f,32.0f,32.0f);
}


/*------------------------------------------------------------------------------
< Destructor >
------------------------------------------------------------------------------*/
Ground::~Ground() {
	delete this->collider;
}


/*------------------------------------------------------------------------------
< Start >
------------------------------------------------------------------------------*/
void Ground::Start() {
	this->sprite->MakeSlice("Floor",160,64,32,32);
	this->sprite->SetTexture(this->vertex, "Floor");

	this->transform->Update(this->vertex, this->sprite->slices.at("Floor").size);
}


/*------------------------------------------------------------------------------
< Update >
------------------------------------------------------------------------------*/
void Ground::Update() {
	// this->transform->Update(this->vertex, this->sprite->slices.at("Floor").size);
}


/*------------------------------------------------------------------------------
< Draw >
------------------------------------------------------------------------------*/
void Ground::Draw() {
	this->sprite->Draw(this->vertex);
}
