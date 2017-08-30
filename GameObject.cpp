
#include "Engine.h"
#include "GameObject.h"

GameObject::GameObject() {
	// GetGameObjects and push_back
	this->gameObjects = GetGameObjects();
	this->gameObjects->push_back(this);
	
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
