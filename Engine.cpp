
#include "Engine.h"

float RandomRange(float min, float max) {
	return min + (float)(rand()%1000)/999.0f * (max - min);
}

void Destroy(GameObject* gameObject, float time) {
	if ((float)gameObject->time->currentTime - (float)gameObject->birthTime > time * 1000.0f) {
		gameObject->active = false;
	}
}
