
#ifndef _PARTICLE_SYSTEM_H_
#define _PARTICLE_SYSTEM_H_

class ParticleSystem {
private:

public:
	std::vector<Particle*> particles;
	int rate = 10;
	bool rateOverTime = true;

	ParticleSystem(int size);
	~ParticleSystem();

	void LinkTexture(Texture texture);
	void Instantiate(Transform* transform);

	// Set Parameters
	void SetStartLifeTimeRange(float min, float max);
	void SetStartSpeedRange(float min, float max);
	void SetStartSizeRange(float min, float max);
	void SetStartAngleRange(float min, float max);
	void SetGravity(float gravity);
	void SetColor(int r, int g, int b, int a);
};

#endif
