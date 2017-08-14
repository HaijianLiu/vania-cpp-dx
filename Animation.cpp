
#include "main.h"
#include "Animation.h"

Animation::Animation(int imageSizeX, int imageSizeY, int divideX, int divideY, int sampleTime) {
	this->counter = 0;
	this->currentPattern = 0;
	this->sampleTime = sampleTime;
	this->divideX = divideX;
	this->divideY = divideY;
	this->patterSizeX = imageSizeX / this->divideX * PIXEL_SCALE;
	this->patterSizeY = imageSizeY / this->divideY * PIXEL_SCALE;
	this->patternMax = this->divideX * this->divideY;
	this->flipX = false;
}

Animation::~Animation() {
}

void Animation::Update(Vertex2D* vertex) {
	this->counter++;
	// reset counter
	if (this->counter > this->sampleTime - 1) {
		this->counter = 0;
	}
	if(this->counter % this->sampleTime == 0) {
		this->currentPattern = (this->currentPattern + 1) % this->patternMax;
		Animation::SetTexture(vertex);
	}
}

void Animation::SetTexture(Vertex2D* vertex) {
	int x = this->currentPattern % this->divideX;
	int y = this->currentPattern / this->divideY;
	float sizeX = 1.0f / this->divideX;
	float sizeY = 1.0f / this->divideY;

	if (this->flipX == false) {
		(vertex+0)->texture = D3DXVECTOR2( (float)( x ) * sizeX, (float)( y ) * sizeY );
		(vertex+1)->texture = D3DXVECTOR2( (float)( x ) * sizeX + sizeX, (float)( y ) * sizeY );
		(vertex+2)->texture = D3DXVECTOR2( (float)( x ) * sizeX, (float)( y ) * sizeY + sizeY );
		(vertex+3)->texture = D3DXVECTOR2( (float)( x ) * sizeX + sizeX, (float)( y ) * sizeY + sizeY );
	}
	if (this->flipX == true) {
		(vertex+0)->texture = D3DXVECTOR2( (float)( x ) * sizeX + sizeX, (float)( y ) * sizeY );
		(vertex+1)->texture = D3DXVECTOR2( (float)( x ) * sizeX, (float)( y ) * sizeY );
		(vertex+2)->texture = D3DXVECTOR2( (float)( x ) * sizeX + sizeX, (float)( y ) * sizeY + sizeY );
		(vertex+3)->texture = D3DXVECTOR2( (float)( x ) * sizeX, (float)( y ) * sizeY + sizeY );
	}
}
