
#include "Engine.h"

Transform::Transform () {
	this->camera = GetCamera();
}
Transform::~Transform () {

}


void Transform::Update(Vertex2D* vertex) {
	// World Axis to Screen Axis
	float x = (this->position.x - this->camera->position.x) * UNIT_TO_PIXEL;
	float y = (this->position.y - this->camera->position.y) * UNIT_TO_PIXEL;

	// Screen Axis
	float w = (float)(this->size.x * PIXEL_SCALE) / 2.0f;
	float h = (float)(this->size.y * PIXEL_SCALE) / 2.0f;
	(vertex+0)->vertex = D3DXVECTOR3(SCREEN_WIDTH_CENTER + x - w, SCREEN_HEIGHT_CENTER + y - h, 0.0f);
	(vertex+1)->vertex = D3DXVECTOR3(SCREEN_WIDTH_CENTER + x + w, SCREEN_HEIGHT_CENTER + y - h, 0.0f);
	(vertex+2)->vertex = D3DXVECTOR3(SCREEN_WIDTH_CENTER + x - w, SCREEN_HEIGHT_CENTER + y + h, 0.0f);
	(vertex+3)->vertex = D3DXVECTOR3(SCREEN_WIDTH_CENTER + x + w, SCREEN_HEIGHT_CENTER + y + h, 0.0f);
}


void Transform::Update(Vertex2D* vertex, int sizeX, int sizeY) {
	// World Axis to Screen Axis
	float x = (this->position.x - this->camera->position.x) * UNIT_TO_PIXEL;
	float y = (this->position.y - this->camera->position.y) * UNIT_TO_PIXEL;

	// Screen Axis
	float w = (float)(sizeX * PIXEL_SCALE) / 2.0f;
	float h = (float)(sizeY * PIXEL_SCALE) / 2.0f;
	(vertex+0)->vertex = D3DXVECTOR3(SCREEN_WIDTH_CENTER + x - w, SCREEN_HEIGHT_CENTER + y - h, 0.0f);
	(vertex+1)->vertex = D3DXVECTOR3(SCREEN_WIDTH_CENTER + x + w, SCREEN_HEIGHT_CENTER + y - h, 0.0f);
	(vertex+2)->vertex = D3DXVECTOR3(SCREEN_WIDTH_CENTER + x - w, SCREEN_HEIGHT_CENTER + y + h, 0.0f);
	(vertex+3)->vertex = D3DXVECTOR3(SCREEN_WIDTH_CENTER + x + w, SCREEN_HEIGHT_CENTER + y + h, 0.0f);
}

void Transform::Update(Vertex2D* vertex, Int2D size) {
	// World Axis to Screen Axis
	float x = (this->position.x - this->camera->position.x) * UNIT_TO_PIXEL;
	float y = (this->position.y - this->camera->position.y) * UNIT_TO_PIXEL;

	// Screen Axis
	float w = (float)(size.x * PIXEL_SCALE) / 2.0f;
	float h = (float)(size.y * PIXEL_SCALE) / 2.0f;
	(vertex+0)->vertex = D3DXVECTOR3(SCREEN_WIDTH_CENTER + x - w, SCREEN_HEIGHT_CENTER + y - h, 0.0f);
	(vertex+1)->vertex = D3DXVECTOR3(SCREEN_WIDTH_CENTER + x + w, SCREEN_HEIGHT_CENTER + y - h, 0.0f);
	(vertex+2)->vertex = D3DXVECTOR3(SCREEN_WIDTH_CENTER + x - w, SCREEN_HEIGHT_CENTER + y + h, 0.0f);
	(vertex+3)->vertex = D3DXVECTOR3(SCREEN_WIDTH_CENTER + x + w, SCREEN_HEIGHT_CENTER + y + h, 0.0f);
}

void Transform::Update(Vertex2D* vertex, D3DXVECTOR2 size) {
	// World Axis to Screen Axis
	float x = (this->position.x - this->camera->position.x) * UNIT_TO_PIXEL;
	float y = (this->position.y - this->camera->position.y) * UNIT_TO_PIXEL;

	// Screen Axis
	float w = (float)(size.x * PIXEL_SCALE) / 2.0f;
	float h = (float)(size.y * PIXEL_SCALE) / 2.0f;
	(vertex+0)->vertex = D3DXVECTOR3(SCREEN_WIDTH_CENTER + x - w, SCREEN_HEIGHT_CENTER + y - h, 0.0f);
	(vertex+1)->vertex = D3DXVECTOR3(SCREEN_WIDTH_CENTER + x + w, SCREEN_HEIGHT_CENTER + y - h, 0.0f);
	(vertex+2)->vertex = D3DXVECTOR3(SCREEN_WIDTH_CENTER + x - w, SCREEN_HEIGHT_CENTER + y + h, 0.0f);
	(vertex+3)->vertex = D3DXVECTOR3(SCREEN_WIDTH_CENTER + x + w, SCREEN_HEIGHT_CENTER + y + h, 0.0f);
}
