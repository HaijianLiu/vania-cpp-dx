
#include "Engine.h"

/*------------------------------------------------------------------------------
< Constructor >
------------------------------------------------------------------------------*/
BossCore::BossCore() {
	this->layer = 1;
	// Transform Size in real pixel (Int2D)
	this->transform->scale = Float2D(32.0f,32.0f);
	// Animation (divideX, divideY, sampleTime) || Slice (ID,positionX,positionY,sizeX,sizeY) all in real pixel
	this->sprite->slice = Slice(0,0,0,32,32);
}


/*------------------------------------------------------------------------------
< Destructor >
------------------------------------------------------------------------------*/
BossCore::~BossCore() {

}


/*------------------------------------------------------------------------------
< Start >
------------------------------------------------------------------------------*/
void BossCore::Start() {
	// Resources
	this->sprite->texture = this->resources->texBossCore;

	// Animation MakeFrame() || Sprite MakeSlice()
	this->sprite->SetTexture();
}


/*------------------------------------------------------------------------------
< Update >
------------------------------------------------------------------------------*/
void BossCore::Update() {

}


/*------------------------------------------------------------------------------
< On Trigger Enter >
------------------------------------------------------------------------------*/
void BossCore::OnTriggerEnter(BoxCollider* other) {

}


/*------------------------------------------------------------------------------
< Fixed Update >
------------------------------------------------------------------------------*/
void BossCore::FixedUpdate() {

}


/*------------------------------------------------------------------------------
< Functions >
------------------------------------------------------------------------------*/
void BossCore::FollowTarget() {

	float angle = atan((this->target->transform->position.y - this->parent->transform->position.y) / (this->target->transform->position.x - this->parent->transform->position.x));

	if (this->target->transform->position.x < this->parent->transform->position.x) {
		this->transform->position.x -= cos(angle) * this->speed * this->time->deltaTime;
		this->transform->position.y -= sin(angle) * this->speed * this->time->deltaTime;
		if (this->transform->position.x < this->parent->transform->position.x - cos(angle) * this->radius) {
			this->transform->position.x = this->parent->transform->position.x - cos(angle) * this->radius;
		}
		if ( (this->transform->position.y <= this->parent->transform->position.y - sin(angle) * this->radius && sin(angle) >= 0) || (this->transform->position.y > this->parent->transform->position.y - sin(angle) * this->radius && sin(angle) < 0) ){
			this->transform->position.y = this->parent->transform->position.y - sin(angle) * this->radius;
		}
	}
	else {
		this->transform->position.x += cos(angle) * this->speed * this->time->deltaTime;
		this->transform->position.y += sin(angle) * this->speed * this->time->deltaTime;
		if (this->transform->position.x > this->parent->transform->position.x + cos(angle) * this->radius) {
			this->transform->position.x = this->parent->transform->position.x + cos(angle) * this->radius;
		}
		if ( (this->transform->position.y >= this->parent->transform->position.y + sin(angle) * this->radius && sin(angle) >= 0) || (this->transform->position.y < this->parent->transform->position.y + sin(angle) * this->radius && sin(angle) < 0) ){
			this->transform->position.y = this->parent->transform->position.y + sin(angle) * this->radius;
		}
	}
	// if (this->target->transform->position.x < this->parent->transform->position.x) {
	// 	this->transform->position.x = this->parent->transform->position.x - cos(angle) * this->radius;
	// 	this->transform->position.y = this->parent->transform->position.y - sin(angle) * this->radius;
	// }
	// else {
	// 	this->transform->position.x = this->parent->transform->position.x + cos(angle) * this->radius;
	// 	this->transform->position.y = this->parent->transform->position.y + sin(angle) * this->radius;
	// }
}
