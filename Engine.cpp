
#include "Engine.h"

void Instantiate(GameObject* gameObject, Transform* transform) {
	gameObject->transform->position.x = transform->position.x;
	gameObject->transform->position.y = transform->position.y;
	gameObject->active = true;
	gameObject->Reset();
}

float RandomRange(float min, float max) {
	return min + (float)(rand()%1000)/999.0f * (max - min);
}

void Destroy(GameObject* gameObject, float time) {
	if ((float)gameObject->time->currentTime - (float)gameObject->birthTime > time * 1000.0f) {
		gameObject->active = false;
	}
}

float DistancePow(D3DXVECTOR3 a, D3DXVECTOR3 b) {
	return pow(a.x - b.x, 2.0f) + pow(a.y - b.y, 2.0f) + pow(a.z - b.z, 2.0f);
}
