
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
}

void GameObject::UpdateTransform() {
	this->transform->Update(this->vertex);
}
