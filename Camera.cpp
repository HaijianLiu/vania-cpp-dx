﻿
#include "Engine.h"

Camera::Camera() {

}
Camera::~Camera() {
	for (unsigned int i = 0; i < this->range.size(); i++) {
		delete this->range[i];
	}
}

void Camera::Update() {
	// Camera position
	if (!this->switching) {
		this->position.x = this->target->transform->position.x;
		this->position.y = this->target->transform->position.y;
	}
	else {
		if (this->position.x != this->target->transform->position.x) {
			if (this->position.x > this->target->transform->position.x) {
				this->position.x -= this->switchSpeed * this->target->time->deltaTime;
				if (this->position.x < this->target->transform->position.x) {
					this->position.x = this->target->transform->position.x;
				}
			}
			else {
				this->position.x += this->switchSpeed * this->target->time->deltaTime;
				if (this->position.x > this->target->transform->position.x) {
					this->position.x = this->target->transform->position.x;
				}
			}
		}
		if (this->position.x == this->target->transform->position.x) {
			this->switching = false;
		}
	}
	// Scene Camera Range
	if (this->position.x <= this->range[2*this->activeRange]->transform->position.x) {
		this->position.x = this->range[2*this->activeRange]->transform->position.x;
	}
	if (this->position.x > this->range[2*this->activeRange + 1]->transform->position.x) {
		this->position.x = this->range[2*this->activeRange + 1]->transform->position.x;
	}
	if (this->position.y <= this->range[2*this->activeRange]->transform->position.y) {
		this->position.y = this->range[2*this->activeRange]->transform->position.y;
	}
	if (this->position.y > this->range[2*this->activeRange + 1]->transform->position.y) {
		this->position.y = this->range[2*this->activeRange + 1]->transform->position.y;
	}
}

void Camera::SwitchTarget(GameObject* target) {
	if (!this->switching) {
		this->switching = true;
		this->target = target;
	}
}
