
#include "Engine.h"
#include "GameObject.h"

GameObject::GameObject() {
	this->transform = new Transform();
}
GameObject::~GameObject() {
	delete this->transform;
}

void GameObject::PreStart() {
	this->time = GetTime();
}

BoxCollider * GameObject::GetCollider() {
	return nullptr;
}
