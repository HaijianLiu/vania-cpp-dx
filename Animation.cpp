
#include "Engine.h"

Animation::Animation(int imageSizeX, int imageSizeY, int divideX, int divideY, int sampleTime) {
	this->sprite = new Sprite(imageSizeX, imageSizeY, divideX, divideY);
	this->counter = 0;
	this->currentSprite = 0;
	this->sampleTime = sampleTime;
}

Animation::~Animation() {
	delete this->sprite;
}

void Animation::Update(Vertex2D* vertex) {
	this->counter++;
	// reset counter
	if (this->counter > this->sampleTime - 1) {
		this->counter = 0;
	}

	if(this->counter % this->sampleTime == 0) {
		this->currentSprite = (this->currentSprite + 1) % this->sprite->spriteMax;
	}

	this->sprite->SetTexture(vertex, this->currentSprite);
}
