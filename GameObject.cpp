
#include "Engine.h"
#include "GameObject.h"

GameObject::GameObject() {
	this->transform = new Transform();
	this->sprite = new Sprite();
}
GameObject::~GameObject() {
	delete this->transform;
	delete this->sprite;
}

void GameObject::PreStart() {
	this->time = GetTime();
	this->resources = GetResources();
	this->birthTime = this->time->currentTime;
	this->sprite->device = GetDevice();
}

void GameObject::UpdateTransform() {
	this->transform->Update(this->sprite->vertex);
}

void GameObject::Draw() {
	this->sprite->Draw();
}

void GameObject::Reset() {

}
