
#include "Engine.h"

Transform::Transform () {

}
Transform::~Transform () {

}

void Transform::Update(Vertex2D* vertex, int spriteX, int spriteY) {
	float sizeX = (float)(spriteX * PIXEL_SCALE) / 2.0f;
	float sizeY = (float)(spriteY * PIXEL_SCALE) / 2.0f;
	(vertex+0)->vertex = D3DXVECTOR3(this->position.x - sizeX, this->position.y - sizeY, 0.0f);
	(vertex+1)->vertex = D3DXVECTOR3(this->position.x + sizeX, this->position.y - sizeY, 0.0f);
	(vertex+2)->vertex = D3DXVECTOR3(this->position.x - sizeX, this->position.y + sizeY, 0.0f);
	(vertex+3)->vertex = D3DXVECTOR3(this->position.x + sizeX, this->position.y + sizeY, 0.0f);
}

void Transform::Update(Vertex2D* vertex, Int2D size) {
	float sizeX = (float)(size.x * PIXEL_SCALE) / 2.0f;
	float sizeY = (float)(size.y * PIXEL_SCALE) / 2.0f;
	(vertex+0)->vertex = D3DXVECTOR3(this->position.x - sizeX, this->position.y - sizeY, 0.0f);
	(vertex+1)->vertex = D3DXVECTOR3(this->position.x + sizeX, this->position.y - sizeY, 0.0f);
	(vertex+2)->vertex = D3DXVECTOR3(this->position.x - sizeX, this->position.y + sizeY, 0.0f);
	(vertex+3)->vertex = D3DXVECTOR3(this->position.x + sizeX, this->position.y + sizeY, 0.0f);
}
