
#include "Engine.h"

Transform::Transform () {

}
Transform::~Transform () {

}

void Transform::Update(Vertex2D* vertex, int spriteX, int spriteY) {
	float x = this->position.x;
	float y = this->position.y;
	float w = (float)(spriteX * PIXEL_SCALE) / 2.0f;
	float h = (float)(spriteY * PIXEL_SCALE) / 2.0f;
	(vertex+0)->vertex = D3DXVECTOR3(x-w,y-h,0.0f);
	(vertex+1)->vertex = D3DXVECTOR3(x+w,y-h,0.0f);
	(vertex+2)->vertex = D3DXVECTOR3(x-w,y+h,0.0f);
	(vertex+3)->vertex = D3DXVECTOR3(x+w,y+h,0.0f);
}

void Transform::Update(Vertex2D* vertex, Int2D size) {
	float x = this->position.x;
	float y = this->position.y;
	float w = (float)(size.x * PIXEL_SCALE) / 2.0f;
	float h = (float)(size.y * PIXEL_SCALE) / 2.0f;
	(vertex+0)->vertex = D3DXVECTOR3(x-w,y-h,0.0f);
	(vertex+1)->vertex = D3DXVECTOR3(x+w,y-h,0.0f);
	(vertex+2)->vertex = D3DXVECTOR3(x-w,y+h,0.0f);
	(vertex+3)->vertex = D3DXVECTOR3(x+w,y+h,0.0f);
}
