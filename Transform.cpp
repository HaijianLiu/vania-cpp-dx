
#include "Engine.h"
#include "Transform.h"

Transform::Transform () {

}
Transform::~Transform () {

}

void Transform::Update(Vertex2D* vertex, int spriteX, int spriteY) {
	(vertex+0)->vertex = D3DXVECTOR3(this->position.x - (float)spriteX / 2.0f, this->position.y - (float)spriteY / 2.0f, 0.0f);
	(vertex+1)->vertex = D3DXVECTOR3(this->position.x + (float)spriteX / 2.0f, this->position.y - (float)spriteY / 2.0f, 0.0f);
	(vertex+2)->vertex = D3DXVECTOR3(this->position.x - (float)spriteX / 2.0f, this->position.y + (float)spriteY / 2.0f, 0.0f);
	(vertex+3)->vertex = D3DXVECTOR3(this->position.x + (float)spriteX / 2.0f, this->position.y + (float)spriteY / 2.0f, 0.0f);
}
