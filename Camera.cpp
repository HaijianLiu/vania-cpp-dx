
#include "Engine.h"

Camera::Camera() {

}
Camera::~Camera() {

}

void Camera::Update() {
	this->position.x = this->target->transform->position.x;
	this->position.y = this->target->transform->position.y;
	if (this->position.x <= this->range[0]->transform->position.x) {
		this->position.x = this->range[0]->transform->position.x;
	}
	if (this->position.x > this->range[1]->transform->position.x) {
		this->position.x = this->range[1]->transform->position.x;
	}
	if (this->position.y < this->range[0]->transform->position.y) {
		this->position.y = this->range[0]->transform->position.y;
	}
	if (this->position.y > this->range[1]->transform->position.y) {
		this->position.y = this->range[1]->transform->position.y;
	}
}
