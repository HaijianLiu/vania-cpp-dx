
#ifndef _PARTICLE_SYSTEM_H_
#define _PARTICLE_SYSTEM_H_

class ParticleSystem {
private:
	/* data */

public:
	std::vector<Particle*> particles;
	int rateOverTime = 10;

	ParticleSystem(int size);
	~ParticleSystem();

	void LinkTexture(Texture texture);
	void Instantiate(Transform* transform);
};

#endif
