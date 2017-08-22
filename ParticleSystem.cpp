
#include "Engine.h"

ParticleSystem::ParticleSystem(int size) {
	for (int i = 0; i < size; i++) {
		this->particles.push_back(new Particle());
	}
}
ParticleSystem::~ParticleSystem() {
	for (unsigned int i = 0; i < this->particles.size(); i++) {
		delete this->particles[i];
	}
}

void ParticleSystem::LinkTexture(Texture texture) {
	for (unsigned int i = 0; i < this->particles.size(); i++) {
		this->particles[i]->sprite->texture = texture;
	}
}

void ParticleSystem::Instantiate(Transform* transform) {
	if (this->rateOverTime) {
		int counter = 0;
		for (unsigned int i = 0; i < this->particles.size(); i++) {
			if (!this->particles[i]->active) {
				this->particles[i]->Instantiate(transform);
				counter++;
				if (counter >= this->rate) {
					break;
				}
			}
		}
	}
	else {
		for (unsigned int i = 0; i < this->particles.size(); i++) {
			if (!this->particles[i]->active) {
				this->particles[i]->Instantiate(transform);
				break;
			}
		}
	}
}

void ParticleSystem::SetStartLifeTimeRange(float min, float max) {
	for (unsigned int i = 0; i < this->particles.size(); i++) {
		this->particles[i]->startLifeTimeRange = Float2D(min, max);
	}
}
void ParticleSystem::SetStartSpeedRange(float min, float max) {
	for (unsigned int i = 0; i < this->particles.size(); i++) {
		this->particles[i]->startSpeedRange = Float2D(min, max);
	}
}
void ParticleSystem::SetStartSizeRange(float min, float max) {
	for (unsigned int i = 0; i < this->particles.size(); i++) {
		this->particles[i]->startSizeRange = Float2D(min, max);
	}
}
void ParticleSystem::SetStartAngleRange(float min, float max) {
	for (unsigned int i = 0; i < this->particles.size(); i++) {
		this->particles[i]->startAngleRange = Float2D(min, max);
	}
}
void ParticleSystem::SetGravity(float gravity) {
	for (unsigned int i = 0; i < this->particles.size(); i++) {
		this->particles[i]->gravity = gravity;
	}
}
void ParticleSystem::SetColor(int r, int g, int b, int a) {
	for (unsigned int i = 0; i < this->particles.size(); i++) {
		this->particles[i]->sprite->vertex[0].diffuse = D3DCOLOR_RGBA(r,g,b,a);
		this->particles[i]->sprite->vertex[1].diffuse = D3DCOLOR_RGBA(r,g,b,a);
		this->particles[i]->sprite->vertex[2].diffuse = D3DCOLOR_RGBA(r,g,b,a);
		this->particles[i]->sprite->vertex[3].diffuse = D3DCOLOR_RGBA(r,g,b,a);
	}
}
