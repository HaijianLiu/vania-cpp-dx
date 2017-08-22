
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
	int counter = 0;
	for (unsigned int i = 0; i < this->particles.size(); i++) {
		if (!this->particles[i]->active) {
			this->particles[i]->Instantiate(transform);
			counter++;
			if (counter >= this->rateOverTime) {
				break;
			}
		}
	}
}
