﻿
#include "Engine.h"

/*------------------------------------------------------------------------------
< Constructor >
------------------------------------------------------------------------------*/
Item::Item() {
	// Set GameObject
	this->layer = 1;
	// Transform Size in real pixel (Int2D)
	this->transform->scale = Float2D(16.0f,16.0f);
	// Animation (divideX, divideY, sampleTime) || Slice (ID,positionX,positionY,sizeX,sizeY) all in real pixel
	this->sprite->slice = Slice(0,0,0,16,16);
	// Collider (this,offsetX,offsetY,sizeX,sizeY) size is in real pixel && Collider is trigger ?
	this->collider = new BoxCollider(this,0.0f,0.0f,16.0f,16.0f);
	this->collider->tag = "item";
	// UIObject
	this->info = new UIObject(0.0f, 0.0f, 256.0f, 128.0f);
	this->info->active = false;
}


/*------------------------------------------------------------------------------
< Destructor >
------------------------------------------------------------------------------*/
Item::~Item() {
	delete this->collider;
	delete this->info;
}


/*------------------------------------------------------------------------------
< Start >
------------------------------------------------------------------------------*/
void Item::Start() {
	// Resources
	this->sprite->texture = this->resources->texItem;
	if (this->status->tag == "dark") {
		this->sprite->slice = Slice(0,0,0,16,16);
		this->info->sprite->texture = this->resources->texUIItemDark;
	}
	if (this->status->tag == "gold") {
		this->sprite->slice = Slice(0,32,0,16,16);
		this->info->sprite->texture = this->resources->texUIItemGold;
	}
	if (this->status->tag == "sliver") {
		this->sprite->slice = Slice(0,48,0,16,16);
		this->info->sprite->texture = this->resources->texUIItemSliver;
	}
	if (this->status->tag == "bronze") {
		this->sprite->slice = Slice(0,16,0,16,16);
		this->info->sprite->texture = this->resources->texUIItemBronze;
	}

	// Animation MakeFrame()
}


/*------------------------------------------------------------------------------
< Update >
------------------------------------------------------------------------------*/
void Item::Update() {
	if (this->status->tag == "dark") {
		this->resources->fxItem->SetColor(245,103,227,255);
	}
	if (this->status->tag == "gold") {
		this->resources->fxItem->SetColor(252,226,82,255);
	}
	if (this->status->tag == "sliver") {
		this->resources->fxItem->SetColor(251,112,240,255);
	}
	if (this->status->tag == "bronze") {
		this->resources->fxItem->SetColor(195,241,136,255);
	}

	this->transform->position.y += 0.002f * sin(this->time->currentTime/300.0f);
	this->resources->fxItem->Instantiate(this->transform);

	// Animation SetTexture() || Sprite SetTexture()
	this->sprite->SetTexture();
}


/*------------------------------------------------------------------------------
< On Trigger Enter >
------------------------------------------------------------------------------*/
void Item::OnTriggerEnter(BoxCollider* other) {
	if (other->tag == "player") {
		this->active = false;
		this->resources->audOrbGet->Play();
		this->info->birthTime = this->time->currentTime;
		this->info->active = true;
		this->info->destroy = true;
	}
}


/*------------------------------------------------------------------------------
< Fixed Update >
------------------------------------------------------------------------------*/
void Item::FixedUpdate() {

}
