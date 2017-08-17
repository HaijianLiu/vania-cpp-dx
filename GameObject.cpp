
#include "Engine.h"

GameObject::GameObject() {
	this->transform = new Transform();
}
GameObject::~GameObject() {
	delete this->transform;
}

void GameObject::PreStart() {
	this->time = GetTime();
}
