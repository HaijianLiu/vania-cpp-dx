
#include "Engine.h"

Sprite::Sprite(int imageSizeX, int imageSizeY, int divideX, int divideY) {
	this->imageSize = Int2D(imageSizeX, imageSizeY);
	this->divide = Int2D(divideX, divideY);
	this->spriteSize = Int2D(imageSizeX / divideX * PIXEL_SCALE, imageSizeY / divideY * PIXEL_SCALE);
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
		this->imageSize.x, this->imageSize.y,
		1, 0,
		D3DFMT_A8R8G8B8, D3DPOOL_MANAGED, D3DX_FILTER_NONE, D3DX_FILTER_NONE, 0xFF000000, NULL, NULL,
		&this->texture);
}

void Sprite::SetTexture(Vertex2D* vertex, int currentSprite) {
	int x = currentSprite % this->divide.x;
	int y = currentSprite / this->divide.y;
	float sizeX = 1.0f / this->divide.x;
	float sizeY = 1.0f / this->divide.y;

	if (this->flipX == false) {
		(vertex+0)->texCoord = D3DXVECTOR2((float)x * sizeX, (float)y * sizeY);
		(vertex+1)->texCoord = D3DXVECTOR2((float)x * sizeX + sizeX, (float)y * sizeY);
		(vertex+2)->texCoord = D3DXVECTOR2((float)x * sizeX, (float)y * sizeY + sizeY);
		(vertex+3)->texCoord = D3DXVECTOR2((float)x * sizeX + sizeX, (float)y * sizeY + sizeY);
	}
	if (this->flipX == true) {
		(vertex+0)->texCoord = D3DXVECTOR2((float)x * sizeX + sizeX, (float)y * sizeY);
		(vertex+1)->texCoord = D3DXVECTOR2((float)x * sizeX, (float)y * sizeY);
		(vertex+2)->texCoord = D3DXVECTOR2((float)x * sizeX + sizeX, (float)y * sizeY + sizeY);
		(vertex+3)->texCoord = D3DXVECTOR2((float)x * sizeX, (float)y * sizeY + sizeY);
	}
}

void Sprite::Draw(Vertex2D* vertex) {
	this->device->SetFVF(FVF_VERTEX_2D);
	this->device->SetTexture(0,this->texture);
	this->device->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, 2, vertex, sizeof(Vertex2D));
}
