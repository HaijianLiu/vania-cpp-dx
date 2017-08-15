
#include "Engine.h"

Sprite::Sprite(int imageSizeX, int imageSizeY, int divideX, int divideY) {
	this->imageSize = D3DXVECTOR2((float)imageSizeX, (float)imageSizeY);
	this->divide = D3DXVECTOR2((float)divideX, (float)divideY);
	this->spriteSize = D3DXVECTOR2((float)imageSizeX / (float)divideX, (float)imageSizeY / (float)divideY);
	this->spriteMax = divideX * divideY;
}
Sprite::~Sprite() {
	if (this->texture != NULL) {
		this->texture->Release();
	}
}

void Sprite::CreatTexture(const char* path) {
	this->device = GetDevice();

	D3DXCreateTextureFromFileEx(
		this->device, path,
		(int)this->imageSize.x, (int)this->imageSize.y,
		1, 0,
		D3DFMT_A8R8G8B8, D3DPOOL_MANAGED, D3DX_FILTER_NONE, D3DX_FILTER_NONE, 0xFF000000, NULL, NULL,
		&this->texture);
}
