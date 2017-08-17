
#include "Engine.h"

Sprite::Sprite(int imageSizeX, int imageSizeY, int divideX, int divideY) {
	this->imageSize = Int2D(imageSizeX, imageSizeY);
	this->divide = Int2D(divideX, divideY);
	this->spriteSize = Int2D(imageSizeX / divideX, imageSizeY / divideY);
	this->spriteMax = divideX * divideY;
}
Sprite::Sprite(int imageSizeX, int imageSizeY) {
	this->imageSize = Int2D(imageSizeX, imageSizeY);
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

void Sprite::MakeSlice(const char* name, int x, int y, int w, int h) {
	this->slices.insert(std::make_pair(name, Slice(x,y,w,h)));
}

void Sprite::SetTexture(Vertex2D* vertex, int currentSprite) {
	float x = (float)(currentSprite % this->divide.x);
	float y = (float)(currentSprite / this->divide.y);
	float w = 1.0f / (float)this->divide.x;
	float h = 1.0f / (float)this->divide.y;

	if (this->flipX == false) {
		(vertex+0)->texCoord = D3DXVECTOR2(x*w,y*h);
		(vertex+1)->texCoord = D3DXVECTOR2(x*w+w,y*h);
		(vertex+2)->texCoord = D3DXVECTOR2(x*w,y*h+h);
		(vertex+3)->texCoord = D3DXVECTOR2(x*w+w,y*h+h);
	}
	if (this->flipX == true) {
		(vertex+0)->texCoord = D3DXVECTOR2(x*w+w,y*h);
		(vertex+1)->texCoord = D3DXVECTOR2(x*w,y*h);
		(vertex+2)->texCoord = D3DXVECTOR2(x*w+w,y*h+h);
		(vertex+3)->texCoord = D3DXVECTOR2(x*w,y*h+h);
	}
}
void Sprite::SetTexture(Vertex2D* vertex, const char* name) {
	float x = (float)this->slices.at(name).position.x / (float)this->imageSize.x;
	float y = (float)(this->imageSize.y - this->slices.at(name).position.y - this->slices.at(name).size.y) / (float)this->imageSize.y;
	float w = (float)this->slices.at(name).size.x / (float)this->imageSize.x;
	float h = (float)this->slices.at(name).size.y / (float)this->imageSize.y;;

	if (this->flipX == false) {
		(vertex+0)->texCoord = D3DXVECTOR2(x,y);
		(vertex+1)->texCoord = D3DXVECTOR2(x+w,y);
		(vertex+2)->texCoord = D3DXVECTOR2(x,y+h);
		(vertex+3)->texCoord = D3DXVECTOR2(x+w,y+h);
	}
	if (this->flipX == true) {
		(vertex+0)->texCoord = D3DXVECTOR2(x+w,y);
		(vertex+1)->texCoord = D3DXVECTOR2(x,y);
		(vertex+2)->texCoord = D3DXVECTOR2(x+w,y+h);
		(vertex+3)->texCoord = D3DXVECTOR2(x,y+h);
	}
}

void Sprite::Draw(Vertex2D* vertex) {
	this->device->SetFVF(FVF_VERTEX_2D);
	this->device->SetTexture(0,this->texture);
	this->device->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, 2, vertex, sizeof(Vertex2D));
}
