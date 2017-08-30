
#include "Engine.h"
#include "GameObject.h"

GameObject::GameObject() {
	// GetGameObjects and push_back
	this->gameObjects = GetGameObjects();
	this->gameObjects->push_back(this);
	// function class
	this->transform = new Transform();
	this->sprite = new Sprite();
	this->status = new Status();
}
GameObject::~GameObject() {
	delete this->transform;
	delete this->sprite;
	delete this->status;
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
