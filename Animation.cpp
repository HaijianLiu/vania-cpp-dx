
#include "Engine.h"
#include "Animation.h"

Animation::Animation(int divideX, int divideY, int sampleTime) {
	this->sprite = new Sprite();
	this->counter = 0;
	this->currentSprite = 0;
	this->sampleTime = sampleTime;
	this->divide = Int2D(divideX, divideY);
}

Animation::~Animation() {
	delete this->sprite;
}

void Animation::MakeFrame() {
	this->spriteSize = Int2D(this->sprite->texture.size.x / this->divide.x, this->sprite->texture.size.y / this->divide.y);
	this->spriteMax = this->divide.x * this->divide.y;
	for (int i = 0; i < this->spriteMax; i++) {
		// default divideY = 1
		this->sprite->MakeFrame(i ,i * this->spriteSize.x ,0 ,this->spriteSize.x, this->spriteSize.y);
	}
}

void Animation::SetTexture(Vertex2D* vertex) {
	this->counter++;
	// reset counter
	if (this->counter > this->sampleTime - 1) {
		this->counter = 0;
	}

	if(this->counter % this->sampleTime == 0) {
		this->currentSprite = (this->currentSprite + 1) % this->spriteMax;
	}

	this->sprite->SetTexture(vertex, this->currentSprite);
}
