
#ifndef _ORB_H_
#define _ORB_H_

class Orb : public GameObject {
private:

public:
	// Collider
	BoxCollider* collider;
	// ParticleSystem
	ParticleSystem* fxOrb;

	// Constructors
	Orb();
	~Orb();

	// virtual Functions
	void Start();
	void Update();
	void OnTriggerEnter(BoxCollider* other);
	void FixedUpdate();
};

#endif
