
#include "Engine.h"

Camera::Camera() {

}
Camera::~Camera() {

}

void Camera::Update() {
	this->position.x = this->target->transform->position.x;
	this->position.y = this->target->transform->position.y;
}
