
#ifndef _CRAB_H_
#define _CRAB_H_

class Crab : public GameObject {
private:

public:
	// Collider
	BoxCollider* collGroundCheck;
	BoxCollider* collHorizonCheck;
	// Animation
	Animation* animWalk;

	// GameObject
	Orb* orb;

	// Parameter
	float gravity = 9.8f;
	float speed = 0.3f;
	float jumpPower = 4.0f;

	// status
	bool right = false;
	bool air = true;
	float verticalSpeed = 0.0f;

	// Constructors
	Crab ();
	~Crab();

	// virtual Functions
	void Start();
	void Update();
	void OnTriggerEnter(BoxCollider* other);
	void FixedUpdate();
};

#endif
