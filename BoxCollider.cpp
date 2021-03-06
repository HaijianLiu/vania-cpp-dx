﻿
#include "Engine.h"

BoxCollider::BoxCollider(GameObject* gameObject, float x, float y, float w, float h) {
	this->colliders = GetColliders();
	this->colliders->push_back(this);

	this->gameObject = gameObject;
	this->offset.x = x;
	this->offset.y = y;
	this->size.x = w;
	this->size.y = h;
	this->halfSize.x = w / 2.0f;
	this->halfSize.y = h / 2.0f;

	#ifdef _DEBUG
		this->vertex[0].diffuse = D3DCOLOR_RGBA(0, 255, 0, 0);
		this->vertex[1].diffuse = D3DCOLOR_RGBA(0, 255, 0, 0);
		this->vertex[2].diffuse = D3DCOLOR_RGBA(0, 255, 0, 0);
		this->vertex[3].diffuse = D3DCOLOR_RGBA(0, 255, 0, 0);
		this->transform = new Transform();
		this->sprite = new Sprite(32,32);
	#endif
}
BoxCollider::~BoxCollider() {

	/* Dont forget to clear vector member here!! */

	#ifdef _DEBUG
		delete this->transform;
		delete this->sprite;
	#endif
}

#ifdef _DEBUG
	void BoxCollider::Start() {
		this->sprite->CreatTexture("assets/white-32.png");
		this->sprite->SetTexture(this->vertex);
	}
	void BoxCollider::Update() {
		this->transform->position.x = this->gameObject->transform->position.x + this->offset.x;
		this->transform->position.y = this->gameObject->transform->position.y + this->offset.y;
		this->transform->Update(this->vertex, this->size);
	}
	void BoxCollider::Draw() {
		this->sprite->Draw(this->vertex);
	}
#endif
